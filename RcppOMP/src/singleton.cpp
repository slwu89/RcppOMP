/*
 *  Testing thread-safe singleton object
 *  Sean Wu
 *  March 2018
 *
*/

#include "singleton.hpp"

/* constructor & destructor */
singleton::singleton(){
  std::cout << "singleton being born at " << this << std::endl;
};

singleton::~singleton(){
  std::cout << "singleton being killed at " << this << std::endl;
};

/* utility methods */
singleton& singleton::instance(){
    static singleton instance;
    return instance;
};

/* testing bits */
void singleton::set_seed(const uint_least32_t &seed){
  rng.seed(seed);
};

int singleton::get_rpois(double lambda){
  std::poisson_distribution<int>rpois(lambda);
  return rpois(rng);
};
