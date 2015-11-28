/*
#include "TROOT.h"
#include "TVector3.h"
#include "TMath.h"
#include "TString.h"
#include "TH1.h"
#include "TCanvas.h"
const Double_t m0=13.;
const Double_t ml=4.;
const Double_t mh=9.;
*/
#include "PieceFly.hh"

void PieceFly()
{
	TCanvas *c1 = new TCanvas("c1","Dis of Piece",800,600);
	TH1F *h1 = new TH1F("h1","Dis",300,0,30);
	TH1F *h2 = new TH1F("h2","",300,0,30);
	TH2F *hh = new TH2F("hh","Dis",120,0,12,280,0,28);
	//
	Double_t Ecms=50;
	Double_t Ex=15;
	Double_t Eth=10.7;
	Double_t Ecos=Ex-Eth;
	TVector3 p0;
	p0.SetMagThetaPhi(TMath::Sqrt(2*m0*Ecms),0,0);
	//
	DisOfHP(p0,Ecos);
	
}

void DisOfHP(TVector3 p0,Double_t Ecos)
{
	Double_t thl=0;
	Double_t thh=0;
	//
	TRandom3 rd(0);
	Double_t Pcms=TMath::Sqrt(2*Ecos*ml*mh/m0);
	TVector3 plcms,phcms;
	for(Int_t i=0;i<100000;i++)
	{
		Double_t phi=rd.Uniform(0,2*TMath::Pi());
		Double_t theta=TMath::ACos(2*rd.Uniform()-1);
		plcms.SetMagThetaPhi(Pcms,theta,phi);
		phcms.SetMagThetaPhi(Pcms,TMath::Pi()-theta,phi+TMath::Pi());
	
		Double_t tem1=(1.0/m0*p0+1.0/ml*plcms).Theta();
		Double_t tem2=(1.0/m0*p0+1.0/mh*phcms).Theta();
		//h1->Fill(tem1/TMath::Pi()*180);
		//h2->Fill(tem2/TMath::Pi()*180);
		hh->Fill(tem2/TMath::Pi()*180,tem1/TMath::Pi()*180);
		if(tem1>thl) thl=tem1;
		if(tem2>thh) thh=tem2;
	}
	//h1->Draw();
	//h2->Draw("Same");
	hh->Draw("colz");
	//cout<<"Max Light Piece Angle: "<<thl/TMath::Pi()*180<<endl;
}

void Vpiece(TVector3 p0,Double_t Ecos,TVector3 &Heavy,TVector3 &Light)
{
	
	//
	TRandom3 rdd(0);
	Double_t Pcms=TMath::Sqrt(2*Ecos*ml*mh/m0);
	TVector3 plcms,phcms;
	
	Double_t phi=rdd.Uniform(0,2*TMath::Pi());
	Double_t theta=TMath::ACos(2*rdd.Uniform()-1);
	plcms.SetMagThetaPhi(Pcms,theta,phi);
	phcms.SetMagThetaPhi(Pcms,TMath::Pi()-theta,phi+TMath::Pi());
		
	//Double_t tem1=(1.0/m0*p0+1.0/ml*plcms).Theta();
	//Double_t tem2=(1.0/m0*p0+1.0/mh*phcms).Theta();
	
	Heavy=1.0/m0*p0+1.0/mh*phcms;
	Light=1.0/m0*p0+1.0/ml*plcms;
}
