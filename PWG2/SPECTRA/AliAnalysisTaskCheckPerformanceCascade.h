#ifndef ALIANALYSISTASKCHECKPERFORMANCECASCADE_H
#define ALIANALYSISTASKCHECKPERFORMANCECASCADE_H

/*  See cxx source for full Copyright notice */

//-----------------------------------------------------------------
//		 AliAnalysisTaskCheckPerformanceCascade class
//            This task is for a performance study of cascade identification.
//            It works with MC info and ESD/AOD tree.
//            Origin   : A.Maire Mar2009, antonin.maire@ires.in2p3.fr
//            Modified : A.Maire Aug2009, antonin.maire@ires.in2p3.fr
//-----------------------------------------------------------------

class TList;
class TH1F;
class TH2F;
class AliESDEvent;

#include "AliAnalysisTaskSE.h"

class AliAnalysisTaskCheckPerformanceCascade : public AliAnalysisTaskSE {
 public:
 
  AliAnalysisTaskCheckPerformanceCascade();
  AliAnalysisTaskCheckPerformanceCascade(const char *name );
  virtual ~AliAnalysisTaskCheckPerformanceCascade() {}
  
  //virtual void   ConnectInputData(Option_t *);
  virtual void   UserCreateOutputObjects();
  virtual void   UserExec(Option_t *option);
  virtual void   Terminate(Option_t *);
  
  void SetDebugLevelCascade(Int_t lDebugCascade = 0)          {fDebugCascade = lDebugCascade;}
  void SetCollidingSystems (Short_t collidingSystems = 0)     {fCollidingSystems = collidingSystems;}
  void SetAnalysisType     (const char* analysisType = "ESD") {fAnalysisType = analysisType;}
  
 private:
	Int_t	fDebugCascade;			// Denug Flag for this task devoted to cascade
	TString fAnalysisType;			// "ESD" or "AOD" analysis type	
	Short_t fCollidingSystems;		// 0 = pp collisions or 1 = AA collisions
	
 	TList	*fListHistCascade;		//! List of Cascade histograms
		// - Histos 
	TH1F	*fHistMCTrackMultiplicity;	//! MC Track multiplicity
	
	
	// proton
	TH1F	*fHistEtaGenProton;   			//! MC Pseudo-rapidity of any generated p+ (no cuts in acceptance)
	TH1F	*fHistEtaGenAntiProton;   		//! MC Pseudo-rapidity of any generated p+ (no cuts in acceptance)

// Part 1 - Generated cascades
	
	//--------------
	// Xi-
	TH1F	*fHistEtaGenCascXiMinus;   		//! MC Pseudo-rapidity of any generated Xi- (no cuts in acceptance)
	TH2F	*f2dHistGenPtVsGenYGenXiMinus;		//! MC Pt Vs MC Y of generated Xi- 
		
	// - Histos planned for Xi- emitted within the acceptance (cuts in theta + pt of daughters)
	// 	= findable cascades
	TH1F	*fHistThetaGenCascXiMinus;		//! MC Theta angle of the generated Xi-
	TH2F	*f2dHistGenPtVsGenYFdblXiMinus;		//! MC Pt Vs MC y of the findable Xi-
	
	TH1F	*fHistThetaLambdaXiMinus;		//! MC Theta angle of the Lambda daughter of the generated Xi-
	TH1F	*fHistThetaBachXiMinus;			//! MC Theta angle of the Bachelor (pi-)
	
	TH1F	*fHistThetaMesDghterXiMinus;		//! MC Theta angle of the mesonic  V0 daughter in the generated cascade, pi-
	TH1F	*fHistThetaBarDghterXiMinus;		//! MC Theta angle of the baryonic V0 daughter in the generated cascade, p+
	
	TH1F	*fHistPtBachXiMinus;   			//! MC Pt of the Bachelor (pi-)                         (Control Plot)
	TH1F	*fHistPtMesDghterXiMinus;		//! MC Pt of the meson daughter of the 'Lambda0', pi-   (Control Plot)
	TH1F	*fHistPtBarDghterXiMinus;		//! MC Pt of the baryon daughter of the 'Lambda0', p+   (Control Plot)
	
	
	
