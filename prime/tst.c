#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "prime.h"

int main (int argc, char *argv[]) {
    unsigned long long maxl, psizel;
    unsigned long long *primesl;
    unsigned long max, psize;
    unsigned long *primes;
    time_t st, en;

    if (argc < 1)
        return 0;

    maxl = atoll(argv[1]);
    st = time(NULL);
    primesl = gen_prime_ll(maxl, &psizel);
    en = time(NULL);

    printf("time: %u sec\n", en-st);
    printf("size: %llu, last: %llu\n", psizel, primesl[psizel-1]);
    free(primesl);

    max = atol(argv[1]);
    st = time(NULL);
    primes = gen_prime(max, &psize);
    en = time(NULL);

    printf("time: %u sec\n", en-st);
    printf("size: %lu, last: %lu\n", psize, primes[psize-1]);


    free(primes);

    return 1;

}