# WHAT ARCHITECTURE?

CPROVER now needs a C++11 compliant compiler and works in the following
environments:

- Linux
- MacOS X
- Solaris 11
- FreeBSD 11
- Cygwin
- Microsoft Visual Studio

The rest of this document is split up into three parts: compilation on Linux,
MacOS, Windows.  Please read the section appropriate for your machine.

# COMPILATION ON LINUX

We assume that you have a Debian/Ubuntu or Red Hat-like distribution.

1. You need a C/C++ compiler, Flex and Bison, and GNU make.
   The GNU Make needs to be version 3.81 or higher.
   On Debian-like distributions, do as root:
   ```
   apt-get install g++ gcc flex bison make git curl patch
   ```
   On Red Hat/Fedora or derivates, do as root:
   ```
   dnf install gcc gcc-c++ flex bison curl patch
   ```
   Note that you need g++ version 5.0 or newer.

   On Amazon Linux and similar distributions, do as root:
   ```
   yum install gcc72-c++ flex bison curl patch tar
   ```

   To compile JBMC, you additionally need the JDK and Maven 3. You also
   need jq if you wish to run the entire test suite.
   On Debian-like distributions, do as root:
   ```
   apt-get install openjdk-8-jdk maven jq
   ```
   On Red Hat/Fedora or derivates, do as root:
   ```
   dnf install java-1.8.0-openjdk-devel maven jq
   ```

2. As a user, get the CBMC source via
   ```
   git clone https://github.com/diffblue/cbmc cbmc-git
   cd cbmc-git
   ```

3. To compile, do
   ```
   make -C src minisat2-download
   make -C src
   ```
   See doc/architectural/compilation-and-development.md for instructions on how
   to use a SAT solver other than MiniSat 2.

4. To compile JBMC, do
   ```
   make -C jbmc/src setup-submodules
   make -C jbmc/src
   ```

# COMPILATION ON SOLARIS 11

We assume Solaris 11.4 or newer.  To build JBMC, you'll need to install
Maven 3 manually.

1. As root, get the necessary development tools:
   ```
   pkg install gcc-c++-7 bison flex
   ```
2. As a user, get the CBMC source via
   ```
   git clone https://github.com/diffblue/cbmc cbmc-git
   cd cbmc-git
   ```
3. To compile CBMC, type
   ```
   gmake -C src minisat2-download DOWNLOADER=wget TAR=gtar
   gmake -C src
   ```
4. To compile JBMC, type
   ```
   gmake -C jbmc/src setup-submodules
   gmake -C jbmc/src
   ```

# COMPILATION ON FREEBSD 11

1. As root, get the necessary tools:
   ```
   pkg install bash gmake git www/p5-libwww patch flex bison
   ```
   To compile JBMC, additionally install
   ```
   pkg install openjdk8 wget maven3
   ```
2. As a user, get the CBMC source via
   ```
   git clone https://github.com/diffblue/cbmc cbmc-git
   cd cbmc-git
   ```
3. To compile CBMC, do
   ```
   gmake -C src minisat2-download
   gmake -C src
   ```
4. To compile JBMC, do
   ```
   gmake -C jbmc/src setup-submodules
   gmake -C jbmc/src
   ```

# COMPILATION ON MACOS X

Follow these instructions:

1. You need a C/C++ compiler, Flex and Bison, and GNU make. To this end, first
   install the XCode from the App-store and then type
   ```
   xcode-select --install
   ```
   in a terminal window.
2. Then get the CBMC source via
   ```
   git clone https://github.com/diffblue/cbmc cbmc-git
   cd cbmc-git
   ```
3. To compile CBMC, do
   ```
   make -C src minisat2-download
   make -C src
   ```
4. To compile JBMC, you additionally need Maven 3, which has to be installed
   manually. Then do
   ```
   make -C jbmc/src setup-submodules
   make -C jbmc/src
   ```

# COMPILATION ON WINDOWS

There are two options: the Visual Studio compiler with version 14 (2015) or
later, or the MinGW cross compiler with version 5.4 or later.
We recommend Visual Studio.

Follow these instructions:

1. First install Cygwin, then from the Cygwin setup facility install the
   following packages: `flex, bison, tar, gzip, git, make, wget, patch,
   curl`.
2. Get the CBMC source via
   ```
   git clone https://github.com/diffblue/cbmc cbmc-git
   cd cbmc-git
   ```
