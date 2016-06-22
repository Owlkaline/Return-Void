#include "../../include/Namespaces/Random.h"

void Random::newSeed(unsigned long long _seed) {  
  seed = _seed;
  rng.seed(seed);
}

int Random::Int(unsigned long long min, unsigned long long max) {
  boost::random::uniform_int_distribution<> dist(min, max);
  return dist(rng);
}

int Random::Int(double a, double b, double c) {
  double probabilities[] = {
    a, b, c
  };
  boost::random::discrete_distribution<> dist(probabilities);
  return dist(rng) + 1;
}

int Random::Int(double a, double b, double c, double d) {
  double probabilities[] = {
    a, b, c, d
  };
  boost::random::discrete_distribution<> dist(probabilities);
  return dist(rng) + 1;
}
