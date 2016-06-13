#include "../../include/Namespaces/Random.h"

void Random::newSeed(unsigned long long _seed) {  
  seed = _seed;
  rng.seed(seed);
}

int Random::Int(unsigned long long min, unsigned long long max) {
  boost::random::uniform_int_distribution<> dist(min, max);
  return dist(rng);
}
