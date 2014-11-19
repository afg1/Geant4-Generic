/*
    Re-implement the histogramming classes within the Generic program using c++11 compliant unordered_map containers.
    
    This should allow me to use a single base class to then histogram in many dimensions, simultaneously if needed.

*/

#include "Histogramming.hh"


Histogram::Histogram(G4String name, G4ThreeVector cent, G4ThreeVector ext, G4ThreeVector bin, short int dim, int type)
{
    centre = cent;
    extents = ext/2.0;
    bins = bin;
    dimension = dim;
    
    nx = static_cast<unsigned int>(bins[0]);
    ny = static_cast<unsigned int>(bins[1]);
    nz = static_cast<unsigned int>(bins[2]);
    hist_name = name;
    hist_type = type;
}

Histogram::~Histogram()
{
    data.clear();
    hitsHere.clear();
}

void Histogram::Merge(Histogram* right)
{
    std::unordered_map<unsigned int, double>::iterator iterator_r;
    std::unordered_map<unsigned int, double>::iterator iterator_l;
    
    std::unordered_map<unsigned int, unsigned int>::iterator iterator_hits_r;
    std::unordered_map<unsigned int, unsigned int>::iterator iterator_hits_l;
    
    for(unsigned int i=0; i < (nx*ny*nz); i++)
    {
        iterator_r = right->data.find(i);
        iterator_l = data.find(i);
        if(iterator_l != data.end() && iterator_r != right->data.end())// Found in both - add the right to left
        {
            iterator_l->second += iterator_r->second;
        }
        else if(iterator_l == data.end() && iterator_r != right->data.end())// Found in right, but not left
        {
            data.insert(*iterator_r);// We add the newfound dose to our map
        }
        // Two other cases:
        // -    Found in left but not right : We would effectively be doing D_l += 0, so we can ignore this case
        // -    Not found in either map : This is a voxel where no dose has been deposited, so we can safely ignore this case too
        
        iterator_hits_r = right->hitsHere.find(i);
        iterator_hits_l = hitsHere.find(i);
        if(iterator_hits_l != hitsHere.end() && iterator_hits_r != right->hitsHere.end())// Found in both - add the right to left
        {
            iterator_hits_l->second += iterator_hits_r->second;
        }
        else if(iterator_hits_l == hitsHere.end() && iterator_hits_r != right->hitsHere.end())// Found in right, but not left
        {
            hitsHere.insert(*iterator_hits_r);// We add the newfound dose to our map
        }
    }

}

// One dimension

Histogram1D::Histogram1D(G4String name, G4ThreeVector cent, G4ThreeVector ext, G4ThreeVector bin, short int dim, int type) : Histogram(name, cent, ext, bin, dim, type)
{
    // Rely on the setting of bin to determine which dimension to histogram in
    if(nx > 0)
    {
        bindim1 = 0;
        ignore0 = 1;
        ignore1 = 2;
        ny = 1;
        nz = 1;
    }
    else if(ny > 0)
    {
        bindim1 = 1;
        ignore0 = 2;
        ignore1 = 0;
        nx = 1;
        nz = 1;
    }
    else if(nz > 0)
    {
        bindim1 = 2;
        ignore0 = 0;
        ignore1 = 1;
        nx = 1;
        ny = 1;
    }
}

Histogram1D::~Histogram1D()
{
}

void Histogram1D::Fill(G4ThreeVector pos, double D)
{
    
    // Leave it up to the SD to give us sensible numbers
    double diff = ((pos[bindim1] - centre[bindim1]) + extents[bindim1])/(2.0*extents[bindim1]);
    unsigned int u;
    u = static_cast<unsigned int>(floor(diff*bins[bindim1]));
    if(u < bins[bindim1])
    {
        std::pair<unsigned int, double> temp = std::make_pair(u, D);// According to my tests in python, this hashing function has no collisions. It gets re-hashed anyway by the map though.
        std::pair<unsigned int, unsigned int> hitTemp = std::make_pair(u, 1);
        std::pair<std::unordered_map<unsigned int, double>::iterator, bool> insert_rval = data.insert(temp);
        std::pair<std::unordered_map<unsigned int, unsigned int>::iterator, bool> insert_hit = hitsHere.insert(hitTemp);
        
        if(insert_rval.second && insert_hit.second)// Insertion succeeded! Return now
        {
            return;
        }
        else// Found another element with same key - first rval is the iterator to it, so we can directly add the deposit
        {
            insert_rval.first->second += D;
            insert_hit.first->second += 1;
        }
    }
}

void Histogram1D::Write(G4String fname)
{
    std::ofstream output;
    output.open(fname, std::ios::binary);
    double outdata(0), founddata(0);
    if(output.is_open())
    {
        std::unordered_map<unsigned int, double>::iterator iterator;
        std::unordered_map<unsigned int, unsigned int>::iterator hits_iterator;
        for(unsigned int i=0; i < (bins[bindim1]); i++)
        {
            iterator = data.find(i);
            hits_iterator = hitsHere.find(i);
            if(iterator != data.end() && hits_iterator != hitsHere.end())
            {
                if(hist_type == 1 || hist_type == 3)// LET and penumbra LET
                {
                    founddata = (iterator->second/hits_iterator->second);
                }
                else
                {
                    founddata = iterator->second;
                }
                output.write((char*)&founddata, sizeof(double));
            }
            else
            {
                output.write((char*)&outdata, sizeof(double));
            }
        }
    }
	else
	{
		G4cerr << "The file could not be opened for writing." << G4endl;
	}
    output.close();
}





