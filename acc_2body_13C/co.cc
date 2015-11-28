#include "TROOT.h"
#include "TVector3.h"
#include "TMath.h"
#include "TString.h"
#include "TH1.h"
#include "TH2F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "time.h"
const Double_t m0=13.;
const Double_t ml=4.;
const Double_t mh=9.;

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
//
const Double_t Thickness=2;//um
const Double_t Ex=15.0;
const Double_t Eth=10.7;
const Double_t Ecos=Ex-Eth;
const Double_t PIE=TMath::Pi();

//
const Double_t halfSize=2.5;//cm
const Double_t distance=10.;//cm
const Double_t posAngle=20.*PIE/180.;//rd
//
void co()
{
	TCanvas *c1 = new TCanvas("c1","Dis of Piece",800,600);
	//TH2F *hh = new TH2F("hh","Dis",200,0,20,300,0,30);
	TGraph *gr= new TGraph();Int_t gn=0;
	//
	Double_t Ebeam=70;//MeV
	TRandom3 rd(0);
	Double_t Otheta,Ophi;//outging direction
	Otheta=0.;
	TVector3 pout(1,0,0);
	Double_t deff;
	Double_t Eout;
	
	Double_t TOT=1000000;
	Double_t count,realTOT;
	Double_t acc=0;
	
	TVector3 vHeavy,vLight,plcms,phcms;
	Double_t Pcms,phi,theta;
	TRandom3 rand[4];
	//
	Int_t timer=(Int_t)time(0);
	for(Int_t ii=0;ii<3;ii++)
	{
		rand[ii].SetSeed(timer+ii);
	}
	//
	while(Otheta<28.6)
	{
		count=0.;
		realTOT=0.;
		Double_t angle=Otheta*PIE/180.;
		Eout=scatterE(Ebeam,angle);
		//Eout=(4.02216+0.0245759*Otheta-0.00375997*Otheta*Otheta)*M_a;
		pout.SetMag(1);
		pout.SetTheta(angle);
		
		for(Int_t i=0;i<TOT;i++)
		{
			Ophi=2*PIE*rand[0].Rndm();
			pout.SetPhi(Ophi);
			pout.SetMag(TMath::Sqrt(2*m0*Eout));
			if(!notHit(pout)) realTOT+=1.;
			//Vpiece(pout,4.3,vHeavy,vLight);
			////////////////////
			Pcms=TMath::Sqrt(2*Ecos*ml*mh/m0);
			phi=2*PIE*rand[1].Uniform();
			theta=TMath::ACos(2*rand[2].Uniform()-1);
			plcms.SetMagThetaPhi(Pcms,theta,phi);
			phcms=-plcms;
		
			vHeavy=1.0/m0*pout+1.0/mh*phcms;
			vLight=1.0/m0*pout+1.0/ml*plcms;
			///////////////
			
			//if(isHit(vHeavy,vLight)) count+=1.;
			vHeavy.RotateY(-posAngle);
			vLight.RotateY(-posAngle);
			Double_t x1,y1,x2,y2;
			Double_t theta1,phi1,theta2,phi2;
			theta1=vHeavy.Theta();theta2=vLight.Theta();
			phi1=vHeavy.Phi();phi2=vLight.Phi();
			x1=distance*TMath::Tan(theta1)*TMath::Cos(phi1);
			y1=distance*TMath::Tan(theta1)*TMath::Sin(phi1);
			x2=distance*TMath::Tan(theta2)*TMath::Cos(phi2);
			y2=distance*TMath::Tan(theta2)*TMath::Sin(phi2);
			//////////////
			if((TMath::Abs(x1)<halfSize)&&(TMath::Abs(y1)<halfSize)&&(TMath::Abs(x2)<halfSize)&&(TMath::Abs(y2)<halfSize))
			//if(x1<2.5&&x1>-2.5&&y1<2.5&&y1>-2.5&&x2<2.5&&x2>-2.5&&y2<2.5&&y2>-2.5)
			{
				//hh->Fill(theta1*180/PIE,theta2*180/PIE);
				//cout<<x1<<" "<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<endl;
				count+=1.;
			}
		}
		if(realTOT) acc=count/realTOT;//cout<<Otheta<<" "<<realTOT<<endl;
		else acc=0;
		gr->SetPoint(gn,Otheta,acc);gn++;
		//cout<<"Angle: "<<Otheta<<";  acc: "<<acc<<";"<<endl;
		Otheta+=0.5;
		
	}
	//hh->Draw("colz");
	gr->Draw("AP*");
	
}

