#include "myTTreeRecorder.hh"

myTTreeRecorder* myTTreeRecorder::theRecorder=NULL;

myTTreeRecorder::myTTreeRecorder()
{
	//pfile = new TFile(filename,"RECREATE");
	ptree = new TTree("tree","tree");
	ptree->Branch("deltaE",&deltaE,"deltaE/D");
}

myTTreeRecorder::~myTTreeRecorder()
{
}

///////////////////////////////////////
TTree* myTTreeRecorder::GetTree()
{
	return ptree;
}
////////////////////////////////////
void myTTreeRecorder::OpenFile(const G4String filename)
{
	pfile = new TFile(filename,"RECREATE");
	//ptree = new TTree("tree","tree");
}
//////////////////////////
myTTreeRecorder* myTTreeRecorder::Instance()
{
	if(theRecorder==NULL)
		theRecorder = new myTTreeRecorder();
	return theRecorder;
}
/////////////////////////
void myTTreeRecorder::Record()
{
	pfile->cd();
	ptree->Write();
	pfile->Close();
}
