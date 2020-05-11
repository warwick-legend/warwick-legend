cmake_minimum_required(VERSION 3.12)
project(warwick-legend VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Geant4 10.6 REQUIRED ui_all vis_all)

add_executable(warwick-legend
  warwick-legend.cc
  src/WLGDActionInitialization.cc
  src/WLGDBiasChangeCrossSection.cc
  src/WLGDBiasMultiParticleChangeCrossSection.cc
  src/WLGDDetectorConstruction.cc
  src/WLGDEventAction.cc
  src/WLGDPrimaryGeneratorAction.cc
  src/WLGDPSLocation.cc
  src/WLGDRunAction.cc
  src/getopt_pp.cpp)
target_include_directories(warwick-legend PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(warwick-legend PRIVATE ${Geant4_LIBRARIES})
