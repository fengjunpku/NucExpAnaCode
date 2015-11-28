#include "TROOT.h"
#include "TVector3.h"
#include "TMath.h"
#include "TString.h"
#include "TH1.h"
#include "TH2F.h"
#include "TF1.h"
#include "TCanvas.h"

const Double_t M_a=13.0;//beam
const Double_t M_A=9.0;//target
const Double_t M_b=13.0;//out
const Double_t M_B=9.0;//recoil
const Double_t Me=0.511/939;//elec:u
const Int_t Z_a=6;
const Int_t Z_A=4;
const Double_t NA=6.022e23;
const Double_t rou_A=1.85;//unit:g/cm3
const Double_t qe=1.60217e-19;//unit:C
const Double_t KK=81e18;//  JingDianLi Const ^2

Double_t deLoss(Double_t Ek);
void Scattering();
Double_t scatterE(Double_t Ein,Double_t sTheta);
Double_t LossE(Double_t Ein,Double_t Deff);
Double_t Range(Double_t Ein);