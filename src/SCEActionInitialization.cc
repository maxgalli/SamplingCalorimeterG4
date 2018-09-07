#include "SCEActionInitialization.hh"
#include "SCEPrimaryGeneratorAction.hh"
#include "SCERunAction.hh"
#include "SCEEventAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCEActionInitialization::SCEActionInitialization(int nenergy)
 : G4VUserActionInitialization()
{
nEnergy = nenergy;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCEActionInitialization::~SCEActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SCEActionInitialization::BuildForMaster() const
{
  SetUserAction(new SCERunAction(nEnergy));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SCEActionInitialization::Build() const
{
  SetUserAction(new SCEPrimaryGeneratorAction);
  SetUserAction(new SCERunAction(nEnergy));
  SetUserAction(new SCEEventAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
