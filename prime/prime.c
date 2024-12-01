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
unsigned long *gen_prime (unsigned long max, unsigned long *p_size) {
    unsigned long i, k, p, limit, j;
    unsigned long *primes;
    bool *seive;

    if ((seive = malloc((max+1)*sizeof(bool))) == NULL) {
        fprintf(stderr, "Failed to allocate RAM: %s\n", strerror(errno));
        return NULL;
    }

    // reset seive array to true
    memset(seive, true, max);

    limit = (unsigned long)sqrtl((long double)max);
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

    if ((primes = (unsigned long *)malloc(k*sizeof(unsigned long))) == NULL) {
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
unsigned long long  *gen_prime_ll (unsigned long long max, unsigned long long *p_size) {
    unsigned long long i, k, p, limit, j;
    unsigned long long *primes;
    bool *seive;

    if ((seive = malloc((max+1)*sizeof(bool))) == NULL) {
        fprintf(stderr, "Failed to allocate RAM: %s\n", strerror(errno));
        return NULL;
    }

    // reset seive array to true
    memset(seive, true, max);

    limit = (unsigned long long)sqrtl((long double)max);
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

    if ((primes = (unsigned long long *)malloc(k*sizeof(unsigned long long))) == NULL) {
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
bool is_prime(unsigned long x, unsigned long arr[], unsigned long p_size) {
    unsigned long mid, low = 0, high = p_size-1;

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
bool is_prime_ll(unsigned long long x, unsigned long long arr[], unsigned long long p_size) {
    unsigned long long mid, low = 0, high = p_size-1;

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

