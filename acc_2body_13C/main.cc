#include "Scattering.cc"
#include "PieceFly.cc"

const Double_t Thickness=2;//um
const Double_t Ex=15.0;
const Double_t Eth=10.7;
void main()
{
	Double_t Ebeam=70;//MeV
	TRandom3 rd(0);
	Double_t Otheta,Ophi;//outging direction
	Otheta=0.;
	TVector3 pout;
	Double_t deff;
	Double_t Eout;
	
	Double_t TOT=100;
	Double_t acc=0;
	
	//TCanvas *c =new TCanvas();
	//TH2F *hh=new TH2F("hh","",280,0,28,140,0,14);
	
	TVector3 vHeavy(0.4,0,1),vLight(0.5,0,1);
	
	while(Otheta<28.6)
	{
		Double_t count=0;
		Double_t angle=Otheta*TMath::Pi()/180.;
		Eout=scatterE(Ebeam,angle);
		pout.SetMagThetaPhi(TMath::Sqrt(2*M_a*Eout),Otheta,0);
		for(Int_t i=0;i<TOT;i++)
		{
			//Double_t rand=rd.Rndm();
			//deff=Thickness*(rand/TMath::Cos(angle)+1-rand);
			//Ophi=0;//rd.Uniform(0,2*TMath::Pi());
			
			//Eout=scatterE(Ebeam,angle);//-LossE(Ebeam,deff);
			//pout.SetMagThetaPhi(TMath::Sqrt(2*M_a*Eout),Otheta,Ophi);		
			
			Vpiece(pout,4.3,vHeavy,vLight);
			if(isHit(vHeavy,vLight))
			{
				count+=1.;
			}
			
			//if(Otheta<0.1) hh->Fill(vLight.Theta()/TMath::Pi()*180,vHeavy.Theta()/TMath::Pi()*180);
		}
		//if(Otheta<0.1) hh->Draw("colz");
		acc=count/TOT;
		cout<<"Angle: "<<Otheta<<";  acc: "<<acc<<";"<<endl;
		Otheta+=0.1;
	}
}

Double_t GetCrossSection(Double_t tangle)
{
	return 1;
}

Bool_t isHit(TVector3 vel1,TVector3 vel2)
{
	Double_t posDis=15;//cm
	Double_t posTheta=20;//degree
	Double_t posHalf=2.5;//cm
	Bool_t isIn1,isIn2;
	
	vel1.RotateY(-1*posTheta*TMath::Pi()/180.0);
	Double_t xx1=posDis*TMath::Tan(vel1.Theta())*TMath::Cos(vel1.Phi());
	Double_t yy1=posDis*TMath::Tan(vel1.Theta())*TMath::Sin(vel1.Phi());
	if((xx1<posHalf)&&(xx1>-1*posHalf)&&(yy1<posHalf)&&(yy1>-1*posHalf))
		isIn1=kTRUE;
	else isIn1=kFALSE;
	
	vel2.RotateY(-1*posTheta*TMath::Pi()/180.0);
	Double_t xx2=posDis*TMath::Tan(vel2.Theta())*TMath::Cos(vel2.Phi());
	Double_t yy2=posDis*TMath::Tan(vel2.Theta())*TMath::Sin(vel2.Phi());
	if((xx2<posHalf)&&(xx2>-1*posHalf)&&(yy2<posHalf)&&(yy2>-1*posHalf))
		isIn2=kTRUE;
	else isIn2=kFALSE;
	
	if(isIn1&&isIn2) {//cout<<xx1<<" "<<yy1<<" "<<xx2<<" "<<yy2<<" "<<endl; 
	return kTRUE;}
		else return kFALSE;
}