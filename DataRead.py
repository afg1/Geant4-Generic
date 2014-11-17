import numpy as np
import matplotlib.pyplot as plt
"""
Simple plotting script for the histograms output from my basic Geant4 sim
"""



xrange = np.linspace(0, 30, 1000)# this should correspond to the binning and extents in your macro

#hist1D = np.fromfile("electrondose", dtype=float)# Change the bits in quotes here to whatever your output is called
hist1dP = np.fromfile("protonLET1") # comment this line if you only want to plot a single result

#hist1D = hist1D/max(hist1D)# This is normalising by dividing everything by the biggest number in the array - probably not strictly correct but makes pretty plots
hist1dP = hist1dP/max(hist1dP)# comment this line if you only want to plot a single result

print(hist1dP)# these will print the sizes of arrays, if they are different, something went wrong and the plot will crash
#print(xrange.shape)


#plt.plot(xrange, hist1D)
plt.plot(xrange, hist1dP)# comment this line if you only want to plot a single result
plt.xlabel("Depth in Water (cm)")
plt.ylabel("Energy Deposited (Normalised)")
plt.savefig("BraggPeak.png")# Save plots - always do this BEFORE showing!
plt.show()# Show the plots
