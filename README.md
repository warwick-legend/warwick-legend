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

## How to Build/Develop
The project has the following requirements:

- Linux/macOS system (only CentOS7, Catalina tested at present)
- C++17 compatible compiler (GCC9, Xcode 11 tested at present)
- CMake 3.12 or newer
- Geant4 10.6 built with multithreading and gdml support

It may be compiled using:

```console
$ mkdir build && cd build
$ cmake ..
$ make
```

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

