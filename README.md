# RcppOMP

Testing OpenMP in an Rcpp package

## MacOS (macOS High Sierra v.10.13.3)

Compiler info: Apple LLVM version 9.0.0 (clang-900.0.39.2)

OpenMP installed using homebrew `brew install libomp`; added necessary flags from the thing that brew printed out to the Makevars file. Printout from brew:
```
On Apple Clang, you need to add several options to use OpenMP's front end
instead of the standard driver option. This usually looks like
  -Xpreprocessor -fopenmp -lomp

You might need to make sure the lib and include directories are discoverable
if /usr/local is not searched:

  -L/usr/local/opt/libomp/lib -I/usr/local/opt/libomp/include

For CMake, the following flags will cause the OpenMP::OpenMP_CXX target to
be set up correctly:
  -DOpenMP_CXX_FLAGS="-Xpreprocessor -fopenmp -I/usr/local/opt/libomp/include" -DOpenMP_CXX_LIB_NAMES="omp" -DOpenMP_omp_LIBRARY=/usr/local/opt/libomp/lib/libomp.dylib
```

### To-do:

  1. Figure out how to check in the makefile if compiling under gcc or clang and set flags accordingly.
  2. Do some 'realistic' tests, look into accessing thread-safe singleton objects, especially for getting parallel random number streams.

### Useful links:
  * https://thecoatlessprofessor.com/programming/openmp-in-r-on-os-x/
  * not useful for package development, but a few good examples of how to code with omp: http://gallery.rcpp.org/tags/openmp/
  * slightly older, but useful for setting compilation flags in `makevars`: https://mattstats.wordpress.com/2016/07/12/openmp-on-os-x-using-gcc/ and it references this bit of the official R docs: https://cran.r-project.org/doc/manuals/r-release/R-admin.html#Customizing-package-compilation
  * insanely useful website about omp: https://people.sc.fsu.edu/~jburkardt/cpp_src/hello_openmp/hello_openmp.html
