#include "SCERunAction.hh"
#include "SCEAnalysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCERunAction::SCERunAction(int nenergy, int nlayers, G4String fabsmaterial, double fthick)
        : G4UserRunAction()
{
        nEnergy = nenergy;
        nLayers = nlayers;
        fAbsMaterial = fabsmaterial;
        fThick = fthick;

        // set printing event number per each event
        G4RunManager::GetRunManager()->SetPrintProgress(1);

        // Create analysis manager
        // The choice of analysis technology is done via selectin of a namespace
        // in SCEAnalysis.hh
        auto analysisManager = G4AnalysisManager::Instance();
        G4cout << "Using " << analysisManager->GetType() << G4endl;

        // Create directories
        //analysisManager->SetHistoDirectoryName("histograms");
        //analysisManager->SetNtupleDirectoryName("ntuple");
        analysisManager->SetVerboseLevel(1);
        analysisManager->SetNtupleMerging(true);
        // Note: merging ntuples is available only with Root output

        // Book histograms, ntuple
        //

        for (int i=0; i<nLayers; i++) {
                // Creating histograms
                analysisManager->CreateH1("Eabs" + std::to_string(i),"Edep in absorber", 100, 0., nEnergy*GeV);
                analysisManager->CreateH1("Egap" + std::to_string(i),"Edep in gap", 100, 0., nEnergy*GeV);
                analysisManager->CreateH1("Labs" + std::to_string(i),"trackL in absorber", 100, 0., nEnergy*m);
                analysisManager->CreateH1("Lgap" + std::to_string(i),"trackL in gap", 100, 0., nEnergy*m);

                // Creating ntuple
                //
                analysisManager->CreateNtuple("SCE" + std::to_string(i), "Edep and TrackL");
                analysisManager->CreateNtupleDColumn("Eabs");
                analysisManager->CreateNtupleDColumn("Egap");
                analysisManager->CreateNtupleDColumn("Labs");
                analysisManager->CreateNtupleDColumn("Lgap");
                analysisManager->FinishNtuple();
        }
        // Creating histograms for tot
        analysisManager->CreateH1("Eabs_tot","Edep in absorber", 100, 0., nEnergy*GeV);
        analysisManager->CreateH1("Egap_tot","Edep in gap", 100, 0., nEnergy*GeV);
        analysisManager->CreateH1("Labs_tot","trackL in absorber", 100, 0., nEnergy*m);
        analysisManager->CreateH1("Lgap_tot","trackL in gap", 100, 0., nEnergy*m);

        // Creating ntuple for tot
        //
        analysisManager->CreateNtuple("SCE_tot", "Edep and TrackL");
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
        G4String fileName = "rootfiles/SCExam" + std::to_string(nEnergy) + "GeV" + fAbsMaterial + std::to_string((int)fThick) + "cm";
        analysisManager->OpenFile(fileName);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SCERunAction::EndOfRunAction(const G4Run* /*run*/)
{
        // print histogram statistics
        //
        auto analysisManager = G4AnalysisManager::Instance();
        if ( analysisManager->GetH1(nLayers*4+1) ) {
                G4cout << G4endl << " ----> print histograms statistic ";
                if(isMaster) {
                        G4cout << "for the entire run " << G4endl << G4endl;
                }
                else {
                        G4cout << "for the local thread " << G4endl << G4endl;
                }

                G4cout << " EAbs : mean = "
                        << G4BestUnit(analysisManager->GetH1(nLayers*4)->mean(), "Energy")
                        << " rms = "
                        << G4BestUnit(analysisManager->GetH1(nLayers*4)->rms(),  "Energy") << G4endl;

                G4cout << " EGap : mean = "
                        << G4BestUnit(analysisManager->GetH1(nLayers*4+1)->mean(), "Energy")
                        << " rms = "
                        << G4BestUnit(analysisManager->GetH1(nLayers*4+1)->rms(),  "Energy") << G4endl;

                G4cout << "Total mean energy deposited: "
                        << G4BestUnit(analysisManager->GetH1(nLayers*4)->mean() + analysisManager->GetH1(nLayers*4+1)->mean(), "Energy")
                        << G4endl;

                G4cout << "Energy resolution: "
                        << G4BestUnit(analysisManager->GetH1(nLayers*4+1)->rms() / analysisManager->GetH1(nLayers*4+1)->mean(), "Energy")
                        << G4endl;

                G4cout << "corresponding to: "
                        << (analysisManager->GetH1(nLayers*4+1)->rms()/analysisManager->GetH1(nLayers*4+1)->mean())*100 << "%" << G4endl;

                G4cout << " LAbs : mean = "
                        << G4BestUnit(analysisManager->GetH1(nLayers*4+2)->mean(), "Length")
                        << " rms = "
                        << G4BestUnit(analysisManager->GetH1(nLayers*4+2)->rms(),  "Length") << G4endl;

                G4cout << " LGap : mean = "
                        << G4BestUnit(analysisManager->GetH1(nLayers*4+3)->mean(), "Length")
                        << " rms = "
                        << G4BestUnit(analysisManager->GetH1(nLayers*4+3)->rms(),  "Length") << G4endl;
        }

        // Open text file fo write means for later analysis
        std::ofstream txtfile;
        G4String fileName = "txtfiles/SCExam" + std::to_string(nEnergy) + "GeV" + fAbsMaterial + std::to_string((int)fThick) + "cm" + ".txt";
        txtfile.open(fileName);

        // write to .txt file
        for (int i=0; i<nLayers; i++) {
                txtfile << i << "\t" << analysisManager->GetH1(i*4+3)->mean() << "\t" << analysisManager->GetH1(i*4+1)->mean() << "\n";
        }
        txtfile.close();

        // save histograms & ntuple
        //
        analysisManager->Write();
        analysisManager->CloseFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
