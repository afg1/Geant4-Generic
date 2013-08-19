#include "Hit.hh"

WaterHit::WaterHit(){}

WaterHit::~WaterHit(){}

WaterHit::WaterHit(const WaterHit& right) : G4VHit()
{
    edep = right.edep;
    pos = right.pos;
    ene = right.ene;

}

const WaterHit& WaterHit::operator=(const WaterHit& right)
{
    edep = right.edep;
    pos = right.pos;
    ene = right.ene;
    return *this;
}

G4int WaterHit::operator==(const WaterHit& right)const
{
    return (this==&right) ? 1:0;
}

void WaterHit::Draw()
{}

void WaterHit::Print()
{
    G4cout << "Energy Deposit " << edep << G4endl;
    G4cout << "Position " << pos << G4endl;
    G4cout << "Energy of step " << ene << G4endl;
}
