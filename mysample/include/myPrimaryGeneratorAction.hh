#ifndef myPrimaryGeneratorAction_h
#define myPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include <cmath>
#include <string>
#include <iostream>
#include <cstdio>
//#include <cstdlib>

//class G4ParticleGun;
//class G4Event;

class myPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    myPrimaryGeneratorAction();
    ~myPrimaryGeneratorAction();

public:
	void GeneratePrimaries(G4Event* anEvent);
	G4double GetRandomEnergy();
	G4ThreeVector GetRandomVector();
	G4ParticleDefinition *GetParticle();
private:
    G4ParticleGun* particleGun;
	G4ParticleTable* particleTable;
	G4IonTable* ionTable;
};

#endif