// Two Dimensions

Histogram2D::Histogram2D(G4String name, G4ThreeVector cent, G4ThreeVector ext, G4ThreeVector bin, short int dim, int type) : Histogram(name, cent, ext, bin, dim, type)
{
    if(nx > 0 && ny > 0)
    {
        bindim1 = 0;
        bindim2 = 1;
        ignore1 = 2;
        nz = 1;
    }
    else if(ny > 0 && nz > 0)
    {
        bindim1 = 1;
        bindim2 = 2;
        ignore1 = 0;
        nx = 1;
    }
    else if(nz > 0 && nx > 0)
    {
        bindim1 = 2;
        bindim2 = 0;
        ignore1 = 1;
        ny = 1;
    }

}

Histogram2D::~Histogram2D()
{

}

void Histogram2D::Fill(G4ThreeVector pos, double D)
{
    // Leave it up to the SD to give us sensible numbers
    double diff1 = ((pos[bindim1] - centre[bindim2]) + extents[bindim1])/(2.0*extents[bindim1]);
    double diff2 = ((pos[bindim2] - centre[bindim2]) + extents[bindim2])/(2.0*extents[bindim2]);
    
    unsigned int u1;
    unsigned int u2;
    u1 = static_cast<unsigned int>(floor(diff1*bins[bindim1]));
    u2 = static_cast<unsigned int>(floor(diff2*bins[bindim2]));
    if(u1 < bins[bindim1] && u2 < bins[bindim2])
    {
        std::pair<unsigned int, double> temp = std::make_pair(u1 + bins[bindim1]*u2, D);// According to my tests in python, this hashing function has no collisions. It gets re-hashed anyway by the map though.
        std::pair<std::unordered_map<unsigned int, double>::iterator, bool> insert_rval = data.insert(temp);
        if(insert_rval.second)// Insertion succeeded! Return now
        {
            return;
        }
        else// Found another element with same key - first rval is the iterator to it, so we can directly add the deposit
        {
            insert_rval.first->second += D;
        }
    }
}

void Histogram2D::Write(G4String fname)
{
    std::ofstream output;
    output.open(fname, std::ios::binary);
    double outdata(0);
    if(output.is_open())
    {
        std::unordered_map<unsigned int, double>::iterator iterator;
        for(unsigned int i=0; i < (bins[bindim1]*bins[bindim2]); i++)
        {
            iterator = data.find(i);
            if(iterator != data.end())
            {
                output.write((char*)&iterator->second, sizeof(double));
            }
            else
            {
                output.write((char*)&outdata, sizeof(double));
            }
        }
    }
	else
	{
		G4cerr << "The file could not be opened for writing." << G4endl;
	}
    output.close();
}

// Three Dimensions

Histogram3D::Histogram3D(G4String name, G4ThreeVector cent, G4ThreeVector ext, G4ThreeVector bin, short int dim, int type) : Histogram(name, cent, ext, bin, dim, type)
{

}

Histogram3D::~Histogram3D()
{

}

void Histogram3D::Fill(G4ThreeVector pos, double D)
{
    // Leave it up to the SD to give us sensible numbers
    double xdiff(0), ydiff(0), zdiff(0);
    xdiff = (pos[0] + extents[0])/(2.0*extents[0]);
    ydiff = (pos[1] + extents[1])/(2.0*extents[1]);// This is the linear method used in the GSL library histogram filling, it only works in the range is linear, which it always will be for this case.
    zdiff = (pos[2] + extents[2])/(2.0*extents[2]);
    
    unsigned int ux, uy, uz;
    ux = static_cast<unsigned int>(floor(xdiff*bins[0]));
    uy = static_cast<unsigned int>(floor(ydiff*bins[1]));// Explicitly floor then cast to avoid confusion
    uz = static_cast<unsigned int>(floor(zdiff*bins[2]));
    
    if(ux < bins[0] && uy < bins[1] && uz < bins[2]  )
    {
        std::pair<unsigned int, double> temp = std::make_pair(ux + nx*uy + (nx*ny)*uz , D);// According to my tests in python, this hashing function has no collisions. It gets re-hashed anyway by the map though.
        std::pair<std::unordered_map<unsigned int, double>::iterator, bool> insert_rval = data.insert(temp);
        if(insert_rval.second)// Insertion succeeded! Return now
        {
            return;
        }
        else// Found another element with same key - first rval is the iterator to it, so we can directly add the deposit
        {
            insert_rval.first->second += D;
        }
    }

}

void Histogram3D::Write(G4String fname)
{
    std::ofstream output;
    output.open(fname, std::ios::binary);
    double outdata(0);
    if(output.is_open())
    {
        std::unordered_map<unsigned int, double>::iterator iterator;
        for(unsigned int i=0; i < (nx*ny*nz); i++)
        {
            iterator = data.find(i);
            if(iterator != data.end())
            {
                output.write((char*)&iterator->second, sizeof(double));
            }
            else
            {
                output.write((char*)&outdata, sizeof(double));
            }
        }
    }
	else
	{
		G4cerr << "The file could not be opened for writing." << G4endl;
	}
    output.close();
}
