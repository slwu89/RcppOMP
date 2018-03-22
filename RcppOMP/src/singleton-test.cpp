/*
 *        ____                   ____  __  _______
 *       / __ \_________  ____  / __ \/  |/  / __ \
 *      / /_/ / ___/ __ \/ __ \/ / / / /|_/ / /_/ /
 *     / _, _/ /__/ /_/ / /_/ / /_/ / /  / / ____/
 *    /_/ |_|\___/ .___/ .___/\____/_/  /_/_/
 *              /_/   /_/
 *
 *    Sean Wu
 *    Testing threadsafe singleton
 *    March 2018
*/

#include <Rcpp.h>
#include <omp.h>
#include <iostream>

#include "singleton.hpp"

//' @export
// [[Rcpp::export]]
void test_singletonOMP(const uint_least32_t &seed){

  singleton::instance().set_seed(seed);

  int tid, nthreads;

  #pragma omp parallel default(shared) private(tid, nthreads)
  {
    tid = omp_get_thread_num();
    nthreads = omp_get_num_threads();

    double lambda = tid*100;

    std::cout << "thread " << tid << " of " << nthreads << " with lambda: " << lambda << " is going to sample a poisson random variate" << std::endl;
    double pois = singleton::instance().get_rpois(lambda);
    std::cout << "thread " << tid << " got " << pois << std::endl;
  }

};
