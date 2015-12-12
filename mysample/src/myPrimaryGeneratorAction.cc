#include "myPrimaryGeneratorAction.hh"


myPrimaryGeneratorAction::myPrimaryGeneratorAction()
{
	//particle number
	G4int n_particle = 1;
	particleGun = new G4ParticleGun(n_particle);
	particleTable = G4ParticleTable::GetParticleTable();
	ionTable = G4IonTable::GetIonTable();
}

myPrimaryGeneratorAction::~myPrimaryGeneratorAction()
{
	delete particleGun;
}

void myPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	//方法一
	//G4ParticleTable* pparticleTable=G4ParticleTable::GetParticleTable();
	//G4ParticleDefinition* particle=pparticleTable->FindParticle("alpha");  //"e-","e+","gamma","neutron","proton"
	//方法二
	//G4IonTable *particleTable=G4IonTable::GetIonTable();
	//particleTable->GetIon(2,4,0.0); //alpha
	//方法三
	//particleGun->SetParticleDefinition(G4Alpha::AlphaDefinition())
	particleGun->SetParticleDefinition(GetParticle());
	particleGun->SetParticleCharge(0.);		//EM 物理过程自动修正
	particleGun->SetParticleEnergy(GetRandomEnergy());
	particleGun->SetParticleTime(0.);
	particleGun->SetParticlePosition(G4ThreeVector(0.,-20.*cm,0.));
	particleGun->SetParticleMomentumDirection(GetRandomVector());  
	//particleGun->SetParticleMomentum(G4ParticleMomentum);
	//particleGun->SetParticlePolarization(G4ThreeVector);
	particleGun->GeneratePrimaryVertex(anEvent);
}
//////////////////////////
G4double myPrimaryGeneratorAction::GetRandomEnergy()
{
	G4double Emean=5.42*MeV;
	G4double Esigma=0.008*MeV;
	return CLHEP::RandGauss::shoot(Emean,Esigma);
}
G4ThreeVector myPrimaryGeneratorAction::GetRandomVector()
{
	G4double Pi=3.1415926*rad;
	G4double theta,phi;
	phi=CLHEP::RandFlat::shoot(0.48*Pi,0.52*Pi);
	theta=CLHEP::RandFlat::shoot(0.48*Pi,0.52*Pi);
	G4double x,y,z;
	x=sin(theta)*cos(phi);
	y=sin(theta)*sin(phi);
	z=cos(theta);
	return G4ThreeVector(x,y,z);
}
G4ParticleDefinition* myPrimaryGeneratorAction::GetParticle()
{
	double pp=CLHEP::RandFlat::shoot(0.,1.);
	G4ParticleDefinition *particle;
	if(pp<0.3) 
		particle=particleTable->FindParticle("alpha");
	else if(pp<0.4) 
		particle=particleTable->FindParticle("proton");
	else 
		particle=ionTable->GetIon(6,12,0.0);//Z,A,Ex

	return particle;
}
