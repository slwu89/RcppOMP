/*
 *        ____                   ____  __  _______
 *       / __ \_________  ____  / __ \/  |/  / __ \
 *      / /_/ / ___/ __ \/ __ \/ / / / /|_/ / /_/ /
 *     / _, _/ /__/ /_/ / /_/ / /_/ / /  / / ____/
 *    /_/ |_|\___/ .___/ .___/\____/_/  /_/_/
 *              /_/   /_/
 *
 *    Sean Wu
 *    Introduction: https://bisqwit.iki.fi/story/howto/openmp/#IntroductionToOpenmpInC
 *    March 2018
*/

#include <Rcpp.h>
#include <omp.h>
#include <cmath>
/* for mandelbrot fractal */
#include <complex>
#include <cstdio>

//' Initialize an array of doubles in parallel
//'
//' Initialize an array (sin function) in parallel.
//'
//' @param size size of array
//'
//' @export
// [[Rcpp::export]]
Rcpp::NumericVector table_multiple_threads(const int size){

  double sinTable[size];

  #pragma omp parallel for
  for(int n=0; n<size; ++n){
    sinTable[n] = std::sin(2 * M_PI * n / size);
  }

  return Rcpp::NumericVector(sinTable,sinTable+sizeof(sinTable)/sizeof(*sinTable));
}

//' Initialize an array of doubles with SIMD (single thread; vectorized)
//'
//' Initialize an array (sin function) with SIMD. Please note this probably won't
//' be any faster than serial without a parallel floating point library (AMD and Intel have some).
//'
//' @param size size of array
//'
//' @export
// [[Rcpp::export]]
Rcpp::NumericVector table_simd(const int size){

  double sinTable[size];

  #pragma omp simd
  for(int n=0; n<size; ++n){
    sinTable[n] = std::sin(2 * M_PI * n / size);
  }

  return Rcpp::NumericVector(sinTable,sinTable+sizeof(sinTable)/sizeof(*sinTable));
}

//' Initialize an array of doubles in serial
//'
//' Initialize an array (sin function) in serial. This is for comparison purposes.
//'
//' @param size size of array
//'
//' @export
//' @export
// [[Rcpp::export]]
Rcpp::NumericVector table_serial(const int size){

  double sinTable[size];

  for(int n=0; n<size; ++n){
    sinTable[n] = std::sin(2 * M_PI * n / size);
  }

  return Rcpp::NumericVector(sinTable,sinTable+sizeof(sinTable)/sizeof(*sinTable));
}

/* mandelbrot fractal */
typedef std::complex<double> complex;

int MandelbrotCalculate(complex c, int maxiter){
    // iterates z = z + c until |z| >= 2 or maxiter is reached,
    // returns the number of iterations.
    complex z = c;
    int n=0;
    for(; n<maxiter; ++n)
    {
        if( std::abs(z) >= 2.0) break;
        z = z*z + c;
    }
    return n;
}

//' Calculate and display Mandelbrot fractal
//'
//' See the title; uses ordered dynamic scheduling for parallelism.
//'
//' @param width resolution
//' @param height resolution
//'
//' @export
// [[Rcpp::export]]
void mandelbrot(const int width = 78, const int height = 44){

  int num_pixels = width*height;

  const complex center(-.7, 0), span(2.7, -(4/3.0)*2.7*height/width);
  const complex begin = center-span/2.0;//, end = center+span/2.0;
  const int maxiter = 100000;

  #pragma omp parallel for ordered schedule(dynamic)
  for(int pix=0; pix<num_pixels; ++pix){
    const int x = pix%width, y = pix/width;

    complex c = begin + complex(x * span.real() / (width +1.0),
                                y * span.imag() / (height+1.0));

    int n = MandelbrotCalculate(c, maxiter);
    if(n == maxiter) n = 0;

    #pragma omp ordered
    {
      char c = ' ';
      if(n > 0)
      {
          static const char charset[] = ".,c8M@jawrpogOQEPGJ";
          c = charset[n % (sizeof(charset)-1)];
      }
      std::putchar(c);
      if(x+1 == width) std::puts("|");
    }
  }
}
