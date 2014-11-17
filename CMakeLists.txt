cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH /Users/andrew/Documents/Programs/Geant4/geant4.9.5.p01/cmake/Modules/)

find_package(Geant4 REQUIRED vis_all)
SET(CXX11 "-std=c++11")
include_directories("include" ${Geant4_INCLUDE_DIRS})
add_definitions(${Geant4_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${Geant4_CXX_FLAGS} ${CXX11}")

FILE(GLOB sources src/*.cc)
FILE(GLOB headers include/*.hh)

add_executable(G4e G4Generic.cc ${sources} ${headers})
target_link_libraries(G4e ${Geant4_LIBRARIES})
