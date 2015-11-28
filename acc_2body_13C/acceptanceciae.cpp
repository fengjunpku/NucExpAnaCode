#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TMath.h>
#include <TCutG.h>
#include <TGraph.h>
#include <TRandom1.h>
#include <TCut.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
using namespace std;

extern float exacceptance(float oexenergy);
extern float dwbacrosssection(float dwbatheta[300],float dwbacs[300],float onetheta);
extern float oneexresolution(float exdata[100],float resdata[100],float oneex);

void acceptanceciae()
{
    gROOT->cd(); 
	
	delete gDirectory->FindObject("acceptance");
    TCanvas *c2 = new TCanvas("acceptance","acceptance",800,800);
    c2->Draw();
    string pngfile="head";
    string filename="file";
    delete gDirectory->FindObject("acc");
    TH2F *acc=new TH2F("acc","acc",300,0,1.6,1000,0,1);
    
    ofstream fout;
    filename="acceptancebe10.dat";
    fout.open(filename.c_str());
    
    float exenergy[300],resolution[300];
    cout<<"initialization."<<endl;
   for(int i=0;i<100;i++)
   {
       exenergy[i]=0.05+0.01*i;
       resolution[i]=exacceptance(exenergy[i]);      
       acc->Fill(exenergy[i],resolution[i]);
       fout<<i<<"   "<<exenergy[i]<<"   "<<resolution[i]<<endl;
   }
	   acc->SetMarkerStyle(20);
       acc->SetMarkerSize(1);
       pngfile="acceptancebe10.png";
       acc->Draw();
       c2->SaveAs(pngfile.c_str()); 
       fout.close();
}

