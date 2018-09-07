#ifndef SCEDetectorConstruction_h
#define SCEDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;

/// Detector construction class to define materials and geometry.
/// The calorimeter is a box made of a given number of layers. A layer consists
/// of an absorber plate and of a detection gap. The layer is replicated.
///
/// Four parameters define the geometry of the calorimeter :
///
/// - the thickness of an absorber plate,
/// - the thickness of a gap,
/// - the number of layers,
/// - the transverse size of the calorimeter (the input face is a square).
///
/// In ConstructSDandField() sensitive detectors of SCECalorimeterSD type
/// are created and associated with the Absorber and Gap volumes.

class SCEDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    SCEDetectorConstruction(int fnlayers, G4String fabsmat, int factthick);
    virtual ~SCEDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

  private:
    // methods
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();

    // data members
    G4bool fCheckOverlaps; // option to activate checking of volumes overlaps
    G4int fNofLayers;     // number of layers
    G4String fAbsMaterial;
    G4int fActThickness;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

