# warwick-legend
Legend muon background simulations

First attempt at creating a LEGEND Monte-Carlo simulation application, 
suitable for large production runs estimating Germanium-77 production in 
Germanium-76 crystals in different underground laboratories.

Should allow for two alternative experimental setups.

## Requirements

Multi-threading operation and MPI capability

ROOT ntuple output

Biasing of neutron production by muons (physics bias), 
neutron population inside cryostant (geometry bias) and 
neutron capture reaction (Ge-77 production from n,gamma reaction)

Operate with command line input and Geant4 macro.

Macro commands for change of geometry, one material in the geometry, 
primary vertex generator, cross section bias factor (one each, neutron and muon), 
bias split factor (integer >= 2)

CLI for number of threads, macro file, output file name (for production runs)

User Limits for run time optimization, use recommended benchmarking tool


