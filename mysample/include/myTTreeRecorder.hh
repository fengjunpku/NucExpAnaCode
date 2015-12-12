#ifndef myTTreeRecorder_h
#define myTTreeRecorder_h 1

#include "globals.hh"
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include "G4ios.hh"
#include <iomanip>

using namespace std;
//instance->openfile->gettree->recorde
class myTTreeRecorder
{
private:
	myTTreeRecorder();
	virtual ~myTTreeRecorder();
public:
	static myTTreeRecorder* Instance();
	void Record();
	void OpenFile(const G4String filename);
	TTree* GetTree();//then operate the tree!!!
	
private:
	TTree *ptree;
	TFile *pfile;
	static myTTreeRecorder* theRecorder;
public:
	double deltaE;
};
#endif
