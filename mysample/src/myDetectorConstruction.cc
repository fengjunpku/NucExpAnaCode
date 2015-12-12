#include "myDetectorConstruction.hh"

myDetectorConstruction::myDetectorConstruction()
{

	//World_para
	fSizeWorld[0]=0.*cm;//rmin
	fSizeWorld[1]=100*cm;//rmax
	fSizeWorld[2]=100*cm;//height
	fSizeWorld[3]=0.*deg;//startAngle
	fSizeWorld[4]=360.*deg;//spanningAngle
}

myDetectorConstruction::~myDetectorConstruction()
{

}

G4VPhysicalVolume* myDetectorConstruction::Construct()
{
//构造材料，方法一
	//Vacuum
	//定义元素，方法一
	//G4Element* H = new G4Element("Hydrogen","H" , 1., 1.);
	//定义元素，方法二
	G4NistManager* man = G4NistManager::Instance();
	G4Element *N = man->FindOrBuildElement("N");
	G4Element *O = man->FindOrBuildElement("O");
	G4Element *Si =man->FindOrBuildElement("Si");

	pVacuum = new G4Material("Vacuum",1.29e-10*mg/cm3,2,kStateGas);//kStateSolid,kStateLiquid
	pSilicon = new G4Material("Silicon",2.32*g/cm3,1,kStateSolid);
	//填充材料，方法一
	pVacuum->AddElement(N, 70.*perCent);
	pVacuum->AddElement(O, 30.*perCent);
	pSilicon->AddElement(Si,100.*perCent);
	//填充材料，方法二
	//pVacuum->AddElement(N, 7);
	//pVacuum->AddElement(O, 3);

//构造材料，方法二
//Air = man->FindOrBuildMaterial("G4_AIR");
	
	//world 
  	pSolidWorld= new G4Tubs("solidWorld",fSizeWorld[0],fSizeWorld[1],0.5*fSizeWorld[2],fSizeWorld[3],fSizeWorld[4]);
  	pLogicWorld= new G4LogicalVolume(pSolidWorld,pVacuum, "logicWorld",0,0,0);
  	pPhysiWorld= new G4PVPlacement(0,G4ThreeVector(0,0,0),pLogicWorld,"physiWorld",0,false,0);

	//SSD
	G4RotationMatrix *rot=new G4RotationMatrix();
	rot->rotateX(90*deg);	//迎着转动轴方向，顺时针为正,与3D相反
	G4ThreeVector tran(0.,0.,0.);//translation
	//G4Box *pSolidBox= new G4Box("solidBox",0.5*10.*cm,0.5*10.*cm,0.5*1000.*um);
	pSolidSSD = new G4Box("solidSSD",0.5*10.*cm,0.5*10.*cm,0.5*20.*um);
	//G4LogicalVolume *pLogicpBox= new G4LogicalVolume(pSolidBox,pSi, "logicBox",0,0,0);
	pLogicSSD = new G4LogicalVolume(pSolidSSD,pSilicon,"logicSSD",0,0,0,true);
	//last4: filed,senvitiveDetector,uesrlimit,Optimise;
	//G4PVPlacement *pPhysiBox= new G4PVPlacement(ro,tr,pLogicpBox,"physiBox",pLogicWorld,false,0);//last 0 copyID
	//	G4PVPlacement *pPhysiBox2= new G4PVPlacement(G4Transform3D(*ro,tr),pLogicpBox,"physiBox",pLogicWorld,false,1,true);
	pPhysiSSD = new G4PVPlacement(rot,tran,pLogicSSD,"physiSSD",pLogicWorld,false,0);//last3: motherlogi, pMany, copyNo

	//SSD2
	G4ThreeVector tran2(0.,10.*cm,0.);
	pSolidSSD2 = new G4Box("solidSSD2",0.5*10.*cm,0.5*10.*cm,0.5*500.*um);
	pLogicSSD2 = new G4LogicalVolume(pSolidSSD2,pSilicon,"logicSSD2",0,0,0,true);
	pPhysiSSD2 = new G4PVPlacement(rot,tran2,pLogicSSD2,"physiSSD2",pLogicWorld,false,0);//last3: motherlogi, pMany, copyNo
	//-------------------------sensitive-detector---------------------
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
	G4String SDnameSSD="my/SSD";
	mySSD* pSensiSSD = new mySSD(SDnameSSD);
	SDman->AddNewDetector(pSensiSSD);
	pLogicSSD->SetSensitiveDetector(pSensiSSD);
	/////////////
	//mySSD2* pSensiSSD2 = new mySSD2("my/SSD2");
	//SDman->AddNewDetector(pSensiSSD2);
	//pLogicSSD2->SetSensitiveDetector(pSensiSSD2);
	//----------------VIS-----------------
	G4VisAttributes *pSSDVisAtt = new G4VisAttributes(G4Colour::Blue());
	G4VisAttributes *pWorldVisAtt = new G4VisAttributes(G4Colour::Yellow());
	pLogicWorld->SetVisAttributes(pWorldVisAtt);
	pLogicSSD->SetVisAttributes(pSSDVisAtt);
	//------end-----------------
	return pPhysiWorld;

}