3. Depending on your choice of compiler:
   1. To compile with Visual Studio, change the second line of `src/config.inc`
      to
      ```
      BUILD_ENV = MSVC
      ```
      Open the Developer Command Prompt for Visual Studio, then start the
      Cygwin shell with
      ```
      bash.exe -login
      ```
      Please note that this might open a different shell instead, especially if
      you have installed other Linux subsystems previously. To verify that you
      are in the correct shell, make sure that the Windows file system can be
      accessed via the folder`/cygdrive`. If the command above does not open
      the Cygwin shell, you can also access it by using its absolute path,
      `C:\cygwin64\bin\bash.exe` by default. In the Developer Command Prompt, 
      simply type
      ```
      C:\cygwin64\bin\bash.exe -login
      ```
   2. To compile with MinGW, use Cygwin setup to install a mingw g++ compiler
      package, i.e. one of `mingw{32,64}-{x86_64,i686}-gcc-g++`. You may also
      have to adjust the section in `src/common` that defines `CC` and `CXX`
      for BUILD_ENV = Cygwin.
      Then start the Cygwin shell.
4. To compile CMBC, open the Cygwin shell and type
   ```
   make -C src DOWNLOADER=wget minisat2-download
   make -C src
   ```
5. To compile JBMC, you additionally need the JDK and Maven 3, which have
   to be installed manually. Then open the Cygwin shell and type
   ```
   make -C jbmc/src setup-submodules
   make -C jbmc/src
   ```

(Optional) A Visual Studio project file can be generated with the script
"generate_vcxproj" that is in the subdirectory "scripts".  The project file is
helpful for GUI-based tasks, e.g., the class viewer, debugging, etc., and can
be used for building with MSBuild.  Note that you still need to run flex/bison
using "make generated_files" before opening the project.

# WORKING WITH CMAKE

There is also a build based on CMake instead of hand-written
makefiles. It should work on a wider variety of systems than the standard
makefile build, and can integrate better with IDEs and static-analysis tools.
On Windows, the CMake build does not depend on Cygwin or MinGW, and doesn't
require manual modification of build files.