float exacceptance(float oexenergy){
    TRandom1 r,rg,ra,rb,rc,rd,re,rf,rh;
	int timer;
    float betheta,becs,tsize,inexres,exenergy,normc;
    int rflag=0;
     //DWBA
   float ta,tb,tc,td;
   float dwbatheta[300],dwbacs[300];
   int ppn;
   float exdata[100],resdata[100];
   
   ifstream dwba,ifresa;
   
   dwba.open("be9be9tobe10-lab-13-33.dat");
    for(int j=0;j<90;j++) {
      dwba>>ta>>tb;
      dwbatheta[j]=ta;
      dwbacs[j]=tb;
    }
  
   ifresa.open("exresolution-be10-1.dat");
    for(int j=0;j<100;j++) {
      ifresa>>ppn>>tc>>td;
      exdata[j]=tc;
      resdata[j]=td;
    }
  
    float inexres;
	inexres=oneexresolution(exdata,resdata,oexenergy)/2.355;
    float Q,tthick=16.0,dedxbe9=0.2062,beame,e10be,e8be,betheta,cobetheta,hitspot,normc=8.5;
	float sigmatheta=1.25/180*3.1415926,api=3.1415926;
    float m4He=3723.55,m6He=5571.36;
    float A1,A2,m1,m2,sigmahe4,sigmahe6,mtot,vcm;
    float ot1,ot2,et1,et2,phi1,phi2,cosa1,cosa2,sina1,sina2,ecm1,ecm2,cmom1,cmom2,p1z,p1r,p2z,p2r,pp1,pp2;
    float p1x,p1y,p2x,p2y,ocostheta,ecostheta,theta,exm;
    float bephi,bepz,bepx,bepy,pvcm1,ptcm1,pvcm2,ptcm2;
    float sinphi1,sinphi2,cosphi1,cosphi2,sintheta1,sintheta2;
    float targetx,targety,tradius,tradiusmax=3,targetphi;
	float mean,sigma;
    float count=0,countsame=0,countout=0;
	float targetloss,targetlosshe4,targetlosshe6;
    int total=100000;
    int percent=(int)(total/100),flag=0,npercent=0;
    float dssdcx[16],dssdcy[16],dssdwidth=3,strip=16;
    float dssdz=141.78,tpos=0,hittx=0,hitty=0,ratio; //target
    int hitdssdx[2],hitdssdy[2],hitx[2],hity[2];
  
	
    for(int i=0;i<strip;i++){
      dssdcx[i]=dssdwidth*(i-7)-0.5*dssdwidth;
      dssdcy[i]=dssdwidth*(i-7)-0.5*dssdwidth;
}
//he4,he6
      m1=m4He,m2=m6He;
      A1=4,A2=6;
    
	timer=(int)time(0);
	r.SetSeed(timer+1);
	rg.SetSeed(timer+2);
    ra.SetSeed(timer+3);
	rb.SetSeed(timer+4);
	rc.SetSeed(timer+5);
	rd.SetSeed(timer+6);
	re.SetSeed(timer+7);
	rf.SetSeed(timer+8);
	rh.SetSeed(timer+9);
	

    for(int kkk=0;kkk<total;kkk++){
      exenergy=oexenergy;//相对能+分辨
      ecm1=exenergy*m2/(m1+m2);//相对能的分配
      ecm2=exenergy*m1/(m1+m2);
      cmom1=sqrt(2*ecm1*m1);
      cmom2=sqrt(2*ecm2*m2);
      
      
      //1-st, determine the CM angle of 10Be 
      rflag=-1;
      while(rflag<0){
      betheta=20*r.Rndm()+13;
      becs=ra.Rndm()*normc;//normc为截面值的最大值，这样做来抽样
      if(becs<dwbacrosssection(dwbatheta,dwbacs,betheta))
        rflag=1;
      }
	  
	  cobetheta=betheta-23;//turn the angle from 23 to 0 of the detectors
	  
	  betheta=betheta*api/180;
	  cobetheta=cobetheta*api/180;
	  
	  hitspot=tthick*rh.Rndm();//be9 loss energy in 9be target
      targetloss=hitspot*dedxbe9;
	  beame=45.0-targetloss;
	  
	  Q=-2.26-oexenergy;
	  e10be=pow((2.5*sqrt(2*beame/45.0)*cos(betheta)+sqrt(-2.5*beame/45.0+12.5*cos(betheta)*cos(betheta)*beame/45.0+4*Q/9)),2);
      //e8be=pow((sqrt(10*beame/45.0)*cos(betheta)+sqrt(2.5*beame/45.0+10*cos(betheta)*cos(betheta)*beame/45.0+5*Q/9)),2);// be8 energy
	  vcm=sqrt(2*e10be/(m1+m2));//10be质心系速度
     
    
	//2-nd determine the momentum of the two fragments
      
	  bephi=rb.Rndm()*2*api;
      bepz=cos(cobetheta);
      bepx=sin(cobetheta)*cos(bephi);
      bepy=sin(cobetheta)*sin(bephi);
	  
      //sample->Fill(bephi/2/api);
      phi1=2*api*rc.Rndm();
      phi2=phi1+api;
      if(phi2>2*api)
         phi2=phi2-2*api;

      cosa1=2*(rd.Rndm()-0.5);
      cosa2=-cosa1;
      sina1=sqrt(1-cosa1*cosa1);
      sina2=sqrt(1-cosa2*cosa2);
      pvcm1=vcm*m1+cmom1*cosa1;
      ptcm1=cmom1*sina1;// ptcm1 ?
      pvcm2=vcm*m2+cmom2*cosa2;
      ptcm2=cmom2*sina2;
      p1z=pvcm1*cos(cobetheta)-ptcm1*sin(cobetheta);   //? 
      p2z=pvcm2*cos(cobetheta)-ptcm2*sin(cobetheta);     
      sintheta1=sin(cobetheta)*cosa1+cos(cobetheta)*sina1;
      sintheta2=sin(cobetheta)*cosa2+cos(cobetheta)*sina2;
      sinphi1=sin(bephi)*cos(phi1)+cos(bephi)*sin(phi1);
      sinphi2=sin(bephi)*cos(phi2)+cos(bephi)*sin(phi2);
      cosphi1=cos(bephi)*cos(phi1)-sin(bephi)*sin(phi1);
      cosphi2=cos(bephi)*cos(phi2)-sin(bephi)*sin(phi2); 
      p1x=vcm*m1*bepx+cmom1*sintheta1*cosphi1;
      p1y=vcm*m1*bepy+cmom1*sintheta1*sinphi1;
      p2x=vcm*m2*bepx+cmom2*sintheta2*cosphi2;
      p2y=vcm*m2*bepy+cmom2*sintheta2*sinphi2;

	  //3-rd, the target position 
      tradius=tradiusmax*re.Rndm();
      targetphi=2*api*rf.Rndm();
      targetx=tradius*cos(targetphi);
      targety=tradius*sin(targetphi);
     
      //4-th, hit position in DSSD  
      hitx[0]=dssdz*p1x/p1z+targetx,hity[0]=dssdz*p1y/p1z+targety;
      hitx[1]=dssdz*p2x/p2z+targetx,hity[1]=dssdz*p2y/p2z+targety;
     
	  //5-th, 判断 两个碎片是否击中了两个不同的DSSD像素单元
      for(int i=0;i<2;i++)
	  {
         hitdssdx[i]=-1;
         hitdssdy[i]=-1;
      }
	  
      for(int ii=0;ii<strip;ii++){
         if(abs(hitx[0]-dssdcx[ii])<0.5*dssdwidth)
             hitdssdx[0]=ii;
         if(abs(hity[0]-dssdcy[ii])<0.5*dssdwidth)
             hitdssdy[0]=ii;
          if(abs(hitx[1]-dssdcx[ii])<0.5*dssdwidth)
             hitdssdx[1]=ii;
         if(abs(hity[1]-dssdcy[ii])<0.5*dssdwidth)
             hitdssdy[1]=ii;
      }
     	 
     //9-th, 如果两个碎片在DSSD和CsI中均击中不同的格点单元，则认为探测到
  if((hitdssdx[0]>-1) && (hitdssdx[1]>-1) && (hitdssdy[0]>-1) && (hitdssdy[1]>-1)&&(abs(hitdssdx[0]-hitdssdx[1])+abs(hitdssdy[0]-hitdssdy[1])>0.8) )
    {               
			  count++;
			  cout<<"count"<<count<<endl;
     }
	 
               flag++;
              cout<<"flag"<<flag<<endl;
      if(flag==percent)
	 {
              npercent++;
              flag=0;
     }   
     
}
     ratio=count/total;  
     cout<<"E-rel:"<<oexenergy<<":acceptance:"<<ratio<<endl;
     return(ratio);
      
}

