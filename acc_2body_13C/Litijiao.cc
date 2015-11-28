#include "TROOT.h"
#include "TVector3.h"
#include "TMath.h"
#include "TString.h"
#include "TH1.h"
#include "TH2F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TGraph.h"

const Double_t PIE=TMath::Pi();
const Double_t halfSize=2.5;//cm
const Double_t distance=10.;//cm
const Double_t posAngle=20.*PIE/180.;//rd

void Litijiao()
{
	TCanvas *c1 = new TCanvas("c1","Dis of Piece",800,600);
	TGraph *gr= new TGraph();Int_t gn=0;
	TVector3 scan;
	Double_t phi,theta,angle;
	Double_t TOT=10000;
	Double_t acc,count,MaxPhi;	
	angle=0.;
	///////////////
	TRandom3 rand[3];
	Int_t timer=(Int_t)time(0);
	for(Int_t ii=0;ii<3;ii++){rand[ii].SetSeed(timer+ii);}
	/////////////
	while(angle<28.6)
	{
		count=0.;
		MaxPhi=0.;
		theta=angle*PIE/180.;
		for(Int_t i=0;i<TOT;i++)
		{
			phi=2*PIE*rand[0].Rndm();
			scan.SetMagThetaPhi(1,theta,phi);
			if(isHit(scan)) {count+=1.;if(phi<PIE&&phi>MaxPhi) MaxPhi=phi;}
		}
		acc=count/TOT;
		gr->SetPoint(gn,angle,MaxPhi*180/PIE);gn++;
		angle+=0.5;
		
	}
	gr->Draw("AP*");
}

Bool_t isHit(TVector3 vel)
{
	vel.RotateY(-posAngle);
	
	Double_t temTheta=vel.Theta();
	Double_t temPhi=vel.Phi();
	
	Double_t xx=distance*TMath::Tan(temTheta)*TMath::Cos(temPhi);
	Double_t yy=distance*TMath::Tan(temTheta)*TMath::Sin(temPhi);
	if((xx<halfSize)&&(xx>-halfSize)&&(yy<halfSize)&&(yy>-halfSize))
		return kTRUE;
	else 
		return kFALSE;
}