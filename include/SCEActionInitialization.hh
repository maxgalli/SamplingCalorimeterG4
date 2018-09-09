#ifndef SCEActionInitialization_h
#define SCEActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

// include here otherwise it doesn't compile
#include "G4Types.hh"
#include "G4String.hh"

/// Action initialization class.
///

class SCEActionInitialization : public G4VUserActionInitialization
{
  public:
    SCEActionInitialization(int nenergy, int nlayers, G4String fabsmaterial, double fthick);
    virtual ~SCEActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
    int nEnergy;
    int nLayers;
    G4String fAbsMaterial;
    double fThick;
};

#endif