Double_t scatterE(Double_t Ein,Double_t sTheta)
{
	
	Double_t Qvalue=0-Ex;
	Double_t part1,part2,part3;
	part1=TMath::Sqrt(M_a*M_b*Ein)*TMath::Cos(sTheta)/(M_B+M_b);
	part2=Ein*(M_B-M_a)/(M_B+M_b)+TMath::Power(part1,2);
	part3=M_B*Qvalue/(M_B+M_b);
	if((part2+part3)>0)
		return TMath::Power((part1+TMath::Sqrt(part2+part3)),2);
	else 
		return -1;
}
/*
void Vpiece(TVector3 p0,Double_t Ecos,TVector3 &Heavy,TVector3 &Light)
{
	//
	TRandom3 rdd(0);
	Double_t Pcms=TMath::Sqrt(2*Ecos*ml*mh/m0);
	TVector3 plcms,phcms;
	
	Double_t phi=rdd.Uniform(0,2*PIE);
	Double_t theta=TMath::ACos(2*rdd.Uniform()-1);
	plcms.SetMagThetaPhi(Pcms,theta,phi);
	phcms=-1*plcms;
		
	Heavy=1.0/m0*p0+1.0/mh*phcms;
	Light=1.0/m0*p0+1.0/ml*plcms;
}

Bool_t isHit(TVector3 vel1,TVector3 vel2)
{
	Double_t posDis=15;//cm
	Double_t posTheta=20;//degree
	Double_t posHalf=2.5;//cm
	Bool_t isIn1,isIn2;
	
	vel1.RotateY(0-posTheta*PIE/180.0);
	Double_t xx1=posDis*TMath::Tan(vel1.Theta())*TMath::Cos(vel1.Phi());
	Double_t yy1=posDis*TMath::Tan(vel1.Theta())*TMath::Sin(vel1.Phi());
	if((xx1<posHalf)&&(xx1>-1*posHalf)&&(yy1<posHalf)&&(yy1>-1*posHalf))
		isIn1=kTRUE;
	else isIn1=kFALSE;
	
	vel2.RotateY(0-posTheta*PIE/180.0);
	Double_t xx2=posDis*TMath::Tan(vel2.Theta())*TMath::Cos(vel2.Phi());
	Double_t yy2=posDis*TMath::Tan(vel2.Theta())*TMath::Sin(vel2.Phi());
	if((xx2<posHalf)&&(xx2>-1*posHalf)&&(yy2<posHalf)&&(yy2>-1*posHalf))
		isIn2=kTRUE;
	else isIn2=kFALSE;
	
	if(isIn1&&isIn2) {//cout<<xx1<<" "<<yy1<<" "<<xx2<<" "<<yy2<<" "<<endl; 
	return kTRUE;}
		else return kFALSE;
}
*/

Bool_t notHit(TVector3 vel)
{
	vel.RotateY(-posAngle);
	
	Double_t temTheta=vel.Theta();
	Double_t temPhi=vel.Phi();
	
	Double_t xx=distance*TMath::Tan(temTheta)*TMath::Cos(temPhi);
	Double_t yy=distance*TMath::Tan(temTheta)*TMath::Sin(temPhi);
	if((xx<halfSize)&&(xx>-halfSize)&&(yy<halfSize)&&(yy>-halfSize))
		return kFALSE;
	else 
		return kTRUE;
}