	//--------------
	// Xi+
	TH1F	*fHistEtaGenCascXiPlus;   		//! MC Pseudo-rapidity of any generated Xi+ (no cuts in acceptance)
	TH2F	*f2dHistGenPtVsGenYGenXiPlus;		//! MC Pt Vs MC Y of generated Xi+ 
			
	// - Histos planned for Xi+ emitted within the acceptance (cuts in theta + pt of daughters)
	TH1F	*fHistThetaGenCascXiPlus;		//! MC Theta angle of the generated Xi+
	TH2F	*f2dHistGenPtVsGenYFdblXiPlus;		//! MC Pt Vs MC y of the findable Xi+
	
	TH1F	*fHistThetaLambdaXiPlus;		//! MC Theta angle of the anti-Lambda daughter of the generated Xi+
	TH1F	*fHistThetaBachXiPlus;			//! MC Theta angle of the Bachelor (pi+)
	
	TH1F	*fHistThetaMesDghterXiPlus;		//! MC Theta angle of the mesonic  V0 daughter in the generated cascade, pi+
	TH1F	*fHistThetaBarDghterXiPlus;		//! MC Theta angle of the baryonic V0 daughter in the generated cascade, p-
	
	TH1F	*fHistPtBachXiPlus;   			//! MC Pt of the Bachelor (pi+)                       (Control Plot)
	TH1F	*fHistPtMesDghterXiPlus;		//! MC Pt of the meson daughter of the 'Lambda0', pi+ (Control Plot)
	TH1F	*fHistPtBarDghterXiPlus;		//! MC Pt of the baryon daughter of the 'Lambda0', p- (Control Plot)
	
	
	
	//--------------
	// Omega-
	TH1F	*fHistEtaGenCascOmegaMinus;   		//! MC Pseudo-rapidity of any generated Omega- (no cuts in acceptance)
	TH2F	*f2dHistGenPtVsGenYGenOmegaMinus; 	//! MC Pt Vs MC Y of generated Omega- 	
	
	// - Histos planned for Omega- emitted within the acceptance (cuts in theta + pt of daughters)
	TH1F	*fHistThetaGenCascOmegaMinus;		//! MC Theta angle of the generated Omega-
	TH2F	*f2dHistGenPtVsGenYFdblOmegaMinus;	//! MC Pt Vs MC y of the findable Omega-
	
	TH1F	*fHistThetaLambdaOmegaMinus;		//! MC Theta angle of the Lambda daughter of the generated Omega-
	TH1F	*fHistThetaBachOmegaMinus;		//! MC Theta angle of the Bachelor (K-)
	
	TH1F	*fHistThetaMesDghterOmegaMinus;		//! MC Theta angle of the mesonic  V0 daughter in the generated cascade, pi-
	TH1F	*fHistThetaBarDghterOmegaMinus;		//! MC Theta angle of the baryonic V0 daughter in the generated cascade, p+
	
	TH1F	*fHistPtBachOmegaMinus;   		//! MC Pt of the Bachelor (K-)                   (Control Plot)
	TH1F	*fHistPtMesDghterOmegaMinus;		//! MC Pt of the meson daughter of the 'Lambda0', pi- (Control Plot)
	TH1F	*fHistPtBarDghterOmegaMinus;		//! MC Pt of the baryon daughter of the 'Lambda0', p+ (Control Plot)
	
	
	
	//--------------
	// Omega+
	TH1F	*fHistEtaGenCascOmegaPlus;   		//! MC Pseudo-rapidity of any generated Omega+ (no cuts in acceptance)
	TH2F	*f2dHistGenPtVsGenYGenOmegaPlus; 	//! MC Pt Vs MC Y of generated Omega+	
		
