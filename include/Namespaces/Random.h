#ifndef BOOSTRANDOM
#define BOOSTRANDOM

#include <boost/random.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/discrete_distribution.hpp>

class Random {
  public:
    void newSeed(unsigned long long _seed);
    int Int(unsigned long long min, unsigned long long max);
    int Int(double a, double b, double c);
    int Int(double a, double b, double c, double d);
  private:
    unsigned long long seed;
    boost::mt19937 rng;
};

#endif
