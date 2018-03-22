/*
 *  Testing thread-safe singleton object
 *  Sean Wu
 *  March 2018
 *
*/

#ifndef SINGLETON
#define SINGLETON

#include <random>
#include <iostream>

class singleton final {
public:
  /* utility methods */
  static singleton&                      instance(); /* get instance */

  /* testing bits */
  void                                   set_seed(const uint_least32_t& seed);
  int                                    get_rpois(double lambda);


private:
  /* constructor & destructor */
  singleton();
  ~singleton();

  /* delete all copy & move semantics */
  singleton(const singleton&) = delete;
  singleton& operator=(const singleton&) = delete;
  singleton(singleton&&) = delete;
  singleton& operator=(singleton&&) = delete;

  /* prng testing */
  std::mt19937                            rng;
};

#endif