	// - Histos planned for Omega+ emitted within the acceptance (cuts in theta + pt of daughters)
	TH1F	*fHistThetaGenCascOmegaPlus;		//! MC Theta angle of the generated Omega+
	TH2F	*f2dHistGenPtVsGenYFdblOmegaPlus;	//! MC Pt Vs MC y of the findable Omega+
	
	TH1F	*fHistThetaLambdaOmegaPlus;		//! MC Theta angle of the anti-Lambda daughter of the generated Omega+
	TH1F	*fHistThetaBachOmegaPlus;		//! MC Theta angle of the Bachelor (K+)
	
	TH1F	*fHistThetaMesDghterOmegaPlus;		//! MC Theta angle of the mesonic  V0 daughter in the generated cascade, pi+
	TH1F	*fHistThetaBarDghterOmegaPlus;		//! MC Theta angle of the baryonic V0 daughter in the generated cascade, p-
	
	TH1F	*fHistPtBachOmegaPlus;   		//! MC Pt of the Bachelor (K+) (Control Plot)
	TH1F	*fHistPtMesDghterOmegaPlus;		//! MC Pt of the meson daughter of the 'Lambda0', pi+ (Control Plot)
	TH1F	*fHistPtBarDghterOmegaPlus;		//! MC Pt of the baryon daughter of the 'Lambda0', p- (Control Plot)
	
	
	
// Part 2 - Any reconstructed cascades + reconstructed cascades associated with MC
	// 2.1 - Effective mass and PID
	// - Effective mass histos for all the cascade candidates
	TH1F	*fHistMassXiMinus;			//! reconstructed cascade effective mass, under Xi- hyp.
	TH1F	*fHistMassXiPlus;			//! reconstructed cascade effective mass, under Xi+ hyp.
	TH1F	*fHistMassOmegaMinus;			//! reconstructed cascade effective mass, under Omega- hyp.
	TH1F	*fHistMassOmegaPlus;			//! reconstructed cascade effective mass, under Omega+ hyp.
	
	// - Effective mass histos with reconstruction combined PID
	TH1F	*fHistMassWithCombPIDXiMinus;		//! reconstructed Xi- effective mass, with bach. comb PID
	TH1F	*fHistMassWithCombPIDXiPlus;		//! reconstructed Xi+ effective mass, with bach. comb PID
	TH1F	*fHistMassWithCombPIDOmegaMinus;	//! reconstructed Omega- effective mass, with bach. comb PID
	TH1F	*fHistMassWithCombPIDOmegaPlus;		//! reconstructed Omega+ effective mass, with bach. comb PID
	
	// - PID Probability versus MC Pt(bachelor track)
	TH2F	*f2dHistPIDprobaKaonVsMCPtBach;		//! Comb. PID probability for the bach. to be a Kaon Vs MC pt(bach)
	TH2F	*f2dHistPIDprobaPionVsMCPtBach;		//! Comb. PID probability for the bach. to be a Pion Vs MC pt(bach)	

	// - Effective mass histos with perfect MC PID
	TH1F	*fHistMassWithMcPIDXiMinus;		//! reconstructed Xi- effective mass, with MC bach. PID
	TH1F	*fHistMassWithMcPIDXiPlus;		//! reconstructed Xi+ effective mass, with MC bach. PID
	TH1F	*fHistMassWithMcPIDOmegaMinus;		//! reconstructed Omega- effective mass, with MC bach. PID
	TH1F	*fHistMassWithMcPIDOmegaPlus;		//! reconstructed Omega+ effective mass, with MC bach. PID

	
	// 2.2 - Associated candidates
	// - Effective mass histos for the cascade candidates associated with MC, without PID info
	TH1F	*fHistAsMCMassXiMinus;			//! reconstr. cascade effective mass, under Xi- hyp. for Associated cand.
	TH1F	*fHistAsMCMassXiPlus;			//! reconstr. cascade effective mass, under Xi+ hyp. for Associated cand.
	TH1F	*fHistAsMCMassOmegaMinus;		//! reconstr. cascade effective mass, under Omega- hyp. for Associated cand.
	TH1F	*fHistAsMCMassOmegaPlus;		//! reconstr. cascade effective mass, under Omega+ hyp. for Associated cand.
	
