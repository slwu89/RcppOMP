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
#include <vector>

#include "singleton.hpp"

//' @export
// [[Rcpp::export]]
std::vector<double> test_singletonOMP(const uint_least32_t &seed){

  std::vector<double> out;

  singleton::instance().set_seed(seed);

  int tid, nthreads;

  /* parallel section */
  #pragma omp parallel default(shared) private(tid, nthreads) shared(out)
  {
    tid = omp_get_thread_num();
    nthreads = omp_get_num_threads();

    double lambda = tid*100;

    std::cout << "thread " << tid << " of " << nthreads << " with lambda: " << lambda << " is going to sample a poisson random variate" << std::endl;
    double pois = singleton::instance().get_rpois(lambda);
    std::cout << "thread " << tid << " got " << pois << std::endl;
    #pragma omp critical
    {
      out.push_back(pois);
    }
  }
  return out;
};
