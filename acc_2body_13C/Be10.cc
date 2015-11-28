#include "TROOT.h"
#include "TVector3.h"
#include "TMath.h"
#include "TString.h"
#include "TH1.h"
#include "TH2F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TGraph.h"

const Double_t m0=10.;
const Double_t ml=4.;
const Double_t mh=6.;
//9Be(9Be,10Be)8Be
const Double_t M_a=9.0;//beam
const Double_t M_A=9.0;//target
const Double_t M_b=10.0;//out
const Double_t M_B=8.0;//recoil
const Double_t Me=0.511/939;//elec:u
const Int_t Z_a=4;
const Int_t Z_A=4;
const Double_t NA=6.022e23;
const Double_t qe=1.60217e-19;//unit:C
const Double_t KK=81e18;//  JingDianLi Const ^2

const Double_t Thickness=2;//um
const Double_t Ex=15.0;
const Double_t Eth=10.7;

const Double_t PIE=TMath::Pi();

void Be10()
{
	TCanvas *c1 = new TCanvas("c1","Dis of Piece",800,600);
	//TH2F *hh = new TH2F("hh","Dis",30,-3,3,30,-3,3);
	TGraph *gr= new TGraph();Int_t gn=0;
	//
	Double_t Ebeam=45;//MeV
	TRandom3 rd(0);
	Double_t Otheta,Ophi;//outging direction
	Otheta=0.;
	TVector3 pout;
	Double_t deff;
	Double_t Eout;
	
	Double_t TOT=1000;
	Double_t count;
	Double_t acc=0;
	
	TVector3 vHeavy,vLight,plcms,phcms;
	Double_t Pcms,phi,theta;
	TRandom3 ran(0);
	while(Otheta<28.6)
	{
		count=0.;
		Double_t angle=Otheta*PIE/180.;
		Eout=scatterE(Ebeam,angle);
		//Eout=(4.02216+0.0245759*Otheta-0.00375997*Otheta*Otheta)*M_a;
		
		for(Int_t i=0;i<TOT;i++)
		{
			Ophi=0;//2*PIE*ran.Uniform();
			pout.SetMagThetaPhi(TMath::Sqrt(2*m0*Eout),angle,Ophi);
			//Vpiece(pout,4.3,vHeavy,vLight);
			////////////////////
			Pcms=TMath::Sqrt(2*0.13*ml*mh/m0);
			phi=2*PIE*ran.Uniform();
			theta=TMath::ACos(2*ran.Uniform()-1);
			plcms.SetMagThetaPhi(Pcms,theta,phi);
			phcms=-plcms;
		
			vHeavy=1.0/m0*pout+1.0/mh*phcms;
			vLight=1.0/m0*pout+1.0/ml*plcms;
			///////////////
			
			//if(isHit(vHeavy,vLight)) count+=1.;
			vHeavy.RotateY(PIE/-9.);
			vLight.RotateY(PIE/-9.);
			Double_t x1,y1,x2,y2;
			Double_t theta1,phi1,theta2,phi2;
			theta1=vHeavy.Theta();theta2=vLight.Theta();
			phi1=vHeavy.Phi();phi2=vLight.Phi();
			x1=10*TMath::Tan(theta1)*TMath::Cos(phi1);
			y1=10*TMath::Tan(theta1)*TMath::Sin(phi1);
			x2=10*TMath::Tan(theta2)*TMath::Cos(phi2);
			y2=10*TMath::Tan(theta2)*TMath::Sin(phi2);
			//////////////
			if(x1<2.5&&x1>-2.5&&y1<2.5&&y1>-2.5&&x2<2.5&&x2>-2.5&&y2<2.5&&y2>-2.5)
			{
				//hh->Fill(x2,y2);
				//cout<<x1<<" "<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<endl;
				count+=1.;
			}
		}
		acc=count/TOT;
		gr->SetPoint(gn,Otheta,acc);gn++;
		//cout<<"Angle: "<<Otheta<<";  acc: "<<acc<<";"<<endl;
		Otheta+=0.5;
		
	}
	//hh->Draw("colz");
	gr->Draw("AP*");
	
}

Double_t scatterE(Double_t Ein,Double_t sTheta)
{
	
	Double_t Qvalue=-2.39;
	Double_t part1,part2,part3;
	part1=TMath::Sqrt(M_a*M_b*Ein)*TMath::Cos(sTheta)/(M_B+M_b);
	part2=Ein*(M_B-M_a)/(M_B+M_b)+TMath::Power(part1,2);
	part3=M_B*Qvalue/(M_B+M_b);
	if((part2+part3)>0)
		return TMath::Power((part1+TMath::Sqrt(part2+part3)),2);
	else 
		return -1;
	
	//return (4.02216+0.0245759*sTheta-0.00375997*sTheta*sTheta)*M_a;
}
