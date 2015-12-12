#include "myEventAction.hh"
#include "myHit.hh"
#include "myAnalysis.hh"
#include "myTTreeRecorder.hh"

myEventAction::myEventAction()
{;}

myEventAction::~myEventAction()
{;}

void myEventAction::BeginOfEventAction(const G4Event*)
{;}

void myEventAction::EndOfEventAction(const G4Event* evt)
{
	G4double totE=0.;
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
	G4String colNam;
	SSDcolID = SDman->GetCollectionID(colNam="SSDcollection");//set the same collection_name in DectectorConstruction!!!!!
	
	G4HCofThisEvent* HCE=evt->GetHCofThisEvent();
	myHitsCollection* myHC=0;//this HC only for SSD
	if(HCE) myHC=(myHitsCollection*)(HCE->GetHC(SSDcolID));
	if(myHC)
	{
		G4int nhits = myHC->entries();
		
		G4cout<<"  "<<nhits<<" hits in this event."<<G4endl;
		totE=0;
		for(G4int i=0;i<nhits;i++)
		{
			totE+=(*myHC)[i]->GetDeltaE();
		}

		G4cout<<"Energy in this event ::"<<totE / MeV<<" *MeV"<<G4endl;
	}
	////////////////
	G4AnalysisManager* anaMan = G4AnalysisManager::Instance();
	anaMan->FillH1(1,totE);
	///////////////
	myTTreeRecorder *rec = myTTreeRecorder::Instance();
	rec->deltaE=totE;
	rec->GetTree()->Fill();
}
