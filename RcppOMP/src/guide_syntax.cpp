/*
 *        ____                   ____  __  _______
 *       / __ \_________  ____  / __ \/  |/  / __ \
 *      / /_/ / ___/ __ \/ __ \/ / / / /|_/ / /_/ /
 *     / _, _/ /__/ /_/ / /_/ / /_/ / /  / / ____/
 *    /_/ |_|\___/ .___/ .___/\____/_/  /_/_/
 *              /_/   /_/
 *
 *    Sean Wu
 *    Syntax: https://bisqwit.iki.fi/story/howto/openmp/#Syntax
 *    March 2018
*/

#include <Rcpp.h>
#include <omp.h>
#include <cmath>

//' Nested loops (collapse and run in parallel)
//'
//' @param xmax number of rows
//' @param ymax number of columns
//'
//' @export
// [[Rcpp::export]]
Rcpp::NumericMatrix nesting_collapse(const int xmax, const int ymax){

  double out[xmax][ymax];

  #pragma omp parallel for collapse(2)
  for(int y=1; y<=ymax; ++y){
    for(int x=1; x<=xmax; ++x){
      out[x-1][y-1] = x*y;
    }
  }

  return Rcpp::NumericMatrix(xmax,ymax,*out);
}

//' Nested loops (serial for comparison)
//'
//' @param xmax number of rows
//' @param ymax number of columns
//'
//' @export
// [[Rcpp::export]]
Rcpp::NumericMatrix nesting_serial(const int xmax, const int ymax){

  double out[xmax][ymax];

  for(int y=1; y<=ymax; ++y){
    for(int x=1; x<=xmax; ++x){
      out[x-1][y-1] = x*y;
    }
  }

  return Rcpp::NumericMatrix(xmax,ymax,*out);
}
