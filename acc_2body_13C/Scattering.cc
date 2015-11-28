/*
#include "TROOT.h"
#include "TVector3.h"
#include "TMath.h"
#include "TString.h"
#include "TH1.h"
#include "TH2F.h"
#include "TF1.h"
#include "TCanvas.h"

//A(a,b)B

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
*/
//A(a,b)B

#include "Scattering.hh"
Double_t deLoss(Double_t Ek)
{
	////Double_t vv=2*Ek/M_a;
	Double_t beta2=1.-TMath::Power(1/(1+Ek/939.0/M_a),2.);
	Double_t vv=9e16*beta2*1.66055e-27/1.60217e-13;//unit: MeV/u
	//////////
	//Double_t IPart=9.1e-6*Z_A*(1+1.9*TMath::Power(Z_A,2.0/3.0));//MeV
	Double_t IPart=63.6e-6;//MeV
	/////////////
	Double_t partf=1e6*4*TMath::Pi()*Z_a*Z_a*Z_A*rou_A*NA/M_A;//unit:: 1/m3
	Double_t partm=KK*qe*qe*qe*qe/(Me*vv*1.60217e-13);//unit:: C^4/J
	Double_t partb=TMath::Log(2*Me*vv/IPart)-TMath::Log(1-beta2)-beta2;
	return partf*partm*partb/1.60217e-7;//unit::MeV/um
}

void Scattering()
{
	TCanvas *c=new TCanvas("c1","",800,600);
	TH2F *hh=new TH2F("hh","E:theta",300,0,30,50,0,5);
	TF1 *ET=new TF1("ET","[0]+[1]*x+[2]*x*x",0,30);//E(th) @ Ein
	Double_t sTheta=40.0*TMath::Pi()/180.0;
	Double_t Ein=70;
	TVector3 Pin;
	Pin.SetMagThetaPhi(TMath::Sqrt(2*Ein*M_a),0,0);
	cout<<"Energy @ angle: "<<sTheta<<" is :"<<scatterE(Ein,sTheta)/M_a<<endl;
	Double_t x=0;
	while(x<=35)
	{
		Double_t temp=x*TMath::Pi()/180.0;
		hh->Fill(x,scatterE(70,temp)/M_a);
		x+=0.01;
	}
	hh->Fit(ET,"","",0,28.8);
	hh->Draw();
}

Double_t scatterE(Double_t Ein,Double_t sTheta)
{
	Double_t Qvalue=-15.0;
	Double_t part1,part2,part3;
	part1=TMath::Sqrt(M_a*M_b*Ein)*TMath::Cos(sTheta)/(M_B+M_b);
	part2=Ein*(M_B-M_a)/(M_B+M_b)+TMath::Power(part1,2);
	part3=M_B*Qvalue/(M_B+M_b);
	if((part2+part3)>0)
		return TMath::Power((part1+TMath::Sqrt(part2+part3)),2);
	else 
		return -1;
	
}

Double_t LossE(Double_t Ein,Double_t Deff)//Deff :um
{
	Double_t step=0.01;//um
	Double_t range=0;
	Double_t eloss=0;
	Double_t Ere=Ein;
	while((range<=Deff))
	{	
		Double_t tempe=step*deLoss(Ere);
		//if(tempe>0.01) {step/=2;continue;}
		eloss+=tempe;
		Ere-=tempe;
		range+=step;
		//cout<<Ere<<" "<<step<<endl;
	}
	return eloss;
}

Double_t Range(Double_t Ein)
{
	Double_t step=0.01;//um
	Double_t range=0;
	Double_t eloss=0;
	Double_t tempe=100;
	Double_t Ere=Ein;
	while(Ere>1e-6&&tempe>1e-6)
	{
		tempe=step*deLoss(Ere);
		if(tempe>0.01) {step/=2;continue;}
		Ere-=tempe;
		range+=step;
		cout<<range<<" "<<Ere<<endl;
	}
	return range;
}