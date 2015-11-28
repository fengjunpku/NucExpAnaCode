#include "TROOT.h"
#include "TVector3.h"
#include "TMath.h"
#include "TString.h"
#include "TH1.h"
#include "TCanvas.h"
const Double_t m0=13.;
const Double_t ml=4.;
const Double_t mh=9.;

void PieceFly();
void DisOfHP(TVector3 p0,Double_t Ecos);

void Vpiece(TVector3 p0,Double_t Ecos,TVector3 &Heavy,TVector3 &Light);