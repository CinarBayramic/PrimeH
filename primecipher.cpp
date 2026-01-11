#include <gmpxx.h>
#include <vector>
#include <string>
#include "genprimes.hpp"

mpz_class hash(unsigned long int val, char p) {
mpz_class sum;

std::vector<mpz_class> factors = genprimefactors(val);

for(mpz_class i : factors) {
  mpz_class res;
  mpz_pow_ui(res.get_mpz_t(), i.get_mpz_t(),p);
  sum += res;
} 

return sum;

}


unsigned long int hashstrS(std::vector<std::string> toencode, int p ) {

}