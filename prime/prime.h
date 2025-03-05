#ifndef PRIME_H_
#define PRIME_H_

#include <stdbool.h>

unsigned *gen_prime (unsigned max, unsigned *p_size);
long unsigned *gen_prime_ll (long unsigned max, long unsigned *p_size);
bool is_prime(long unsigned x, long unsigned arr[], long unsigned p_size);
bool is_prime_ll(long unsigned x, long unsigned arr[], long unsigned p_size);

#endif /* PRIME_H_ */