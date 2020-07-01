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

Macro commands for change of geometry, 
primary vertex generator and cross section bias factor (one each, neutron and muon)

CLI for number of threads, macro file, output file name (for production runs)

User Limits for run time optimization

## How to Build/Develop
The project has the following requirements:

- Linux/macOS system (only CentOS7, Catalina tested at present)
- C++17 compatible compiler (GCC9, Xcode 11 tested at present)
- CMake 3.12 or newer
- Geant4 10.6 built with multithreading and gdml support
  - Qt or OpenGL/X11 driver support if you want to visualize the geometry/tracks/hits

It may be compiled using:

```console
$ mkdir build && cd build
$ cmake ..
$ make
```

Testing is enabled by default via the `BUILD_TESTING` CMake argument and may be run after
building by running

```
$ ctest
```

Run `ctest --help` for options to select tests and/or run with increased verbosity, e.g.

```
$ ctest -VV
```

to get verbose (including stdout) output from the setup and execution of the tests.

The resulting `warwick-legend` application may be run without arguments to start an interactive
session. Otherwise run `warwick-legend --help` to see a list of options for batch mode running.


Support files for `[clang-format](https://clang.llvm.org/docs/ClangFormat.html)` and `[clang-tidy](https://clang.llvm.org/extra/clang-tidy/)` are provided to help automate formatting (following the
Geant4 style) and static analysis respectively. No explicit setup is needed
for autoformatting other than the relevant integration settings of your
favoured editor/IDE ([vim](http://clang.llvm.org/docs/ClangFormat.html#vim-integration), [emacs](http://clang.llvm.org/docs/ClangFormat.html#emacs-integration), [vscode](https://code.visualstudio.com/docs/cpp/cpp-ide#_code-formatting)). To enable static
analysis, ensure you have `clang-tidy` installed and run the build as:

```console
$ mkdir build-tidy && cd build-tidy
$ cmake -DCMAKE_CXX_CLANG_TIDY="/path/to/clang-tidy" ..
$ make
```

The `.clang-tidy` file supplied in this project will be used, and suggestions
for fixes will be emitted whilst building. At present, the `-fix` option is
automatically apply the suggested change is not used to leave the decision
up to the developer. The set of fixes applied are:

- `readability-*`
- `modernize-*`
- `performance-*`

For a full listing of the wildcards, see [the `clang-tidy` documentation](https://clang.llvm.org/extra/clang-tidy/checks/list.html).

## Code Details
### Cross secton bias reference
M.H. Mendenhall and R.A. Weller, NIM A667 (2012) 38-43

### Ntuple output columns
- Hit data, one row per event
  - Edep
  - Time
  - Hit x location
  - Hit y location
  - Hit z location
- Trajectory data, one row per event
  - PDG code
  - N entries in position containers
  - Vertex logical volume name code, see name map
  - Vertex x location
  - Vertex y location
  - Vertex z location
- Trajectory data track step points, N rows, see N entries column above
  - x position
  - y position
  - z position

### Vertex Name Map
Volume definitions in detector construction.
- lookup["Cavern_log"]   = 0;
- lookup["Hall_log"]     = 1;
- lookup["Tank_log"]     = 2;
- lookup["Water_log"]    = 3;
- lookup["Cout_log"]     = 4;
- lookup["Cvac_log"]     = 5;
- lookup["Cinn_log"]     = 6;
- lookup["Lar_log"]      = 7;
- lookup["Lid_log"]      = 8;
- lookup["Bot_log"]      = 9;
- lookup["Copper_log"]   = 10;
- lookup["ULar_log"]     = 11;
- lookup["Ge_log"]       = 12;
- lookup["Pu_log"]       = 13;
- lookup["Membrane_log"] = 14;
