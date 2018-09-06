#include "SCEActionInitialization.hh"
#include "SCEPrimaryGeneratorAction.hh"
#include "SCERunAction.hh"
#include "SCEEventAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCEActionInitialization::SCEActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCEActionInitialization::~SCEActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SCEActionInitialization::BuildForMaster() const
{
  SetUserAction(new SCERunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SCEActionInitialization::Build() const
{
  SetUserAction(new SCEPrimaryGeneratorAction);
  SetUserAction(new SCERunAction);
  SetUserAction(new SCEEventAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
