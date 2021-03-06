// @(#) $Id: AliHLTTPCCATrackletSelector.cxx 27042 2008-07-02 12:06:02Z richterm $
// **************************************************************************
// This file is property of and copyright by the ALICE HLT Project          *
// ALICE Experiment at CERN, All rights reserved.                           *
//                                                                          *
// Primary Authors: Sergey Gorbunov <sergey.gorbunov@kip.uni-heidelberg.de> *
//                  Ivan Kisel <kisel@kip.uni-heidelberg.de>                *
//                  for The ALICE HLT Project.                              *
//                                                                          *
// Permission to use, copy, modify and distribute this software and its     *
// documentation strictly for non-commercial purposes is hereby granted     *
// without fee, provided that the above copyright notice appears in all     *
// copies and that both the copyright notice and this permission notice     *
// appear in the supporting documentation. The authors make no claims       *
// about the suitability of this software for any purpose. It is            *
// provided "as is" without express or implied warranty.                    *
//                                                                          *
//***************************************************************************


#include "AliHLTTPCCATrackletSelector.h"
#include "AliHLTTPCCATrack.h"
#include "AliHLTTPCCATracker.h"
#include "AliHLTTPCCATrackParam.h"
#include "AliHLTTPCCATracklet.h"
#include "AliHLTTPCCAMath.h"

