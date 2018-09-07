#include "SCERunAction.hh"
#include "SCEAnalysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCERunAction::SCERunAction(int nenergy)
        : G4UserRunAction()
{

        nEnergy = nenergy;

        // set printing event number per each event
        G4RunManager::GetRunManager()->SetPrintProgress(1);

        // Create analysis manager
        // The choice of analysis technology is done via selectin of a namespace
        // in SCEAnalysis.hh
        auto analysisManager = G4AnalysisManager::Instance();
        G4cout << "Using " << analysisManager->GetType() << G4endl;

        // Create directories
        analysisManager->SetHistoDirectoryName("histograms");
        analysisManager->SetNtupleDirectoryName("ntuple");
        analysisManager->SetVerboseLevel(1);
        analysisManager->SetNtupleMerging(true);
        // Note: merging ntuples is available only with Root output

        // Book histograms, ntuple
        //

        // Creating histograms
        analysisManager->CreateH1("Eabs","Edep in absorber", 100, 0., nEnergy*GeV);
        analysisManager->CreateH1("Egap","Edep in gap", 100, 0., nEnergy*GeV);
        analysisManager->CreateH1("Labs","trackL in absorber", 100, 0., nEnergy*m);
        analysisManager->CreateH1("Lgap","trackL in gap", 100, 0., nEnergy*m);

        // Creating ntuple
        //
        analysisManager->CreateNtuple("SCE", "Edep and TrackL");
        analysisManager->CreateNtupleDColumn("Eabs");
        analysisManager->CreateNtupleDColumn("Egap");
        analysisManager->CreateNtupleDColumn("Labs");
        analysisManager->CreateNtupleDColumn("Lgap");
        analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCERunAction::~SCERunAction()
{
        delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SCERunAction::BeginOfRunAction(const G4Run* /*run*/)
{
        //inform the runManager to save random number seed
        //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

        // Get analysis manager
        auto analysisManager = G4AnalysisManager::Instance();

        // Open an output file
        //
        G4String fileName = "SCExam" + std::to_string(nEnergy) + "GeV";
        analysisManager->OpenFile(fileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SCERunAction::EndOfRunAction(const G4Run* /*run*/)
{
        // print histogram statistics
        //
        auto analysisManager = G4AnalysisManager::Instance();
        if ( analysisManager->GetH1(1) ) {
                G4cout << G4endl << " ----> print histograms statistic ";
                if(isMaster) {
                        G4cout << "for the entire run " << G4endl << G4endl;
                }
                else {
                        G4cout << "for the local thread " << G4endl << G4endl;
                }

                G4cout << " EAbs : mean = "
                        << G4BestUnit(analysisManager->GetH1(0)->mean(), "Energy")
                        << " rms = "
                        << G4BestUnit(analysisManager->GetH1(0)->rms(),  "Energy") << G4endl;

                G4cout << " EGap : mean = "
                        << G4BestUnit(analysisManager->GetH1(1)->mean(), "Energy")
                        << " rms = "
                        << G4BestUnit(analysisManager->GetH1(1)->rms(),  "Energy") << G4endl;

                G4cout << "Total mean energy deposited: "
                        << G4BestUnit(analysisManager->GetH1(0)->mean() + analysisManager->GetH1(1)->mean(), "Energy")
                        << G4endl;

                G4cout << " LAbs : mean = "
                        << G4BestUnit(analysisManager->GetH1(2)->mean(), "Length")
                        << " rms = "
                        << G4BestUnit(analysisManager->GetH1(2)->rms(),  "Length") << G4endl;

                G4cout << " LGap : mean = "
                        << G4BestUnit(analysisManager->GetH1(3)->mean(), "Length")
                        << " rms = "
                        << G4BestUnit(analysisManager->GetH1(3)->rms(),  "Length") << G4endl;
        }

        // save histograms & ntuple
        //
        analysisManager->Write();
        analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
