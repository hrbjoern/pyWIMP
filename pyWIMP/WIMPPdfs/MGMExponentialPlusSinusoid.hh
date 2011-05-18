/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef _MGMExponentialPlusSinusoid_hh_
#define _MGMExponentialPlusSinusoid_hh_

#include "MGMPiecewiseFunction.hh"
 
class MGMExponentialPlusSinusoid : public MGMPiecewiseFunction {
public:
  MGMExponentialPlusSinusoid() : MGMPiecewiseFunction() {} ; 
  MGMExponentialPlusSinusoid(const char *name, const char *title,
              RooAbsReal& _x, 
              RooAbsReal& _per, 
              RooAbsReal& _phase);
  MGMExponentialPlusSinusoid(const MGMExponentialPlusSinusoid& other, 
                             const char* name=0);
  virtual TObject* clone(const char* newname) const 
    { return new MGMExponentialPlusSinusoid(*this,newname); }
  inline virtual ~MGMExponentialPlusSinusoid() {}

  Double_t analyticalIntegral(Int_t code, const char* rangeName) const;
protected:
  
  Double_t evaluate() const ;
  RooRealProxy fPeriod;
  RooRealProxy fPhase;

  Double_t IntegralValueAtPoint(Double_t point) const;

private:

  ClassDef(MGMExponentialPlusSinusoid,1) // Your description goes here...
};
 
#endif
