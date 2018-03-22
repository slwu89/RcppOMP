#include <omp.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <thread> /* for getting num of threads */

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

//' @export
// [[Rcpp::export]]
void rcpp_hello_world_omp_2(){
  int id;
  double wtime;

  std::cout << "\n";
  std::cout << "HELLO_OPENMP\n";
  std::cout << "  C++/OpenMP version\n";

  std::cout << "\n";
  std::cout << "  Number of processors available = " << omp_get_num_procs ( ) << "\n";
  std::cout << "  Number of threads =              " << omp_get_max_threads ( ) << "\n";

  wtime = omp_get_wtime ( );
//
//  Have each thread say hello
//
# pragma omp parallel \
  private ( id )
  {
    id = omp_get_thread_num ( );
    std::cout << "  This is process " << id << "\n";
  }
//
//  Finish up by measuring the elapsed time.
//
  wtime = omp_get_wtime ( ) - wtime;
//
//  Terminate.
//
  std::cout << "\n";
  std::cout << "HELLO_OPENMP\n";
  std::cout << "  Normal end of execution.\n";

  std::cout << "\n";
  std::cout << "  Elapsed wall clock time = " << wtime << "\n";
}
