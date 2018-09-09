#include "SCEActionInitialization.hh"
#include "SCEPrimaryGeneratorAction.hh"
#include "SCERunAction.hh"
#include "SCEEventAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCEActionInitialization::SCEActionInitialization(int nenergy, int nlayers, G4String fabsmaterial)
 : G4VUserActionInitialization()
{
nEnergy = nenergy;
nLayers = nlayers;
fAbsMaterial = fabsmaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCEActionInitialization::~SCEActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SCEActionInitialization::BuildForMaster() const
{
  SetUserAction(new SCERunAction(nEnergy, nLayers, fAbsMaterial));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SCEActionInitialization::Build() const
{
  SetUserAction(new SCEPrimaryGeneratorAction);
  SetUserAction(new SCERunAction(nEnergy, nLayers, fAbsMaterial));
  SetUserAction(new SCEEventAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