	// -  Generated Pt Vs generated Y of the cascade candidates associated with MC 
	//     + having the proper maximum proba of combined PID for the bachelor
	TH2F	*f2dHistAsMCandCombPIDGenPtVsGenYXiMinus;	//! Pt(gen) Vs Y(gen) from the MC Xi- associated with Reco cand + with PID info
	TH2F	*f2dHistAsMCandCombPIDGenPtVsGenYXiPlus;	//! Pt(gen) Vs Y(gen) from the MC Xi+ associated with Reco cand + with PID info
	TH2F	*f2dHistAsMCandCombPIDGenPtVsGenYOmegaMinus;	//! Pt(gen) Vs Y(gen) from the MC Omega- associated with Reco cand + with PID info
	TH2F	*f2dHistAsMCandCombPIDGenPtVsGenYOmegaPlus;	//! Pt(gen) Vs Y(gen) from the MC Omega+ associated with Reco cand + with PID info
	
	// - Generated Pt Vs generated Y, for the cascade candidates associated with MC, without PID info
	TH2F	*f2dHistAsMCGenPtVsGenYXiMinus;		//! gen. Pt Vs gen. Rap. from the MC Xi- associated with a reconstr. cascade
	TH2F	*f2dHistAsMCGenPtVsGenYXiPlus;		//! gen. Pt Vs gen. Rap. from the MC Xi+ associated with a reconstr. cascade
	TH2F	*f2dHistAsMCGenPtVsGenYOmegaMinus;	//! gen. Pt Vs gen. Rap. from the MC Omega- associated with a reconstr. cascade
	TH2F	*f2dHistAsMCGenPtVsGenYOmegaPlus;	//! gen. Pt Vs gen. Rap. from the MC Omega+ associated with a reconstr. cascade
	
	// - Generated Eta of the the cascade candidates associated with MC, without PID info
	TH1F	*fHistAsMCGenEtaXiMinus;		//! generated Eta from the MC Xi- associated with a reconstr. cascade
	TH1F	*fHistAsMCGenEtaXiPlus;			//! generated Eta from the MC Xi+ associated with a reconstr. cascade
	TH1F	*fHistAsMCGenEtaOmegaMinus;		//! generated Eta from the MC Omega- associated with a reconstr. cascade
	TH1F	*fHistAsMCGenEtaOmegaPlus;		//! generated Eta from the MC Omega+ associated with a reconstr. cascade
	
	// - Resolution in Pt as function of generated Pt
	TH2F	*f2dHistAsMCResPtXiMinus;		//! resolution in Pt as function of gen. Pt, for Xi-
	TH2F	*f2dHistAsMCResPtXiPlus;		//! resolution in Pt as function of gen. Pt, for Xi-
	TH2F	*f2dHistAsMCResPtOmegaMinus;		//! resolution in Pt as function of gen. Pt, for Omega-
	TH2F	*f2dHistAsMCResPtOmegaPlus;		//! resolution in Pt as function of gen. Pt, for Omega+
	
	// - Resolution in R(2D) as function of generated R
	TH2F	*f2dHistAsMCResRXiMinus;		//! resolution in transv. R = f(transv. gen. R), for Xi-
	TH2F	*f2dHistAsMCResRXiPlus;			//! resolution in transv. R = f(transv. gen. R), for Xi+
	TH2F	*f2dHistAsMCResROmegaMinus;		//! resolution in transv. R = f(transv. gen. R), for Omega-
	TH2F	*f2dHistAsMCResROmegaPlus;		//! resolution in transv. R = f(transv. gen. R), for Omega+
	
	
  AliAnalysisTaskCheckPerformanceCascade(const AliAnalysisTaskCheckPerformanceCascade&);            // not implemented
  AliAnalysisTaskCheckPerformanceCascade& operator=(const AliAnalysisTaskCheckPerformanceCascade&); // not implemented
  
  ClassDef(AliAnalysisTaskCheckPerformanceCascade, 2);
};

#endif