GPUdi() void AliHLTTPCCATrackletSelector::Thread
( int nBlocks, int nThreads, int iBlock, int iThread, int iSync,
 GPUsharedref() MEM_LOCAL(AliHLTTPCCASharedMemory) &s, GPUconstant() MEM_CONSTANT(AliHLTTPCCATracker) &tracker )
{
	// select best tracklets and kill clones

	if ( iSync == 0 ) {
		if ( iThread == 0 ) {
			s.fNTracklets = *tracker.NTracklets();
			s.fNThreadsTotal = nThreads * nBlocks;
			s.fItr0 = nThreads * iBlock;
		}
	} else if ( iSync == 1 ) {
		int nHits, nFirstTrackHit;
		AliHLTTPCCAHitId trackHits[160 - HLTCA_GPU_TRACKLET_SELECTOR_HITS_REG_SIZE];

		for ( int itr = s.fItr0 + iThread; itr < s.fNTracklets; itr += s.fNThreadsTotal ) {

#ifdef HLTCA_GPU_EMULATION_DEBUG_TRACKLET
			if (itr == HLTCA_GPU_EMULATION_DEBUG_TRACKLET)
			{
				tracker.GPUParameters()->fGPUError = 1;
			}
#endif //HLTCA_GPU_EMULATION_DEBUG_TRACKLET

			while (tracker.Tracklets()[itr].NHits() == 0)
			{
				itr += s.fNThreadsTotal;
				if (itr >= s.fNTracklets) return;
			}

			GPUglobalref() MEM_GLOBAL(AliHLTTPCCATracklet) &tracklet = tracker.Tracklets()[itr];
			const int kMaxRowGap = 4;
			const float kMaxShared = .1;

			int firstRow = tracklet.FirstRow();
			int lastRow = tracklet.LastRow();
			if (firstRow < 0 || lastRow > tracker.Param().NRows() || tracklet.NHits() < 0)
			{
#ifdef HLTCA_GPU_ALTERNATIVE_SCHEDULER
				//tracker.GPUParameters()->fGPUError = HLTCA_GPU_ERROR_WRONG_ROW;
				//return;
#else
				continue;
#endif
			}

			const int w = tracklet.HitWeight();

			//int w = (tNHits<<16)+itr;
			//int nRows = tracker.Param().NRows();
			//std::cout<<" store tracklet: "<<firstRow<<" "<<lastRow<<std::endl;

			int irow = firstRow;

			int gap = 0;
			int nShared = 0;
			nHits = 0;
			const int minHits = TRACKLET_SELECTOR_MIN_HITS(tracklet.Param().QPt());

			for (irow = firstRow; irow <= lastRow && lastRow - irow + nHits >= minHits; irow++ )
			{
				gap++;
#ifdef EXTERN_ROW_HITS
				int ih = tracker.TrackletRowHits()[irow * s.fNTracklets + itr];
#else
				int ih = tracklet.RowHit( irow );
#endif //EXTERN_ROW_HITS
				if ( ih >= 0 ) {
					GPUglobalref() const MEM_GLOBAL(AliHLTTPCCARow) &row = tracker.Row( irow );
#ifdef GLOBAL_TRACKING_ONLY_UNASSIGNED_HITS
					bool own = ( abs(tracker.HitWeight( row, ih )) <= w );
#else
					bool own = ( tracker.HitWeight( row, ih ) <= w );
#endif
					bool sharedOK = ( ( nShared < nHits * kMaxShared ) );
					if ( own || sharedOK ) {//SG!!!
						gap = 0;
#if HLTCA_GPU_TRACKLET_SELECTOR_HITS_REG_SIZE != 0
						if (nHits < HLTCA_GPU_TRACKLET_SELECTOR_HITS_REG_SIZE)
							s.fHits[iThread][nHits].Set( irow, ih );
						else
#endif //HLTCA_GPU_TRACKLET_SELECTOR_HITS_REG_SIZE != 0
							trackHits[nHits - HLTCA_GPU_TRACKLET_SELECTOR_HITS_REG_SIZE].Set( irow, ih );
						nHits++;
						if ( !own ) nShared++;
					}
				}

				if ( gap > kMaxRowGap || irow == lastRow ) { // store
					if ( nHits >= minHits ) { //SG!!!
						int itrout = CAMath::AtomicAdd( tracker.NTracks(), 1 );
#ifdef HLTCA_GPUCODE
						if (itrout >= HLTCA_GPU_MAX_TRACKS)
#else
						if (itrout >= tracker.CommonMemory()->fNTracklets * 2 + 50)
#endif //HLTCA_GPUCODE
						{
							tracker.GPUParameters()->fGPUError = HLTCA_GPU_ERROR_TRACK_OVERFLOW;
							CAMath::AtomicExch( tracker.NTracks(), 0 );
							return;
						}
						nFirstTrackHit = CAMath::AtomicAdd( tracker.NTrackHits(), nHits );
						tracker.Tracks()[itrout].SetAlive(1);
						tracker.Tracks()[itrout].SetLocalTrackId(itrout);
						tracker.Tracks()[itrout].SetParam(tracklet.Param());
						tracker.Tracks()[itrout].SetFirstHitID(nFirstTrackHit);
						tracker.Tracks()[itrout].SetNHits(nHits);
						for ( int jh = 0; jh < nHits; jh++ ) {
#if HLTCA_GPU_TRACKLET_SELECTOR_HITS_REG_SIZE != 0
							if (jh < HLTCA_GPU_TRACKLET_SELECTOR_HITS_REG_SIZE)
							{
								tracker.TrackHits()[nFirstTrackHit + jh] = s.fHits[iThread][jh];
#ifdef GLOBAL_TRACKING_ONLY_UNASSIGNED_HITS
								tracker.SetHitWeight( tracker.Row( s.fHits[iThread][jh].RowIndex() ), s.fHits[iThread][jh].HitIndex(), -w );
#endif
							}
							else
#endif //HLTCA_GPU_TRACKLET_SELECTOR_HITS_REG_SIZE != 0
							{
								tracker.TrackHits()[nFirstTrackHit + jh] = trackHits[jh - HLTCA_GPU_TRACKLET_SELECTOR_HITS_REG_SIZE];
#ifdef GLOBAL_TRACKING_ONLY_UNASSIGNED_HITS
								tracker.SetHitWeight( tracker.Row( trackHits[jh - HLTCA_GPU_TRACKLET_SELECTOR_HITS_REG_SIZE].RowIndex() ), trackHits[jh - HLTCA_GPU_TRACKLET_SELECTOR_HITS_REG_SIZE].HitIndex(), -w );
#endif
							}
						}
					}
					nHits = 0;
					gap = 0;
					nShared = 0;
				}
			}
		}
	}
}
