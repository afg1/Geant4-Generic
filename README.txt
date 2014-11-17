This program implements a simple monte carlo implementation using the Geant4 framework to
simulate pretty much any incident particle on a block of water.

Compilation:

I’m going to assume you’ve already installed Geant4, but if you haven’t download the source code from here: 

http://geant4.cern.ch/support/download.shtml

And follow the instructions here:

http://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides/InstallationGuide/html/index.html

After you’ve done this, you need to make sure you source the script called geant4.sh which is located in the bin/ folder wherever you installed Geant. This sets up the environment and makes sure cmake can find the install.

cd into the directory where you cloned this repository and make a folder called “build” or similar, then cd into it. then run “ccmake ../“ to configure the build. after a few presses of “c” and hopefully no error messages, you can press “g” and then give the “make” command. There should not be any error messages, but there might be a few warnings, you can ignore them.

This will give you the executable, called G4e. To run it you need to give the command ./G4e. For help with command line arguments, run “./G4e h” and it will print a little help message which is hopefully self explanatory. 

When you want to run in anger, I suggest creating a folder called “runs” or something and copying G4e into it, then you can run a macro with a command like “./G4e testmac 4” which will load and run testmac using 4 threads. I have included a test macro and visualisation macro to get you started.



Specifics:

I implemented a few new messenger classes that give you access to a few useful commands, they are:

- /geometryMessenger/update - Refreshes the geometry so that things move/rotate when you ask them to.

- /geometryMessenger/shiftWater <x> <y> <z> <unit> - This command moves the water box about. It is very important that the above command is called after any changes to the geometry. <x>, <y> and <z> are floating point numbers, and the unit should be any length unit (e.g. mm)

- /geometryMessenger/rotateWaterX <theta> <unit> - This command rotates about the X-axis by the amount you specify (floating point again). The unit is either deg or rad

- /geometryMessenger/rotateWaterY <theta> <unit> - Same as above but rotate about Y-axis

- /geometryMessenger/rotateWaterX <theta> <unit> - same as above but rotate about Z-axis

It is very important that the geometry is updated after calling any of these commands!


In order to get some nice results quickly, I have implemented a multi-dimensional histogramming class in the simulation. The /SDMessenger/ command subdirectory has all the commands for these histograms.

- /SDMessenger/addHist <name> - This command adds a histogram to the simulation, with your given name. Right now I can only do a single histogram per simulation, but I’m working on multiple…

- /SDMessenger/setHistDim <int> - This command sets the dimension of the histogram, either 1, 2 or 3 dimensional. You must have already added the histogram with the above command. Specifying anything other then 1, 2 or 3 as the argument to this will result in an error.

- /SDMessenger/setMax3 <xMax> <yMax> <zMax> <unit> - This command sets the maximum extent in 3D for the histogram, the numbers should be floating point and the unit is one of length. Only use this for 3D otherwise it will be ignored.

- /SDMessenger/setMin3 <xMin> <yMin> <zMin> <unit> - This command sets the minimum extent of the histogram in 3D, similar to above.

- /SDMessenger/setMax2 <val> <unit> -  Specify the maximum extent in 2D for the histogram. Only used for 2D, will be ignored otherwise. Use in conjunction with /SDMessenger/setMin2. val should be a floating point, unit is of length.

- /SDMessenger/setMin2 <val> <unit> -  Specify the minimum extent in 2D for the histogram. Only used for 2D, will be ignored otherwise. Use in conjunction with /SDMessenger/setMax2. val should be a floating point, unit is of length.

/SDMessenger/setMax1 <val> <unit> -  Specify the maximum extent in 1D for the histogram. Used for 1D and 2D, will be ignored otherwise. Use in conjunction with /SDMessenger/setMin1. val should be a floating point, unit is of length.

- /SDMessenger/setMin1 <val> <unit> -  Specify the minimum extent in 1D for the histogram. Used for 1D and 2D, will be ignored otherwise. Use in conjunction with /SDMessenger/setMax1. val should be a floating point, unit is of length

- /SDMessenger/setBins1D <int> -  Specify the binning in 1D. Used for 1&2D histograms, ignored in 3D. Argument type is integer


- /SDMessenger/setBins2D <int> - Specify the binning in 2D. Used in conjunction with /SDMessenger/setBins1D for 2D histograms only. Argument type is integer


- /SDMessenger/setBins3D <int> <int> <int> - Specify the binning in 3D as x,y,z integers. Only used for 3D histograms. Argument type is integer.

- /SDMessenger/setAxis <str> - Specify the axis to histogram in. Only applicable to 1 and 2D histograms. Should be one of the following: x, y, z, xy, yz, zx (only those combinations are allowed)

- /SDMessenger/writeData <str> -  Writes out the SD tracking data to wherever you tell it to. This basically is the name of the output you want, and can be a path if you want to write somewhere specific.

- /SDMessenger/finalize - Locks the histogram and makes sure everything is ready, call just before beamOn. This is also very important, otherwise things will crash.


Have a look in the “testmac” file for an example of how to use some of these commands, hopefully you can figure out what to do from there. Some of the functions are untested, so there might be some strange bugs, if something really weird happens, let me know and I’ll investigate.

If at any time you need to check something, you can run the executable with no arguments to bring up an interactive shell, then type help and follow the instructions. All this stuff is also in there.


Visualisation:

I’ve included my ‘standard’ visualisation macro, which will give you a pretty little animation of what is going on. This will require you to have built Geant4 with visualisation enabled, but it’s pretty simple to re-build if you didn’t do that. DO NOT run with visualisation enabled when you want to collect results, it makes the code about 100x slower and the simulation will probably take days.

Physics:

I’ve made choices of physics lists based on what I reckon is about right for proton therapy. These may not be the best for what you want to look at. You should look into the available electromagnetic and hadronic physics lists and read around what has been done in your area before selecting a different one. The change is fairly simple, requiring you to edit two lines in the file src/Physics.cc and recompile the executable. If you decide you want to try this, let me know and I can show you what to edit.

Histograms:

I’ve included a little python script to load and visualise the histograms, so that you can get a depth-dose curve from different particles relatively quickly. This is very much a stub, and while I realise learning a programming language in three weeks is probably a tall order, if you’re going to start learning any language, I’d say python is the most useful straight away, and will stand you in good stead for doing MATLAB and C/C++ later (p.s. these are really easy marks to bump your averages up in years 3/4). I hope the script I’ve supplied gives you enough of a start to figure out what to do next. If you get errors like “mode matplotlib.pyplot not found” or something like that, you need to install a few extra bits. I don’t know what OS you’ll be running this on, but you can look up how to install things easily enough. To run it do “python DataRead.py” after making sure you edit the filename to whatever your output is.

The Future:

I plan to add functionality to this program (and use it myself!) including the ability to alter the water box size from the macros, and to load a CT image in to replace the water box. For now if you need to do any of these things urgently, you’ll have to drop me an email so I can either tell you what to do in code, or add the functions to the messengers.


Have fun!


