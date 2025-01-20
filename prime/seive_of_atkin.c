#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <stdarg.h>

#define MOD_60_PRIME 16

static int p1 [MOD_60_PRIME] = {1,7,11,13,17,19,23,29,31,37,41,43,47,49,53,59};

bool is_in_set (int num, int n, ...) {
    va_list ap;
    int i;

    va_start(ap, n);
    for ( ;n > 0; n--) {
        i = va_arg(ap, int);
        if (i == num)
            return true;
    }
    return false;
}





// generate array of prime numbers
// largest prime in array is no bigger than max_p
// r_size is updated with the actual numeber of generated primes
unsigned long *gen_prime_sevie_atkin (unsigned long max_p, unsigned long *r_size) {
    bool *seive;
    unsigned long *primes;
    unsigned long x, y, w, i, x2, w2;
    unsigned long long n, n2, c;

    // allocate ram for seive array
    if ((seive = calloc(max_p+1, sizeof(bool))) == NULL) {
        fprintf(stderr, "Failed to allocate RAM for seive: %s\n", strerror(errno));
        return NULL;
    }

    // Put in candidate primes:
    //   integers which have an odd number of
    //   representations by certain quadratic forms.
    // Algorithm step 3.1:
    x = 1;

    while (true) {
        if ((unsigned long long)(4*x*x) > max_p)
            break;
        y = 1;           
        while (true) {     
            n = 4 * (unsigned long long)(x*x) + (unsigned long long)(y*y);
            if (n <= max_p) {
                if (is_in_set(n % 60, 8, 1,13,17,29,37,41,49,53))
                  seive[n] = !seive[n];                  
            }
            else
                break;
            y += 2;         // all odd numbers 1..max_p
        }
        x++;  // all numbers 1..max_p
    }

    // Algorithm step 3.2:
    x = 1;
    while (true) {  // all odd numbers 1..max_p
        if ((unsigned long long)(3*x*x) > max_p)
            break;
        y = 2;
        while (true) {
            n = 3 * (unsigned long long)(x*x) + (unsigned long long)(y*y);
            if (n <= max_p) {
                if (is_in_set(n % 60, 4, 7,19,31,43))
                  seive[n] = !seive[n]; 
            } 
            else
                break;
            y += 2;     // all even numbers
        }
        x += 2;     // all odd numbers
    }

    // Algorithm step 3.3:
    x = 2;
    while (true) {
        if ((unsigned long long)(2*x*x) > max_p)
            break;
        i = 1;
        while (true) {
            if (x <= i)
                break;

            y = x - i;
            n = 3 * (unsigned long long)(x*x) - (unsigned long long)(y*y);
            if (n <= max_p) {
                if (is_in_set(n % 60, 4, 11,23,47,59))
                  seive[n] = !seive[n];  
            }
            else
                break;
            i += 2;
        }
        x++;        // x = 2, 3, 4, ....
    }

    // Eliminate composites by sieving, only for those occurrences on the wheel:
    w = 0;
    while (true) {
        for (x = 0; (x < MOD_60_PRIME); x++) {
            n = 60 * w + p1[x];
            n2 = n*n;
            if (n2 > max_p)
                goto done_last_loop;

            if (n >= 7) {
                if (seive[n]) {
                    // n is prime, omit multiples of its square; this is sufficient 
                    // because square-free composites can't get on this list
                    w2 = 0;
                    while (true) {
                        if ((unsigned long long)n2*w2 > max_p)
                            break;
                        for (x2 = 0; (x2 < MOD_60_PRIME); x2++) {
                            c = n2 * (60 * w2 + p1[x2]);
                            if (c <= max_p)
                                seive[c] = false;
                            else
                                break;
                        }
                        w2++;
                    }
                }
            }
        }
        w++;    
    }

done_last_loop:

    // one sweep to produce a sequential list of primes up to limit:
    // allocate ram for seive array
    if ((primes = malloc(max_p*sizeof(unsigned long))) == NULL) {
        fprintf(stderr, "Failed to allocate RAM for primes: %s\n", strerror(errno));
        return NULL;
    }

    primes[0] = 2;
    primes[1] = 3;
    primes[2] = 5;
    *r_size = 3;
    w = 0;
    while (true) {
        if (60*w+1 > max_p)
            break;
        for (x = 0; (x < MOD_60_PRIME); x++) {
            n = 60 * w + p1[x];
            if (n >= 7) {
                if (n <= max_p) {
                    if (seive[n]) {
                        primes[*r_size] = n;
                        (*r_size)++;
                    }
                }
                else
                    break;
            }
        }
        w++;
    }

    free(seive);

    primes = realloc(primes, *r_size*sizeof(unsigned long));
    return primes;
    // return seive;
}