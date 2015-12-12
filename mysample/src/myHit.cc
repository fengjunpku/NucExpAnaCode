#include "myHit.hh"

G4ThreadLocal G4Allocator<myHit>* myHitAllocator;

myHit::myHit()
{
}

myHit::~myHit()
{
}

const myHit& myHit::operator=(const myHit &right)
{
	return *this;
}

G4int myHit::operator==(const myHit &right) const
{
	return 0;
}

void myHit::Print()
{
}