1. Ensure you have all the build dependencies installed. Build dependencies are
   the same as for the makefile build, but with the addition of CMake version
   3.2 or higher. The installed CMake version can be queried with `cmake
   --version`. To install cmake:
   - On Debian-like distributions, do
     ```
     apt-get install cmake
     ```
   - On Red Hat/Fedora or derivates, do
     ```
     dnf install cmake
     ```
   - On macOS, do
     ```
     xcode-select --install
     ```
     You shoud also install [Homebrew](https://brew.sh), after which you can
     run `brew install cmake` to install CMake.
   - On platforms where installing the Java Development Kit and Maven is
     difficult, you can avoid needing these dependencies by not building
     JBMC. Just pass `-DWITH_JBMC=OFF` to cmake in step (4) below.
   - On Windows, ensure you have Visual Studio 2015 or later installed.
     Then, download CMake from the [official download
     page](https://cmake.org/download).
     You'll also need `git` and `patch`, which are both provided by the
     [git for Windows](git-scm.com/download/win) package.
     Finally, Windows builds of flex and bison should be installed from
     [the sourceforge page](sourceforge.net/projects/winflexbison).
     The easiest way to 'install' these executables is to unzip them and to
     drop the entire unzipped package into the CBMC source directory.
   - Use of CMake has not been tested on Solaris or FreeBSD. However, it should
     be possible to install CMake from the system package manager or the
     [official download page](https://cmake.org/download) on those systems.
     The dependencies (as listed in the relevant sections above) will also be
     required, and should be installed using the suggested methods.
2. Navigate to the *top level* folder of the project. This is different from
   the Makefile build, which requires you to navigate to the `src` directory
   first.
3. Update git submodules:
   ```
   git submodule update --init
   ```
4. Generate build files with CMake:
   ```
   cmake -S . -Bbuild
   ```
   This command tells CMake to use the configuration in the current directory,
   and to generate build files into the `build` directory.  This is the point
   to specify custom build settings, such as compilers and build back-ends. You
   can use clang (for example) by adding the argument
   `-DCMAKE_CXX_COMPILER=clang++` to the command line. You can also tell CMake
   to generate IDE projects by supplying the `-G` flag.  Run `cmake -G` for a
   comprehensive list of supported back-ends.

   On macOS >10.14, the build will fail unless you explicitly specify
   the full path to the compiler. This issue is being tracked
   [here](https://github.com/diffblue/cbmc/issues/4956). The invocation thus
   looks like this:
   ```
   cmake -S. -Bbuild -DCMAKE_C_COMPILER=/usr/bin/clang
   ```

   Generally it is not necessary to manually specify individual compiler or
   linker flags, as CMake defines a number of "build modes" including Debug and
   Release modes. To build in a particular mode, add the flag
   `-DCMAKE_BUILD_TYPE=Debug` (or `RelWithDebInfo`) to the initial invocation.
   The default is to perform an optimized build via the `Release` configuration.

   If you *do* need to manually add flags, use `-DCMAKE_CXX_FLAGS=...` and
   `-DCMAKE_EXE_LINKER_FLAGS=...`. This is useful for enabling clang's
   sanitizers.

   Finally, to enable building universal binaries on macOS, you can pass the
   flag `-DCMAKE_OSX_ARCHITECTURES=i386;x86_64`. If you don't supply this flag,
   the build will just be for the architecture of your machine.
5. Run the build:
   ```
   cmake --build build
   ```
   This command tells CMake to invoke the correct tool to run the build in the
   `build` directory. You can also use the build back-end directly by invoking
   `make`, `ninja`, or opening the generated IDE project as appropriate.

# WORKING WITH ECLIPSE

To work with Eclipse, do the following:

1. Select File -> New -> Makefile Project with Existing Code
2. Type "cprover" as "Project Name"
3. Select the "src" subdirectory as "Existing Code Location"
4. Select a toolchain appropriate for your platform
5. Click "Finish"
6. Select Project -> Build All

You can also select the repository's root folder as the "Existing Code 
Location". This has the advantage that you can build both CBMC and JBMC without
the need to integrate JBMC as a separate project. Be aware that you need to 
change the build location (Select project in Eclipse -> Properties -> C/C++ 
Build) to one of the src directories.

# WORKING WITH DOCKER

To compile and run the tools in a Docker container, do the following:

1. From the root folder of the project, run `$ docker build -t cbmc .`
2. After the building phase has finished, there should be a new 
   image with the CProver binaries installed under `/usr/local/bin/`.

   To start a container using that image as a base, run `$ docker run -i -t cbmc`
   This will result in dropping you to a new terminal inside the container. To
   load files for analysis into the container, one way is by mounting the folder
   that contains the tests to the container. A possible invocation that does that
   is: `$ docker run --mount type=bind,source=local/path/with/files,target=/mnt/analysis -i t cbmc`. In the
   resulting container, the files present in the local file system under
   `local/path/with/files` will be present under `/mnt/analysis`. 

# OPTIONS AND VARIABLES

## Compiling with CUDD

Cudd is a BDD library which can be used instead of the builtin miniBDD
implementation.

If compiling with make:

1. Download and compile Cudd:
   ```
   make -C src cudd-download
   ```
2. Uncomment the definition of `CUDD` in the file `src/config.inc`.
3. Compile with `make -C src`

If compiling with cmake:

1. Add the `-DCMAKE_USE_CUDD=true` flag to the `cmake` configuration phase.
   For instance:
   ```
   cmake -S . -Bbuild -DCMAKE_USE_CUDD=true
   ```
2. Run the build:
   ```
   cmake --build build
   ```

## Use BDDs for guards

There are two implementation for symex guards. The default one uses the
internal representation of expression. The other one uses BDDs and
though experimental, it is expected to have better performance,
in particular when used in conjunction with CUDD.

To use the BDD implementation of guards, add the `BDD_GUARDS`
compilation flag:
  * If compiling with make:
    ```
    make -C src CXXFLAGS="-O2 -DBDD_GUARDS"
    ```
  * If compiling with CMake:
    ```
    cmake -S . -Bbuild -DCMAKE_CXX_FLAGS="-DBDD_GUARDS"
    ```
    and then `cmake --build build`

## Compiling with alternative SAT solvers

For the packaged builds of CBMC on our release page we currently build CBMC
with the MiniSat2 SAT solver statically linked at compile time. However it is
also possible to build CBMC using alternative SAT solvers.

### Compiling CBMC Using Solver Native Interfaces

The following solvers are supported by CBMC using custom interfaces and can
by downloaded and compiled by the build process: MiniSAT2, CaDiCaL, and Glucose.

For `make` alternatives to the default (i.e. not MiniSAT) can be built with the
following commands for CaDiCaL:
```
make -C src cadical-download
make -C src CADICAL=../../cadical
```
and for glucose
```
make -C src glucose-download
make -C src GLUCOSE=../../glucose-syrup
```

For `cmake` the alternatives can be built with the following arguments to `cmake`
for CaDiCaL `-Dsat_impl=cadical` and for glucose `-Dsat_impl=glucose`.


### Compiling with IPASIR Interface

The below compiling instructions allow linking of an arbitrary IPASIR
compatible SAT solver when compiling CBMC.

The general command using `make` is to compile with
```
make -C src LIBS="$PWD/SATOBJ SATLINKFLAGS" IPASIR=$PWD/SATPATH
```
Where `SATOBJ` is the pre-compiled IPASIR compatible SAT binary,
`SATLINKFLAGS` are any flags required by the SAT object file, and
`SATPATH` is the path to the SAT interface.

The rest of this section provides detailed instructions for some example
SAT solvers.

#### Compiling with CaDiCaL via IPASIR

Note that CaDiCaL can also be built using CBMC's CaDiCaL native interface
as described above. This section is to use CaDiCaL with the IPASIR
interface in CBMC.

The [CaDiCaL](https://github.com/arminbiere/cadical) solver supports the
[IPASIR](https://github.com/biotomas/ipasir) C interface to incremental SAT
solvers, which is also supported by CBMC. So the process for producing a CBMC
with CaDiCaL build is to build CaDiCaL as a static library then compile CBMC
with the IPASIR build options and link to the CaDiCaL static library.

Note that at the time of writing this has been tested to work with the CaDiCaL
1.4.0 on Ubuntu 18.04 & 20.04 and MacOS.

1. Download CaDiCaL:
   ```
   git clone --branch rel-1.4.0 https://github.com/arminbiere/cadical.git
   ```
   This will clone the CaDiCaL repository into a `cadical` subdirectory and
   checkout release 1.4.0, which has been checked for compatibility with CBMC at
   the time these instructions were written.

2. Build CaDiCaL:
   ```
   cd cadical
   ./configure
   make cadical
   cd ..
   ```
   This will create a build directory called `build` inside the clone of the
   CaDiCaL repository. The `cadical` make target is specified in this example in
   order to avoid building targets which are not required by CBMC. The built
   static library will be placed in `cadical/build/libcadical.a`.

3. Build CBMC:
   ```
   make -C src LIBS="$PWD/cadical/build/libcadical.a" IPASIR=$PWD/cadical/src
   ```
   This links the CaDiCaL library as part of the build. Passing the IPASIR
   parameter tells the build system to build for the IPASIR interface. The
   argument for the IPASIR parameter gives the build system the location for
   the IPASIR headers, which is needed for the cbmc includes of `ipasir.h`. The
   compiled binary will be placed in `cbmc/src/cbmc/cbmc`.

#### Compiling with Riss via IPASIR

The [Riss](https://github.com/conp-solutions/riss) solver supports the
[IPASIR](https://github.com/biotomas/ipasir) C interface to incremental SAT
solvers, which is also supported by CBMC. So the process for producing a CBMC
with Riss build is to build Riss as a static library then compile CBMC with the
IPASIR build options and link to the Riss static library. The following
instructions have been confirmed to work on Ubuntu 20 at the time of writing.
They can also be made to work on Ubuntu 18, by using a debug build of Riss. Riss
uses Linux specific functionality / API calls. Therefore it can't be compiled
successfully on Windows or macOS.

1. Download Riss:
   ```
   git clone https://github.com/conp-solutions/riss riss
   ```
   This will clone the Riss repository into a `riss` subdirectory.

2. Build Riss:
   ```
   cd riss
   cmake -H. -Brelease -DCMAKE_BUILD_TYPE=Release
   cd release
   make riss-coprocessor-lib-static
   cd ../..
   ```
   This will create a build directory called `release` inside the clone of the
   Riss repository and build the static library in
   `riss/release/lib/libriss-coprocessor.a`.

3. Build CBMC:
   ```
   make -C src LIBS="$PWD/riss/release/lib/libriss-coprocessor.a -lpthread" IPASIR=$PWD/riss/riss
   ```
   This links the Riss library and the pthreads library. The pthreads library is
   needed because the Riss library uses it for multithreading. Passing the
   IPASIR parameter tells the build system to build for the IPASIR interface.
   The argument for the IPASIR parameter gives the build system the location for
   the IPASIR headers, which is needed for the cbmc includes of `ipasir.h`. The
   compiled binary will be placed in `cbmc/src/cbmc/cbmc`.
