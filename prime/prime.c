#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <stdarg.h>
#include <time.h>

// generate prime numbers based on sieve of eratosthenes
// support max up to 2^32-1
unsigned *gen_prime (unsigned max, unsigned *p_size) {
    unsigned i, k, p, limit, j;
    unsigned *primes;
    bool *seive;

    if ((seive = malloc((max+1)*sizeof(bool))) == NULL) {
        fprintf(stderr, "Failed to allocate RAM: %s\n", strerror(errno));
        return NULL;
    }

    // reset seive array to true
    memset(seive, true, max);

    limit = (unsigned)sqrtl((double)max);
    for (i = 2; i <= limit; i++) {
        if (seive[i]) {
            k = i*i;
            j = k;
            p = 1;
            while (j <= max) {
                seive[j] = false;
                j = k+i*p;
                p++;
            }
        }
    }

    // count primes
    k = 0;
    for (j = 2; j <= max; j++)
        if (seive[j])
           k++; 

    if ((primes = (unsigned  *)malloc(k*sizeof(unsigned ))) == NULL) {
        fprintf(stderr, "Failed to allocate RAM: %s\n", strerror(errno));
        return NULL;
    }

    j = 0;
    for (i = 2; i <= max; i++)
        if (seive[i]) {
            primes[j] = i;
            j++;
        }

    *p_size = k;
    free(seive);
    return primes;       
}

// generate prime numbers based on sieve of eratosthenes
// support max up to 2^64-1
long unsigned  *gen_prime_ll (long unsigned max, long unsigned *p_size) {
    long unsigned i, k, p, limit, j;
    long unsigned *primes;
    bool *seive;

    if ((seive = malloc((max+1)*sizeof(bool))) == NULL) {
        fprintf(stderr, "Failed to allocate RAM: %s\n", strerror(errno));
        return NULL;
    }

    // reset seive array to true
    memset(seive, true, max);

    limit = (long unsigned)sqrtl((long double)max);
    for (i = 2; i <= limit; i++) {
        if (seive[i]) {
            k = i*i;
            j = k;
            p = 1;
            while (j <= max) {
                seive[j] = false;
                j = k+i*p;
                p++;
            }
        }
    }

    // count primes
    k = 0;
    for (j = 2; j <= max; j++)
        if (seive[j])
           k++; 

    if ((primes = (long unsigned *)malloc(k*sizeof(long unsigned))) == NULL) {
        fprintf(stderr, "Failed to allocate RAM: %s\n", strerror(errno));
        return NULL;
    }

    j = 0;
    for (i = 2; i <= max; i++)
        if (seive[i]) {
            primes[j] = i;
            j++;
        }

    *p_size = k;
    free(seive);
    return primes;       
}


// An iterative binary search function.
bool is_prime(long unsigned x, long unsigned arr[], long unsigned p_size) {
    long unsigned mid, low = 0, high = p_size-1;

    while (low < high) {
        mid = low + (high - low) / 2;

        // Check if x is present at mid
        if (arr[mid] == x)
            return true;

        // If x greater, ignore left half
        if (arr[mid] < x)
            low = mid + 1;

        // If x is smaller, ignore right half 
        else if (mid > 0)
            high = mid - 1;

        // but don't move beyond 0
        else
            break;
    }

    // we got here if low == high
    // Check if x is present at last position possible (low or high)
    if (arr[low] == x)
        return true;
    else
        return false;
}

// An iterative binary search function.
bool is_prime_ll(long unsigned x, long unsigned arr[], long unsigned p_size) {
    long unsigned mid, low = 0, high = p_size-1;

    while (low < high) {
        mid = low + (high - low) / 2;

        // Check if x is present at mid
        if (arr[mid] == x)
            return true;

        // If x greater, ignore left half
        if (arr[mid] < x)
            low = mid + 1;

        // If x is smaller, ignore right half 
        else if (mid > 0)
            high = mid - 1;

        // but don't move beyond 0
        else
            break;
    }

    // we got here if low == high
    // Check if x is present at last position possible (low or high)
    if (arr[low] == x)
        return true;
    else
        return false;
}

