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

    if (is_prime_ll(97, primesl, psizel))
        printf("97 is prime\n");

    if (is_prime_ll(2, primesl, psizel))
        printf("2 is prime\n");


    if (!is_prime_ll(1, primesl, psizel))
        printf("1 is not prime\n");

    max = atol(argv[1]);
    st = time(NULL);
    primes = gen_prime(max, &psize);
    en = time(NULL);

    printf("time: %u sec\n", en-st);
    printf("size: %lu, last: %lu\n", psize, primes[psize-1]);



    free(primes);

    return 1;

}