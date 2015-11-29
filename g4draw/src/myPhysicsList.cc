#include "myPhysicsList.hh"

myPhysicsList::myPhysicsList()
{ 
	defaultCutValue=0.1*mm;		//次级粒子产生阈值
	G4int ver=0;				//冗余输出
 	SetVerboseLevel(ver);
	SetCutsWithDefault();

	//Decays
	RegisterPhysics(new G4DecayPhysics("Decay"));
	//RadioactiveDecayPhysics
	RegisterPhysics(new G4RadioactiveDecayPhysics());
	//EM Physics
	RegisterPhysics(new G4EmStandardPhysics(ver,"EM"));
	//Synchroton Radiation & GN Physics
	G4String fState="on";
	G4EmExtraPhysics *pEmPhy=new G4EmExtraPhysics(ver);
	pEmPhy->Synch(fState);
	pEmPhy->GammaNuclear(fState);
	pEmPhy->MuonNuclear(fState);	
	RegisterPhysics(pEmPhy);

 
	
}
myPhysicsList::~myPhysicsList()
{
	
}
