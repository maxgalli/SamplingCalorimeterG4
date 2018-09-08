#include "SCEEventAction.hh"
#include "SCECalorimeterSD.hh"
#include "SCECalorHit.hh"
#include "SCEAnalysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCEEventAction::SCEEventAction()
        : G4UserEventAction(),
        fAbsHCID(-1),
        fGapHCID(-1)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCEEventAction::~SCEEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCECalorHitsCollection*
SCEEventAction::GetHitsCollection(G4int hcID,
                const G4Event* event) const
{
        auto hitsCollection
                = static_cast<SCECalorHitsCollection*>(
                                event->GetHCofThisEvent()->GetHC(hcID));

        if ( ! hitsCollection ) {
                G4ExceptionDescription msg;
                msg << "Cannot access hitsCollection ID " << hcID;
                G4Exception("SCEEventAction::GetHitsCollection()",
                                "MyCode0003", FatalException, msg);
        }

        return hitsCollection;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SCEEventAction::PrintEventStatistics(
                G4double absoEdep, G4double absoTrackLength,
                G4double gapEdep, G4double gapTrackLength) const
{
        // print event statistics
        G4cout
                << "   Absorber: total energy: "
                << std::setw(7) << G4BestUnit(absoEdep, "Energy")
                << "       total track length: "
                << std::setw(7) << G4BestUnit(absoTrackLength, "Length")
                << G4endl
                << "        Gap: total energy: "
                << std::setw(7) << G4BestUnit(gapEdep, "Energy")
                << "       total track length: "
                << std::setw(7) << G4BestUnit(gapTrackLength, "Length")
                << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SCEEventAction::BeginOfEventAction(const G4Event* /*event*/)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SCEEventAction::EndOfEventAction(const G4Event* event)
{
        // Get hits collections IDs (only once)
        if ( fAbsHCID == -1 ) {
                fAbsHCID
                        = G4SDManager::GetSDMpointer()->GetCollectionID("AbsorberHitsCollection");
                fGapHCID
                        = G4SDManager::GetSDMpointer()->GetCollectionID("GapHitsCollection");
        }

        // Get hits collections
        auto absoHC = GetHitsCollection(fAbsHCID, event);
        auto gapHC = GetHitsCollection(fGapHCID, event);

        // Get hit with total values
        auto absoHit = (*absoHC)[absoHC->entries()-1];
        auto gapHit = (*gapHC)[gapHC->entries()-1];

        // Print per event (modulo n)
        //
        auto eventID = event->GetEventID();
        auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
        if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
                G4cout << "---> End of event: " << eventID << G4endl;

                PrintEventStatistics(
                                absoHit->GetEdep(), absoHit->GetTrackLength(),
                                gapHit->GetEdep(), gapHit->GetTrackLength());
        }

        // Fill histograms, ntuple
        //

        // get analysis manager
        auto analysisManager = G4AnalysisManager::Instance();

        int id = 0;
        int id_tup = 0;
        double abso_lenght = 0;
        double gap_lenght = 0;
        for (int i=0; i<absoHC->entries(); i++) {
                absoHit = (*absoHC)[i];
                gapHit = (*gapHC)[i];
                abso_lenght += absoHit->GetTrackLength();
                gap_lenght += gapHit->GetTrackLength();
                // fill histograms
                analysisManager->FillH1(id, absoHit->GetEdep());
                analysisManager->FillH1(id + 1, gapHit->GetEdep());
                if (i!=0 && i<(absoHC->entries()-1)) {
                        analysisManager->FillH1(id + 2, abso_lenght);
                        analysisManager->FillH1(id + 3, gap_lenght);
                }
                else {
                        analysisManager->FillH1(id + 2, absoHit->GetTrackLength());
                        analysisManager->FillH1(id + 3, gapHit->GetTrackLength());
                }
                // fill ntuple
                analysisManager->FillNtupleDColumn(i, id_tup, absoHit->GetEdep());
                analysisManager->FillNtupleDColumn(i, id_tup + 1, gapHit->GetEdep());
                analysisManager->FillNtupleDColumn(i, id_tup + 2, absoHit->GetTrackLength());
                analysisManager->FillNtupleDColumn(i, id_tup + 3, gapHit->GetTrackLength());
                analysisManager->AddNtupleRow(i);

                id += 4;
        }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
