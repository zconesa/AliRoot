#!/bin/sh
# $Id$

CURDIR=`pwd`
OUTDIR=test_out

rm -fr $OUTDIR
mkdir $OUTDIR
cp .rootrc $OUTDIR
cd $OUTDIR

echo "Running simulation  ..."

aliroot -b >& testSim.out << EOF 
AliSimulation MuonSim("$ALICE_ROOT/MUON/Config.C")
MuonSim.Run(10)
.q
EOF

echo "Running reconstruction  ..."

aliroot -b >& testReco.out << EOF
TPluginManager* pluginManager = gROOT->GetPluginManager();
pluginManager->AddHandler("AliReconstructor", "MUON","AliMUONReconstructor", "MUON","AliMUONReconstructor()")
AliReconstruction MuonRec("galice.root")
MuonRec.SetRunTracking("")
MuonRec.SetRunVertexFinder(kFALSE)
MuonRec.SetRunLocalReconstruction("MUON")
MuonRec.SetFillESD("MUON")
MuonRec.Run()
.q
EOF

echo "Running efficiency  ..."

aliroot -b >& testResults.out << EOF
.includepath $ALICE_ROOT/STEER
.includepath $ALICE_ROOT/MUON
.L $ALICE_ROOT/MUON/MUONefficiency.C++
// no argument assumes Upsilon but MUONefficiency(443) works on Jpsi
MUONefficiency();
.q
EOF

echo "Finished"  
echo "... see results in test_out"

cd $CURDIR
