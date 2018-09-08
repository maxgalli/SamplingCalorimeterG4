#include "SCEActionInitialization.hh"
#include "SCEPrimaryGeneratorAction.hh"
#include "SCERunAction.hh"
#include "SCEEventAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCEActionInitialization::SCEActionInitialization(int nenergy, int nlayers)
 : G4VUserActionInitialization()
{
nEnergy = nenergy;
nLayers = nlayers;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCEActionInitialization::~SCEActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SCEActionInitialization::BuildForMaster() const
{
  SetUserAction(new SCERunAction(nEnergy, nLayers));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SCEActionInitialization::Build() const
{
  SetUserAction(new SCEPrimaryGeneratorAction);
  SetUserAction(new SCERunAction(nEnergy, nLayers));
  SetUserAction(new SCEEventAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
