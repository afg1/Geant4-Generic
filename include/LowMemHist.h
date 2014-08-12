#ifndef LOWMEMHIST_H
#define LOWMEMHIST_H 1
/*
Experimental class defining a low memory histogram designed for use in multi-threaded environments.

The general idea:
When I define a histogram, I usually would create arrays or vectors of doubles, and fill them as needed.
However, most of the voxels in these arrays remain empty, and aren't really needed, so what about 
creating a map of voxel# -> dose that only gets filled when dose if deposited?

Using the C++ map container, a key value (of any type) can point to a data value (of any type). No two 
elements can have the same key, so we would index by voxel number. Say we have a 128x128x128 cubic volume,
the maximum voxel number is 2097152, so the indices run from 0 -> 2097151 and will serve as key values.

When filling the histogram, we have to:
- Calculate the 3d voxel number (a,b,c)
- convert this to the voxel index (a*b*c)
- Search for this voxel index
- if it doesn't exist, create it and add dose to that entry
- if it does exists, update the dose in that entry

When writing the histogram, we have to:
- Loop through the nested for loop 
- for each a*b*c in the nested loop, search the map
- If nothing is found, write out a zero
- If something is found, write out that dose.

*/

#include <map>
#include <string>

#include "G4ThreeVector.hh"


class LMHist
{

    public:
        LMHist();// Default constructor, we will then sort things via the messenger class...
        LMHist(int nai , char ax, G4ThreeVector p, double max1i, double min1i);// Constructor for 1d histogram, with axis as char, eg "x". p specifies the centre, also specify the extents
        LMHist(int na1i, int na2i, char* ax, G4ThreeVector p, double max1i, double min1i, double max2i, double min2i);// Constructor for 2dHistogram, axis as c-string, eg "xy", p specifies where in the other plane to put the centre, also specify extents
        LMHist(int nxi, int nyi, int nzi, G4ThreeVector p, G4ThreeVector maxi, G4ThreeVector mini);// Constructor with 3d histogram size, p specifies centre, min and max specify extents
        ~LMHist(){}
    
        void Fill(G4ThreeVector x, double D);// This one method will work for all three dimensionalities
        void Write(std::string );// Also modified to work in all three cases
    
        void Add(LMHist&);
        double Search(int);
        std::map<int, double>& GetDoseMap()
        {
            return doseMap;
        }
    
        void SetDimension(int);
        void SetMax3(G4ThreeVector);
        void SetMin3(G4ThreeVector);
        void SetMax2(double);
        void SetMin2(double);
        void SetMax1(double);
        void SetMin1(double);
    
        void SetCentre(G4ThreeVector);
        void SetBins1(int);
        void SetBins2(int);
        void SetBins3(int, int, int);
        void SetAxis(G4String);
    
        void Finalize();
    
    private:
        int nx;
        int ny;// The voxel numbers, for the output loops
        int nz;
    
        int nc1;
        int nc2;// centres of the histograms
        int nc3;
    
        bool usex;
        bool usey;
        bool usez;
    
        bool usexy;
        bool useyz;
        bool usezx;
    
        bool oneD;
        bool twoD;
        bool threeD;
    
        double s1;
        double s2;
        double s3;
    
        G4ThreeVector centre;
    
        double max1;
        double min1;
        double max2;
        double min2;
        double max3;
        double min3;
    
        int maxcheck;// Check for the maximum - don't fill if outside!
    
        std::map<int, double> doseMap;// The actual histogram
    
        bool axisSet;



};



#endif
