#ifndef AliT0AnalysisTaskQA_cxx
#define AliT0AnalysisTaskQA_cxx

// task determines mean and sigma of T0 signals  ORA, ORC, ORA-ORC, ORA+ORC/2  
// Authors: FK  

#define NPMT0 24  //number T0 of photomultipliers

class TH1F;
class TObjArray; 
class AliESDEvent;
class TH2F;

#include "AliAnalysisTaskSE.h"

class AliT0AnalysisTaskQA : public AliAnalysisTaskSE {
 public:
  AliT0AnalysisTaskQA();
  AliT0AnalysisTaskQA(const char *name);
  virtual ~AliT0AnalysisTaskQA(); 
  
  virtual void   UserCreateOutputObjects();
  virtual void   UserExec(Option_t *option);
  virtual void   Terminate(Option_t *);
  TObjArray* GetOffsetHistos() {return fTzeroObject;}
  
 private:
  AliESDEvent *fESD;          //! ESD object
  TObjArray   *fTzeroObject;  // array with CFDi-CFD1 and  CFDi
  TH1F        *fTzeroORA;     //! or A spectrum    
  TH1F        *fTzeroORC;     //! or C spectrum    
  TH1F        *fResolution;   //! or A minus or C spectrum    
  TH1F        *fTzeroORAplusORC; //! ORA+ORC /2 
  int         fRunNumber;
  TH2F        **fTimeVSAmplitude; //! Time vs. Amplitude
  TH2F        *fCFDVSPmtId;   //! CFDi vs pmt id
  TH2F        *fSPDVertexVST0Vertex; //! SPD vertex vs T0 vertex   
  TH2F        *fOrAvsNtracks; //! T0A vs Ntracks
  TH2F        *fOrCvsNtracks; //! T0C vs Ntracks
  TH2F        *fT0vsNtracks; //! T0A vs Ntracks
  
 
  AliT0AnalysisTaskQA(const AliT0AnalysisTaskQA&); // not implemented
  AliT0AnalysisTaskQA& operator=(const AliT0AnalysisTaskQA&); // not implemented
  
  ClassDef(AliT0AnalysisTaskQA, 1); // example of analysis
};

#endif
