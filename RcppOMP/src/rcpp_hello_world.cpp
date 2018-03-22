#include <omp.h>
#include <iostream>
#include <thread>

#include <Rcpp.h>
using namespace Rcpp;

//' @export
// [[Rcpp::export]]
List rcpp_hello_world() {

    CharacterVector x = CharacterVector::create( "foo", "bar" )  ;
    NumericVector y   = NumericVector::create( 0.0, 1.0 ) ;
    List z            = List::create( x, y ) ;

    return z ;
}

//' @export
// [[Rcpp::export]]
void rcpp_hello_world_omp()
{
  int tid, nthreads;

  #pragma omp parallel default(shared) private(tid, nthreads)
  {
    tid = omp_get_thread_num();
    nthreads = omp_get_num_threads();

    std::cout << "Hello from thread " << tid << " of " << nthreads << std::endl;
  }
}
