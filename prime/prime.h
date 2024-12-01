#ifndef PRIME_H_
#define PRIME_H_

#include <stdbool.h>

unsigned long *gen_prime (unsigned long max, unsigned long *p_size);
unsigned long long  *gen_prime_ll (unsigned long long max, unsigned long long *p_size);
bool is_prime(unsigned long x, unsigned long arr[], unsigned long p_size);
bool is_prime_ll(unsigned long long x, unsigned long long arr[], unsigned long long p_size);

#endif /* PRIME_H_ */