#include <iostream>
#include "genprimes.hpp"


int main(int argc,char**argv) {
PrimeGenerator generator = PrimeGenerator();
while(true) {
unsigned long long int n = 0;
std::cin >> n;
std::vector<mpz_class> factors =  genprimefactors(mpz_class((unsigned long int)n));
for(mpz_class i : factors) {
  std::cout << i << "\n";
}
std::cout << generator.getNthPrime(n) << "\n";

}
return 0;

}