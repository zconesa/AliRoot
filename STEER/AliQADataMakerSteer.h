#ifndef ALIQADATAMAKERSTEER_H
#define ALIQADATAMAKERSTEER_H
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// class for running the QA makers                                           //
//                                                                           //
//   AliQADataMakerSteer qas;                                                //
//   qas.Run(AliQA::kRAWS, rawROOTFileName);                                 //
//   qas.Run(AliQA::kHITS);                                                  //
//   qas.Run(AliQA::kSDIGITS);                                               //
//   qas.Run(AliQA::kDIGITS);                                                //
//   qas.Run(AliQA::kRECPOINTS);                                             //
//   qas.Run(AliQA::kESDS);                                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include <TNamed.h>
#include "AliQA.h"
#include "AliLoader.h" 
 
class AliQADataMaker ;
class AliRawReader ;  
class AliRunLoader ; 
class AliESDEvent ; 

class AliQADataMakerSteer: public TNamed {
public:
	AliQADataMakerSteer(const char* gAliceFilename = "galice.root", 
						const char * name = "AliQADataMakerSteer", 
						const char * title = "QA makers") ; 
	AliQADataMakerSteer(const AliQADataMakerSteer & qas) ; 
	AliQADataMakerSteer & operator = (const AliQADataMakerSteer & qas) ; 
	virtual ~AliQADataMakerSteer() ; 
	UInt_t   GetCurrentEvent() const { return fCurrentEvent ; }
    TObjArray * GetFromOCDB(AliQA::DETECTORINDEX_t det, AliQA::TASKINDEX_t task, const char * year) const ; 
	Bool_t  Merge(const Int_t runNumber = -1) const ;  
    void    Reset(const Bool_t sameCycle = kFALSE) ;  
	TString Run(const char * detectors, const AliQA::TASKINDEX_t taskIndex, Bool_t const sameCycle = kFALSE, const char * fileName = NULL) ; 
	TString Run(const char * detectors, AliRawReader * rawReader, Bool_t const sameCycle = kFALSE) ; 
	TString Run(const char * detectors, const char * filename, Bool_t const sameCycle = kFALSE) ;
    Bool_t  Save2OCDB(const Int_t runNumber, const char * year = "08", const Int_t cycleNumber=0, const char * detectors = "ALL") const ; 
	void    SetCycleLength(const AliQA::DETECTORINDEX_t det, const Int_t cycle) { fQACycles[det] = cycle ; }
	void    SetMaxEvents(UInt_t max) { fMaxEvents = max ; }      
	void    SetNewCycle() { fCycleSame = kTRUE ; }
    void    SetRunLoader(AliRunLoader * rl) { fRunLoader = rl ; }

private: 
	Bool_t			 DoIt(const AliQA::TASKINDEX_t taskIndex, const char * mode) ;
	AliLoader      * GetLoader(Int_t iDet) ; 
	const Int_t      GetQACycles(const Int_t iDet) { return fQACycles[iDet] ; }
	AliQADataMaker * GetQADataMaker(const Int_t iDet, const char * mode) ; 
	Bool_t			 Init(const AliQA::TASKINDEX_t taskIndex, const char * mode, const  char * fileName = NULL) ;
	Bool_t           InitRunLoader() ; 
	Bool_t           IsSelected(const char * detName)  ;
	Bool_t           Finish(const AliQA::TASKINDEX_t taskIndex, const char * mode) ;
	Bool_t           SaveIt2OCDB(const Int_t runNumber, TFile * inputFile, const char * year) const ;  

 
	UInt_t             fCurrentEvent ;                 //! event counter
	Bool_t			   fCycleSame ;                    //! true if 2 consecutive data making for a same detector   
    TString            fDetectors ;                    //! list of active detectors 
    TString            fDetectorsW ;                   //! list of active detectors with QA implemented 
	AliESDEvent *      fESD ;                          //! current ESD
	TTree *            fESDTree ;                      //! current ESD Tree
	Bool_t             fFirst ;                        //! to search the detector QA data maker only once
	TString            fGAliceFileName ;               //! name of the galice file
	Int_t              fMaxEvents ;                    //! number of events to process
	Long64_t           fNumberOfEvents ;               //! number of events in the run 
	UInt_t             fRunNumber ;                    //! current run number
	AliRawReader     * fRawReader ;                    //! current raw reader object 
	Bool_t             fRawReaderDelete ;              //! tells if the rawReader has been created by this
	AliRunLoader *     fRunLoader ;                    //! current run loader object
	static const UInt_t fgkNDetectors = AliQA::kNDET ; //! number of detectors    
	AliLoader      *   fLoader[fgkNDetectors];         //! array of detectors loader
	AliQADataMaker *   fQADataMaker[fgkNDetectors];    //! array of QA data maker objects
	Int_t              fQACycles[fgkNDetectors];       //! array of QA cycle length
	
  ClassDef(AliQADataMakerSteer, 0)      // class for running the QA makers
};

#endif
