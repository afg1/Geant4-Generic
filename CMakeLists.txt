cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH /Users/andrew/Documents/Programs/Geant4/geant4.9.5.p01/cmake/Modules/)

find_package(Geant4 REQUIRED vis_all)

include_directories("include" ${Geant4_INCLUDE_DIRS} ${ROOT_INCLUDE_DIR})
add_definitions(${Geant4_DEFINITIONS} ${ROOT_DEFINITIONS} "-O3" "-Wall" "-DG4VIS_USE" )
set(CMAKE_CXX_FLAGS ${Geant4_CXX_FLAGS} ${ROOT_CXX_FLAGS})

FILE(GLOB sources src/*.cc)
FILE(GLOB headers include/*.hh)

add_executable(G4e G4Generic.cc ${sources} ${headers})
target_link_libraries(G4e ${Geant4_LIBRARIES})
