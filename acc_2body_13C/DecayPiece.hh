#ifndef DecayPiece_h
#define DecayPiece_h 1

#include "TH1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TMath.h"
#include "TCutG.h"
#include "TGraph.h"
#include "TRandom1.h"
#include "TCut.h"
#include "TVector3.h"
#include "TString.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "time.h"

using namespace std;

struct fParticle
{
	TString name;
	double mass;
	double Ex;
	double cmKin;
	double labKin;
	TVector3 cmMom;
	TVector3 labMom;
};

class DecayPiece
{
	public:
		DecayPiece();
		virtual ~DecayPiece();
	
		fParticle *pin;
		fParticle *ptar;
		fParticle *pout;
		fParticle *hpiece;
		fParticle *lpiece;
		
		void Inital();
		TF1 *GetCrossDis();
		double GetKinOut(double phi);
		double GetcmDecayAngle();//random in cm
		double GetDecayEnergy();
		double[4] GetcmPieceInfo();//hp E,P; lp E,P
		double[4] GetlabPieceInfo();
		double GetHpAngle();
		double GetLpAngle();
		
	
};
#endif