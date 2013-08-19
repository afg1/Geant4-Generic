include(CMakeForceCompiler)
find_package(Geant4 REQUIRED vis_all)
include_directories("include" ${Geant4_INCLUDE_DIRS})
add_definitions("src" ${Geant4_DEFINITIONS} "-g")
set(CMAKE_CXX_FLAGS ${Geant4_CXX_FLAGS})


add_executable(FCT FakeCT.cc src/Physics.cc src/Generator.cc
src/World.cc src/Hit.cc src/SensitiveDetector.cc src/CommandLineParser.cc src/GeometryMessenger.cc)
target_link_libraries(FCT ${Geant4_LIBRARIES})
