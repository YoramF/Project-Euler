/*
solution:
brute fource approach.
most of the time is spent in generating the prime numbers array.

answer: 
n: 8319823, factors:8313928, n/t_f(n):1.000709

real    0m49.398s
user    0m0.015s
sys     0m0.045s

*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sets.h"

#define MAX_DIGITS 10
#define MAX_PRIMES 10000000

int binarySearch(unsigned long arr[], unsigned int low, unsigned int high, unsigned long x);

#define is_prime(num,prime_size,prime_arr) binarySearch((prime_arr),0,(prime_size),(num))


// return TRUE if n2 is a permutation of n2
bool is_perm (unsigned long n1, unsigned long n2) {
    int i;
    int digits[MAX_DIGITS];

    if (n1 == n2)
        return false;

    // reset digits
    memset(digits, 0, sizeof(digits));

    // fill digits
    i = 0;
    while (n1) {
        digits[n1 % 10]++;
        n1 /= 10;
        i++;
    }

    // now check n2
    while (n2) {
        if (digits[n2 % 10] > 0) {
            digits[n2 % 10]--;
            i--;
        }

        n2 /= 10;   
    }

    return (i == 0);
}

unsigned long *gen_prime (int max) {
	int ind = 1, p_ind;
    unsigned long i, j, k, p;
	int isPrime;
    unsigned long *primes;

    if ((primes = (unsigned long *)malloc(max*sizeof(unsigned long))) == NULL) {
        fprintf(stderr, "Failed to allocate RAM: %s\n", strerror(errno));
        return NULL;
    }

	primes[0] = 1;
	primes[1] = 2;

    i = 2;
	while (ind < max)
	{
		isPrime = 1;
        i++;
        p_ind = 1;
		// It is enough to check up to the square root of each number.
		// Beyond this value, all factors that constract the number start to repeat
		// For instamce the number 12 is constract of 1 x 12, 2 x 6, 3 x 4, 4 x 3, 6 x 2 and 12 x 1.
		// Square root of 12 is 3.46.. -> 4. Therefor it is enought to check up to 4
		k = (unsigned long)sqrtl(i)+1;
		for (j = primes[p_ind]; j < k; j = primes[++p_ind])
		{
			if (i % j == 0)
			{
				isPrime = 0;
				break;
			}
		}
		if (isPrime)
		{
			primes[++ind] = i;
		}
	}

    return primes;
}

// An iterative binary search function.
int binarySearch(unsigned long arr[], unsigned int low, unsigned int high, unsigned long x) {
    while (low <= high) {
        unsigned int mid = low + (high - low) / 2;

        // Check if x is present at mid
        if (arr[mid] == x)
            return mid;

        // If x greater, ignore left half
        if (arr[mid] < x)
            low = mid + 1;

        // If x is smaller, ignore right half
        else
            high = mid - 1;
    }

    // If we reach here, then element was not present
    return -1;
}

void gen_prime_factors (unsigned long num, SET *s, unsigned long *primes) {
    int i, r_sum;
    set_clear(s);

    if (is_prime(num, num, primes) > 0) {
        set_insert(s, &num);
        return;
    }


    i = 1;
    r_sum = num;

    while (r_sum > 1 && primes[i] <= r_sum && i < MAX_PRIMES) {
        if (r_sum % primes[i] == 0) {
            set_insert(s, &primes[i]);
            do {
                r_sum /= primes[i];
            } while (r_sum % primes[i] == 0);

            if (is_prime(r_sum, r_sum, primes) > 0) {
                set_insert(s, &r_sum);
                return;
            }
        }
        i++;
    }
}

unsigned long totient_function (unsigned long n, SET *set) {
    unsigned long  *p;
    unsigned long long d; 

    S_GET_NEXT g_n;

    g_n = set_reset_get(set);

    d = n;
    while ((p = (unsigned long *)(set_get_next_e(&g_n))) != NULL) {
        d = (d*(*p-1))/(*p);
    }

    return (unsigned long)d;
}

int main () {
    unsigned long p, Ln, Ltf, ultf;
    SET *set;
    double long d, Md;
    unsigned long *primes;

    set = set_create(20, sizeof(p));
    primes = gen_prime(MAX_PRIMES);

    Md = 10000000.0;
    Ln = 0;

    for (p = 2; p < 10000000; p++) {
        gen_prime_factors(p, set, primes);
        ultf = totient_function(p, set);
        if (is_perm(p, ultf)) {
            d = (double long)p/(double long)ultf;
            if (d < Md) {
                Ln = p;
                Md = d;
                Ltf = ultf;
            }
        }
    }

    printf("n: %ld, factors:%ld, n/t_f(n):%Lf\n", Ln, Ltf, Md);

    set_delete(set);
    return 0;
}