#ifndef mySSD_h
#define mySSD_h 1

#include "G4Step.hh"
#include "G4HCofThisEvent.hh"
#include "G4VSensitiveDetector.hh"
#include "G4SystemOfUnits.hh"
#include "myHit.hh"//my....

using namespace std;

class mySSD : public G4VSensitiveDetector
{
public:
	mySSD(G4String detector_name);
	virtual ~mySSD();
	virtual void Initialize(G4HCofThisEvent* HCE);
	virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
	virtual void EndOfEvent(G4HCofThisEvent* HCE);

private:
	myHitsCollection* hitsCollection;
	G4int collectionID;
	G4double stepE;
	
};

#endif
