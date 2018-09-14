#ifndef SCECalorHit_h
#define SCECalorHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Threading.hh"

/// Calorimeter hit class
///
/// It defines data members to store the the energy deposit and track lengths
/// of charged particles in a selected volume:
/// - fEdep, fTrackLength

class SCECalorHit : public G4VHit
{
        public:
                SCECalorHit();
                SCECalorHit(const SCECalorHit&);
                virtual ~SCECalorHit();

                // operators
                const SCECalorHit& operator=(const SCECalorHit&);
                G4int operator==(const SCECalorHit&) const;

                inline void* operator new(size_t);
                inline void  operator delete(void*);

                // methods from base class
                virtual void Draw() {}
                virtual void Print();

                // methods to handle data
                void Add(G4double de, G4double dl);

                // get methods
                G4double GetEdep() const;
                G4double GetTrackLength() const;
                std::vector<G4ThreeVector> GetPos();

                // set pos
                void SetPos(G4ThreeVector xyz) {
                        fPos.push_back(xyz);
                }

        private:
                G4double fEdep;        ///< Energy deposit in the sensitive volume
                G4double fTrackLength; ///< Track length in the  sensitive volume
                std::vector<G4ThreeVector> fPos;


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

using SCECalorHitsCollection = G4THitsCollection<SCECalorHit>;

extern G4ThreadLocal G4Allocator<SCECalorHit>* SCECalorHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* SCECalorHit::operator new(size_t)
{
        if (!SCECalorHitAllocator) {
                SCECalorHitAllocator = new G4Allocator<SCECalorHit>;
        }
        void *hit;
        hit = (void *) SCECalorHitAllocator->MallocSingle();
        return hit;
}

inline void SCECalorHit::operator delete(void *hit)
{
        if (!SCECalorHitAllocator) {
                SCECalorHitAllocator = new G4Allocator<SCECalorHit>;
        }
        SCECalorHitAllocator->FreeSingle((SCECalorHit*) hit);
}

inline void SCECalorHit::Add(G4double de, G4double dl) {
        fEdep += de;
        fTrackLength += dl;
}

inline G4double SCECalorHit::GetEdep() const {
        return fEdep;
}

inline G4double SCECalorHit::GetTrackLength() const {
        return fTrackLength;
}

inline std::vector<G4ThreeVector> SCECalorHit::GetPos() {
        return fPos;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
