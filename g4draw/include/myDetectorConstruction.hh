#ifndef myDetectorConstruction_H
#define myDetectorConstruction_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4NistManager.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh" 
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"//for sensitive detector
#include "mySSD.hh"//my SD define class
//#include "mySSD2.hh"
using namespace std;

class myDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    myDetectorConstruction();
    ~myDetectorConstruction();

    G4VPhysicalVolume* Construct();

private:
  //world_para
  G4double fSizeWorld[5];//for tube: rmin,rmax,height,startAngle,spanningAngle
  //Material
  G4Material*           pVacuum;
  G4Material*           pSilicon;
  //world
  G4Box*                pSolidWorld;
  G4LogicalVolume*	     pLogicWorld;
  G4VPhysicalVolume*	 pPhysiWorld;
  //detector
  G4Box*               pSolidSSD;
  G4LogicalVolume*     pLogicSSD;
  G4VPhysicalVolume*   pPhysiSSD;
  //detector2
  G4Box*               pSolidSSD2;
  G4LogicalVolume*     pLogicSSD2;
  G4VPhysicalVolume*   pPhysiSSD2;
};

#endif
