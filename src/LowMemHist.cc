#include "LowMemHist.h"

#include "G4ThreeVector.hh"
#include "globals.hh"

#include <fstream>
#include <iostream>
LMHist::LMHist()
{
    usex = false;
    usey = false;
    usez = false;
    nx = 0;
    ny = 0;
    nz = 0;
    s1 = 0;
    s2 = 0;
    s3 = 0;
    nc1 = 0;
    nc2 = 0;
    nc3 = 0;
    
    axisSet = false;
    
}



LMHist::LMHist(int nai , char ax, G4ThreeVector p, double max1i, double min1i)
{
    if(ax == 'x')
    {
        nx = nai;
        nc1 = nx/2;
        s1 = (max1i - min1i)/nx;
        usex = true;
    }
    else if(ax == 'y')
    {
        ny = nai;
        nc1 = ny/2;
        s1 = (max1i - min1i)/ny;
        usey = true;
    }
    else if(ax == 'z')
    {
        nz = nai;
        nc1 = nz/2;
        s1 = (max1i - min1i)/nz;
        usez = true;
    }
    else
    {
        G4Exception("LHMist Constructor (1D)", "InvalidAxisException", FatalErrorInArgument , "Must specify a valid axis: x,y or z!");
    }
    centre = p;
}

LMHist::LMHist(int na1i, int na2i, char* ax, G4ThreeVector p, double max1i, double min1i, double max2i, double min2i)
{
    if(strcmp(ax, "xy"))
    {
        nx = na1i;
        ny = na2i;
        
        nc1 = nx/2;
        nc2 = ny/2;
        
        s1 = (max1i - min1i)/nx;
        s2 = (max2i - min2i)/ny;
        
        usexy = true;
    }
    else if(strcmp(ax, "yz"))
    {
        ny = na1i;
        nz = na2i;
        
        nc1 = ny/2;
        nc2 = nz/2;
        
        s1 = (max1i - min1i)/ny;
        s2 = (max2i - min2i)/nz;
        
        useyz = true;
    }
    else if(strcmp(ax, "zx"))
    {
        nz = na1i;
        nx = na2i;
        
        nc1 = nz/2;
        nc2 = nx/2;
        
        s1 = (max1i - min1i)/nz;
        s2 = (max2i - min2i)/nx;
        
        usezx = true;
    }
    else
    {
        G4Exception("LHMist Constructor (2D)", "InvalidAxisException", FatalErrorInArgument , "Must specify a valid axis pair: xy, yz or zx!");
    }
    centre = p;
}
        

LMHist::LMHist(int nxi, int nyi, int nzi, G4ThreeVector p, G4ThreeVector maxi, G4ThreeVector mini)
{
    nx = nxi;
    ny = nyi;
    nz = nzi;
    
    nc1 = nx/2;
    nc2 = ny/2;
    nc3 = nz/2;
    
    s1 = (maxi.x() - mini.x())/nx;
    s2 = (maxi.y() - mini.y())/ny;
    s3 = (maxi.z() - mini.z())/nz;
    
    maxcheck = nx*ny*nz;
    centre = p;
}

void LMHist::Fill(G4ThreeVector x, double D)
{
    int vn(0);
    if(oneD)
    {
        if(usex)
        {
            vn = ceil((x-centre).x()/s1) + nc1;
        }
        else if(usey)
        {
            vn = ceil((x-centre).y()/s1) + nc1;
        }
        else if(usez)
        {
            vn = ceil((x-centre).z()/s1) + nc1;
        }
    }
    else if(twoD)
    {
        if(usexy)
        {
            vn = (ceil((x-centre).x()/s1) + nc1) +  nx * (ceil((x-centre).y()/s2)) + nc2 ;
        }
        else if(useyz)
        {
            vn = (ceil((x-centre).y()/s1) + nc1) +  ny * (ceil((x-centre).z()/s2)) + nc2;
        }
        else if(usezx)
        {
            vn = (ceil((x-centre).z()/s1) + nc1) +  nz * (ceil((x-centre).x()/s2)) + nc2;
        }
    }
    else if(threeD)
    {
        vn = (ceil((x-centre).x()/s1) + nc1) +  (nx * (ceil((x-centre).y()/s2)) + nc2) + nx*ny*ceil((x-centre).z()/s3) + nc3;
    }
    // Iterator to assign
    std::map<int, double>::iterator elem;
    elem = doseMap.find(vn);// Search for the element
    
    if(elem != doseMap.end())// Element exists...
    {
        doseMap[vn] += D;//... Accumulate
    }
    else// Element does not exist...
    {
        doseMap.insert(std::pair<int, double>(vn, D));//... Create
    }
}

