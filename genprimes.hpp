#include <gmpxx.h>
#include <vector>

class PrimeGenerator {
public:
  std::vector<mpz_class> primes;

  PrimeGenerator() {
    primes.push_back(2);
    primes.push_back(3);
  };

  void genPrimes(unsigned long long int n) {
    for(mpz_class i = primes.back() + 1; primes.size() < n; i+=2) {
      bool isdivisible = false;
      for(unsigned long long j = 0;j < primes.size();j++ ) {
        if (primes[j] * primes[j] > i) break;
        if(i % primes[j] == 0) {
          isdivisible = true;
          break;
        }
      }
      if(!isdivisible) {
        primes.push_back(i);
      }
    }
  }
  void genClosestPrimes(mpz_class n) {
    mpz_class N;
    N = n;
    for(mpz_class i = primes.back() + 1; primes.back() < N; i+=2) {
      bool isdivisible = false;
      for(unsigned long long j = 0;j < primes.size();j++ ) {
        if (primes[j] * primes[j] > i) break;
        if(i % primes[j] == 0) {
          isdivisible = true;
          break;
        }
      }
      if(!isdivisible) {
        primes.push_back(i);
      }
    }
  }
  mpz_class getNthPrime(unsigned long long int n) {
    if(n <= primes.size()) {
      return primes[n-1];
    } else {
      genPrimes(n);
      return primes[n-1];
    }
  }

};


std::vector<mpz_class> genprimefactors(mpz_class val) {
  PrimeGenerator p;
  p.genClosestPrimes(val);

}