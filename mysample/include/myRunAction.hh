#ifndef myRunAction_h
#define myRunAction_h 1

#include "myAnalysis.hh"//outputformat
#include "G4ios.hh"
#include "G4Run.hh"
#include "G4UserRunAction.hh"

using namespace std;

class myRunAction : public G4UserRunAction
{
public:
	myRunAction();
	virtual ~myRunAction();

	void BeginOfRunAction(const G4Run* aRun);
	void EndOfRunAction(const G4Run* aRun);

private:
	G4int fRunID;
};

#endif