void LMHist::Write(std::string fname)
{
    G4cout << "Got this far..." << G4endl;
    std::ofstream output(fname.c_str(), std::ios::binary);
    if(!output.is_open())
    {
        G4Exception("LHMist Write", "FileIOException", FatalException , "Failed to open file, aborting!");
    }
    std::map<int, double>::iterator elem;
    double zero = 0.0;// Create a variable so I can reference it in a minute
    G4cout << nx << "  " << ny << "  " << nz << G4endl;
    G4cout << usex << "  " << usey << "  " << usez << G4endl;
    if(oneD)
    {
        if(usex)
        {
            for(int a=0; a<nx; a++)
            {
                elem = doseMap.find(a);// Search for the element
                    
                if(elem == doseMap.end())// element doesn't exist...
                {
                    output.write((char*)&zero, sizeof(double));// therefore output zero
                }
                else
                {
                    output.write((char*)&doseMap[a], sizeof(double));// Element does exist so output it
                }
            }
        }
        else if(usey)
        {
            for(int a=0; a<ny; a++)
            {
                elem = doseMap.find(a);// Search for the element
                    
                if(elem == doseMap.end())// element doesn't exist...
                {
                    output.write((char*)&zero, sizeof(double));// therefore output zero
                }
                else
                {
                    output.write((char*)&doseMap[a], sizeof(double));// Element does exist so output it
                }
            }
        }
        else if(usez)
        {
            for(int a=0; a<nz; a++)
            {
                elem = doseMap.find(a);// Search for the element
                    
                if(elem == doseMap.end())// element doesn't exist...
                {
                    output.write((char*)&zero, sizeof(double));// therefore output zero
                }
                else
                {
                    output.write((char*)&doseMap[a], sizeof(double));// Element does exist so output it
                }
            }
        }

    }
    else if(twoD)
    {
        if(usexy)
        {
            for(int a=0; a<nx; a++)
            {
                for(int b=0; a<ny; b++)
                {
                    elem = doseMap.find((a + nx*b));// Search for the element
                        
                    if(elem == doseMap.end())// element doesn't exist...
                    {
                        output.write((char*)&zero, sizeof(double));// therefore output zero
                    }
                    else
                    {
                        output.write((char*)&doseMap[(a + nx*b)], sizeof(double));// Element does exist so output it
                    }
                }
            }
        }
        else if(useyz)
        {
            for(int a=0; a<ny; a++)
            {
                for(int b=0; a<nz; b++)
                {
                    elem = doseMap.find((a + ny*b));// Search for the element
                        
                    if(elem == doseMap.end())// element doesn't exist...
                    {
                        output.write((char*)&zero, sizeof(double));// therefore output zero
                    }
                    else
                    {
                        output.write((char*)&doseMap[(a + ny*b)], sizeof(double));// Element does exist so output it
                    }
                }
            }
        }
        else if(usezx)
        {
            for(int a=0; a<nz; a++)
            {
                for(int b=0; a<nx; b++)
                {
                    elem = doseMap.find((a + nz*b));// Search for the element
                        
                    if(elem == doseMap.end())// element doesn't exist...
                    {
                        output.write((char*)&zero, sizeof(double));// therefore output zero
                    }
                    else
                    {
                        output.write((char*)&doseMap[(a + nz*b)], sizeof(double));// Element does exist so output it
                    }
                }
            }
        }
    }
    else if(threeD)
    {
        for(int a=0; a<nz; a++)
        {
            for(int b=0; b<ny; b++)
            {
                for(int c=0; c<nx; c++)// Note - the order of loops is specific to Analyze75 format
                {
                    elem = doseMap.find((c + nx*b + nx*ny*a));// Search for the element
                    
                    if(elem == doseMap.end())// element doesn't exist...
                    {
                        output.write((char*)&zero, sizeof(double));// therefore output zero
                    }
                    else
                    {
                        output.write((char*)&doseMap[(c + nx*b + nx*ny*a)], sizeof(double));// Element does exist so output it
                    }
                }
            }
        }
    }
    
}

double LMHist::Search(int vn)
{
    // Iterator to assign
    std::map<int, double>::iterator elem;
    elem = doseMap.find(vn);// Search for the element
    
    if(elem != doseMap.end())// Element exists...
    {
        return doseMap[vn];
    }
    else// Element does not exist...
    {
        return 0.0;
    }
}

void LMHist::Add(LMHist& right)
{
    int lEnd = doseMap.size();
    int rEnd = right.doseMap.size();// Get the sizes of the two maps
    
    if(lEnd > rEnd)
    {
        std::map<int, double>::iterator elem = doseMap.end();// Use for find/accumulate loop
        right.GetDoseMap().insert(doseMap.begin(), doseMap.end());// insert overwrites elements - adds some non-existant elements
        // Don't need to cache because can just use local copy of doseMap in this branch
        for(std::map<int, double>::iterator it=right.GetDoseMap().begin(); it != right.GetDoseMap().end(); ++it)
        {
            elem = doseMap.find(it->first);// Loop through the smaller map, adding elements from the larger map.
            if(elem != doseMap.end())
            {
                it->second += elem->second;
            }
        }
        // Final thing to do is copy the right map to this map. This overwrites current content, but shold be okay now.
        doseMap = right.GetDoseMap();
    }
    else// either rEnd > lEnd, or rEnd == lEnd
    {
        std::map<int, double>::iterator elem = right.GetDoseMap().end();// Use for find/accumulate loop
        std::map<int, double> cacheMap = doseMap;// Need to cache the map in this branch
        doseMap.insert(right.GetDoseMap().begin(), right.GetDoseMap().end());// insert overwrites elements

        for(std::map<int, double>::iterator it=doseMap.begin(); it != doseMap.end(); ++it)
        {
            elem = right.GetDoseMap().find(it->first);// Loop though the smaller map adding elements
            if(elem != right.GetDoseMap().end())
            {
                it->second += elem->second;
            }
        }
        // No need to copy in this branch
    }
}
    
    