float dwbacrosssection(float dwbatheta[300],float dwbacs[300],float onetheta)
{
      int in;
      float lx1,lx2,ly1,ly2,psx,pcs;
      
      for(int i=0;i<90;i++)
         if ((onetheta>dwbatheta[i])&&(onetheta<dwbatheta[i+1]))
              in=i;
     lx1=dwbatheta[in],lx2=dwbatheta[in+1],psx=onetheta;
     ly1=dwbacs[in],ly2=dwbacs[in+1];
     pcs=(ly2-ly1)/(lx2-lx1)*(psx-lx1)+ly1; 
         return (pcs);
}


float  oneexresolution(float exdata[100],float resdata[100],float oneex)
{
      int in;
	  float temp,aaa,bbb,ccc;
      float lx1,lx2,ly1,ly2,psx,pcs;
      if((exdata[0]-oneex)>-0.1)
         return(resdata[0]);
     else if ((exdata[99]-oneex)<0.1){
		 temp=exp(bbb*log(oneex));
		 return (aaa*temp+ccc);}
     else {
          for(int i=0;i<99;i++)
             if ((oneex>exdata[i])&&(oneex<exdata[i+1]))
                  in=i;
     lx1=exdata[in],lx2=exdata[in+1],psx=oneex;
     ly1=resdata[in],ly2=resdata[in+1];
     pcs=(ly2-ly1)/(lx2-lx1)*(psx-lx1)+ly1; 
         return (pcs);

        }

}