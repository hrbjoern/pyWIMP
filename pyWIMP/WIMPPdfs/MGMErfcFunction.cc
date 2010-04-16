 /***************************************************************************** 
  * Project: RooFit                                                           * 
  *                                                                           * 
  * This code was autogenerated by RooClassFactory                            * 
  *****************************************************************************/ 

 // Your description goes here... 

 #include "MGMErfcFunction.hh" 
 #include <math.h> 

 ClassImp(MGMErfcFunction) 

 MGMErfcFunction::MGMErfcFunction(const char *name, const char *title, 
                        RooAbsReal& _energy,
                        RooAbsReal& _mean,
                        RooAbsReal& _sigma,
                        RooAbsReal& _offset) :
   RooAbsPdf(name,title), 
   fEnergy("fEnergy","Energy",this,_energy),
   fMean("fMean","Mean",this,_mean),
   fSigma("fSigma","sigma",this,_sigma),
   fOffset("fOffset","offset",this,_offset)
 { 
 } 


 MGMErfcFunction::MGMErfcFunction(const MGMErfcFunction& other, const char* name) :  
   RooAbsPdf(other,name), 
   fEnergy("fEnergy",this,other.fEnergy),
   fMean("fMean",this,other.fMean),
   fSigma("fSigma",this,other.fSigma),
   fOffset("fOffset",this,other.fOffset)
 { 
 } 



 Double_t MGMErfcFunction::evaluate() const 
 { 
   Double_t func = 0.5 * ( erfc( (fEnergy - fMean)/(sqrt(2)*fSigma) ) ) + fOffset;
   return ( func > 1e-7 ? func : 1e-7 );
 } 

Int_t MGMErfcFunction::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const
{
   if (matchArgs(allVars, analVars, fEnergy)) return 1;
   return 0;
} 

Double_t MGMErfcFunction::integralEvaluateAt(Double_t value) const
{
   Double_t func = 0.5*(value - exp(-0.5*pow((value - fMean)/fSigma, 2.))*sqrt(2/TMath::Pi())*fSigma 
                   + (value - fMean)*erfc((value - fMean)/(sqrt(2)*fSigma)));
   return func;
}

Double_t MGMErfcFunction::analyticalIntegral(Int_t code, const char* rangeName) const
{
   assert(code==1);
   Double_t max = fEnergy.max(rangeName);
   Double_t min = fEnergy.min(rangeName);
   return integralEvaluateAt(max) - integralEvaluateAt(min) + fOffset*(max-min);
                   
}


