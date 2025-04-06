/*
https://projecteuler.net/problem=108

Solution: 1/x+1/y=1/n => n*x+n*y=x*y => 0 = n*x+n*y-x*y => 
n^2 = x*y-n*x-n*y+n^2 => n^2=(x-n)(y-n) => n^2=a*b

If we find n such that total number of all the possible factors for n^2 is greater than
1,000 we find the solution. This solution is a kind of brute force approach.

n: 180180

real    2m21.743s
user    2m21.269s
sys     0m0.081s

*/

#include <stdio.h>


unsigned int factors (unsigned int n) {
    long unsigned int n2 = (long unsigned int)n*(long unsigned int)n;
    unsigned int i, c;

    c = 2;
    for (i = 2; i < n; i++) {
        if (n2 % i == 0) {
            c++;
        }
    }

    return c;
}


int main () {
    unsigned int n, c;

    c = 2;
    n = 1000;
    while(c <= 1000) {
        n++;
        c = factors(n);
    }

    printf("n: %u\n", n);

    return 0;
}