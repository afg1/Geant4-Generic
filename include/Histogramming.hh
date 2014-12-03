#ifndef HISTOGRAM_HH
#define HISTOGRAM_HH 1

#include <unordered_map> // Requires c++11
#include <fstream>

#include "G4ThreeVector.hh"
#include "G4String.hh"

class Histogram
{
    public:
        Histogram(G4String, G4ThreeVector, G4ThreeVector, G4ThreeVector, short int, int);
        virtual ~Histogram();
        virtual void Fill(G4ThreeVector, double, double)=0;
        virtual void Write(G4String)=0;
        void Merge(Histogram*);
        int GetType(){return hist_type;}
        G4String GetName(){return hist_name;}

    protected:
        G4ThreeVector centre;
        G4ThreeVector extents;
        G4ThreeVector bins;
    
        std::unordered_map<unsigned int, double> data;
        std::unordered_map<unsigned int, unsigned int> hitsHere;
    
        short int dimension;
    
        unsigned int nx;
        unsigned int ny;
        unsigned int nz;
        unsigned int bindim1;
        unsigned int bindim2;
        unsigned int ignore0;
        unsigned int ignore1;
    
        G4String hist_name;
        int hist_type;
};


class Histogram1D : public Histogram
{
    public:
        Histogram1D(G4String, G4ThreeVector, G4ThreeVector, G4ThreeVector, short int, int);
        ~Histogram1D();
        virtual void Fill(G4ThreeVector, double, double);
        virtual void Write(G4String);
    
//    private:
    
};

class Histogram2D : public Histogram
{
    public:
        Histogram2D(G4String, G4ThreeVector, G4ThreeVector, G4ThreeVector, short int, int);
        ~Histogram2D();
        virtual void Fill(G4ThreeVector, double, double);
        virtual void Write(G4String);



};

class Histogram3D : public Histogram
{
    public:
        Histogram3D(G4String, G4ThreeVector, G4ThreeVector, G4ThreeVector, short int, int);
        ~Histogram3D();
        virtual void Fill(G4ThreeVector, double, double);
        virtual void Write(G4String);




};

#endif
