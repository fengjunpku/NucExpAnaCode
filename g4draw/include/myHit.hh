#ifndef myHit_h
#define myHit_h 1

#include "globals.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class myHit : public G4VHit
{
public:
	myHit();
	virtual ~myHit();

	//????????????
	const myHit& operator=(const myHit &right);
	G4int operator==(const myHit &right) const;
	//////////////////
	inline void* operator new(size_t);
	inline void  operator delete(void* aHit);
	virtual void Print();

private:
	G4double deltaE;
public:
	inline void SetDeltaE(G4double de){deltaE=de;}
	inline G4double GetDeltaE(){return deltaE;}

};
///////////////////////////////////////
typedef G4THitsCollection<myHit> myHitsCollection;
extern G4ThreadLocal G4Allocator<myHit>* myHitAllocator;

inline void* myHit::operator new(size_t)
{
	if(!myHitAllocator)
		myHitAllocator = new G4Allocator<myHit>;
	return (void*)myHitAllocator->MallocSingle();
}

inline void myHit::operator delete(void* aHit)
{
	myHitAllocator->FreeSingle((myHit*) aHit);
}
//////////////////////////////////////
#endif
