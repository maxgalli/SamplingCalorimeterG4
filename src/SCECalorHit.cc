#include "SCECalorHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<SCECalorHit>* SCECalorHitAllocator = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCECalorHit::SCECalorHit()
        : G4VHit(),
        fEdep(0.),
        fTrackLength(0.),
        fPos(std::vector<G4ThreeVector>())
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCECalorHit::~SCECalorHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCECalorHit::SCECalorHit(const SCECalorHit& right)
        : G4VHit()
{
        fEdep        = right.fEdep;
        fTrackLength = right.fTrackLength;
        fPos       = right.fPos;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const SCECalorHit& SCECalorHit::operator=(const SCECalorHit& right)
{
        fEdep        = right.fEdep;
        fTrackLength = right.fTrackLength;
        fPos       = right.fPos;

        return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int SCECalorHit::operator==(const SCECalorHit& right) const
{
        return ( this == &right ) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SCECalorHit::Print()
{
        G4cout
                << "Edep: "
                << std::setw(7) << G4BestUnit(fEdep,"Energy")
                << " track length: "
                << std::setw(7) << G4BestUnit( fTrackLength,"Length")
                << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
