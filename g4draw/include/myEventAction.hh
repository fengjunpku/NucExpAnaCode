#ifndef myEventAction_h
#define myEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4VHitsCollection.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

class myEventAction : public G4UserEventAction
{
public:
	myEventAction();
	virtual ~myEventAction();
	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);
private:
	G4double deltaE;
	G4int SSDcolID;
};



#endif