void LMHist::SetDimension(int D)
{
    if(D == 1)
    {
        oneD = true;
    }
    else if(D ==2)
    {
        twoD = true;
    }
    else if(D == 3)
    {
        threeD = true;
    }
    else
    {
        G4Exception("LMHist::SetDimension", "IncorrectDimensionException", FatalErrorInArgument , "Histogram must be either 1,2 or 3D!");
    }
}

void LMHist::SetMax3(G4ThreeVector M3)
{
    max1 = M3.x();
    max2 = M3.y();
    max3 = M3.z();
}

void LMHist::SetMin3(G4ThreeVector M3)
{
    min1 = M3.x();
    min2 = M3.y();
    min3 = M3.z();
}

void LMHist::SetMax2(double M2)
{
    max2 = M2;
}

void LMHist::SetMin2(double M2)
{
    min2 = M2;
}

void LMHist::SetMax1(double M1)
{
    max1 = M1;
}
void LMHist::SetMin1(double M1)
{
    min1 = M1;
}

void LMHist::SetCentre(G4ThreeVector C)
{
    centre = C;
}

void LMHist::SetBins1(int B1)
{
    if(!axisSet)
    {
        G4Exception("LHMist::SetBins1", "AxisNotSetWarning", JustWarning , "You need to set the axis before the binning - this result is likely to be bollocks");
    }
    
    if(usex)
    {
        nx = B1;
    }
    else if(usey)
    {
        ny = B1;
    }
    else if(usez)
    {
        nz = B1;
    }
    else if(usexy)
    {
        nx = B1;
    }
    else if(useyz)
    {
        ny = B1;
    }
    else if(usezx)
    {
        nz = B1;
    }
}
void LMHist::SetBins2(int B2)
{
    if(!axisSet)
    {
        G4Exception("LHMist::SetBins2", "AxisNotSetWarning", JustWarning , "You need to set the axis before the binning - this result is likely to be bollocks");
    }

    if(usexy)
    {
        ny = B2;
    }
    else if(useyz)
    {
        nz = B2;
    }
    else if(usezx)
    {
        nx = B2;
    }
}

void LMHist::SetBins3(int nxi, int nyi, int nzi)
{
    nx = nxi;
    ny = nyi;
    nz = nzi;
}

void LMHist::SetAxis(G4String ax)
{
    if(!strcmp(ax, "x"))
    {
        usex = true;
    }
    else if(!strcmp(ax, "y"))
    {
        usey = true;
    }
    else if(!strcmp(ax, "z"))
    {
        usez = true;
    }
    else if(!strcmp(ax, "xy"))
    {
        usexy = true;
    }
    else if(!strcmp(ax, "yz"))
    {
        useyz = true;
    }
    else if(!strcmp(ax, "zx"))
    {
        usezx = true;
    }
    axisSet = true;
}

void LMHist::Finalize()
{
    if(oneD)
    {
        if(usex)
        {
            nc1 = nx/2;
            s1 = (max1 - min1)/nx;
        }
        else if(usey)
        {
            nc1 = ny/2;
            s1 = (max1 - min1)/ny;
        }
        else if(usez)
        {
            nc1 = nz/2;
            s1 = (max1 - min1)/nz;
        }
    }
    else if(twoD)
    {
        if(usexy)
        {
            nc1 = nx/2;
            nc2 = ny/2;
            
            s1 = (max1 - min1)/nx;
            s2 = (max2 - min2)/ny;
        }
        else if(useyz)
        {
            nc1 = ny/2;
            nc2 = nz/2;
            
            s1 = (max1 - min1)/ny;
            s2 = (max2 - min2)/nz;
        }
        else if(usezx)
        {
            nc1 = nz/2;
            nc2 = nx/2;
            
            s1 = (max1 - min2)/nz;
            s2 = (max2 - min2)/nx;
        }
    }
    else if(threeD)
    {
        nc1 = nx/2;
        nc2 = ny/2;
        nc3 = nz/2;
        
        s1 = (max1 - min1)/nx;
        s2 = (max2 - min2)/ny;
        s3 = (max3 - min3)/nz;
        maxcheck = nx*ny*nz;
    }
}
