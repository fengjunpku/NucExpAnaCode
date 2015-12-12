#include "myRunAction.hh"
#include "G4SystemOfUnits.hh"
#include "myAnalysis.hh"
#include "myTTreeRecorder.hh"

myRunAction::myRunAction():G4UserRunAction()
{
	G4AnalysisManager* anaMan = G4AnalysisManager::Instance();
	anaMan->SetVerboseLevel(1);
	anaMan->SetFirstHistoId(1);
	anaMan->CreateH1("1","Edep in SSD",100,0.,10*MeV);
	/////////////////////////////////////
	myTTreeRecorder *rec = myTTreeRecorder::Instance();
}

myRunAction::~myRunAction()
{
	delete G4AnalysisManager::Instance();
}

void myRunAction::BeginOfRunAction(const G4Run* aRun)
{
	fRunID=aRun->GetRunID();

	G4AnalysisManager* anaMan = G4AnalysisManager::Instance();
	anaMan->OpenFile("myData");
	///////////////////////////	
	myTTreeRecorder *rec = myTTreeRecorder::Instance();
	rec->OpenFile("tree.root");
}

void myRunAction::EndOfRunAction(const G4Run* aRun)
{
	G4AnalysisManager* anaMan = G4AnalysisManager::Instance();
	anaMan->Write();
	anaMan->CloseFile();
	/////////////////
	myTTreeRecorder *rec = myTTreeRecorder::Instance();
	rec->Record();
}
