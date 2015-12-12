#include "mySSD.hh"

mySSD::mySSD(G4String detector_name) : G4VSensitiveDetector(detector_name), hitsCollection(0), collectionID(-1)
{
	collectionName.insert("SSDcollection");
}

mySSD::~mySSD()
{
}

void mySSD::Initialize(G4HCofThisEvent* HCE)
{
	if(collectionID<0) collectionID=GetCollectionID(0);
	hitsCollection = new myHitsCollection(SensitiveDetectorName,collectionName[0]);
	HCE->AddHitsCollection(collectionID,hitsCollection);
}

G4bool mySSD::ProcessHits(G4Step* aStep,G4TouchableHistory* ROhist)
{
	myHit* aHit = new myHit();
	//some set methods
	stepE=aStep->GetTotalEnergyDeposit();
	//G4cout<<"  "<<stepE / MeV<<" *MeV"<<endl;
///////////////
	aHit->SetDeltaE(stepE);
	hitsCollection->insert(aHit);
	return true;
}

void mySSD::EndOfEvent(G4HCofThisEvent* HCE)
{

}
