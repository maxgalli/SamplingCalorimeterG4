#ifndef SCEActionInitialization_h
#define SCEActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.
///

class SCEActionInitialization : public G4VUserActionInitialization
{
  public:
    SCEActionInitialization(int nenergy, int nlayers);
    virtual ~SCEActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
    int nEnergy;
    int nLayers;
};

#endif


