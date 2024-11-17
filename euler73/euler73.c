/*

Super naive solution using huge sorted array of fractions
Between 1/3 to 1/2, there are 7295372 fractions

real    0m38.612s
user    0m0.016s
sys     0m0.076s

*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_DENOMINATOR 12000

typedef struct {
    short num;
    short den;
    long double ld;
} fraction;

// find commong denominator of a, b
int gdc (int a, int b) {
    int x;

    if (b == 0)
        return (a);
    else {
        x = a % b;
        return gdc(b, x);  
    }   
}

int qs_func (const void *a, const void *b) {
    fraction _a, _b;

    _a = *(fraction *)a;
    _b = *(fraction *)b;

    if (_a.ld > _b.ld)
        return 1;
    else if (_a.ld < _b.ld)
        return -1;
    else
        return 0;
}

int main () {
    fraction *fr;
    int n, d, i, e;

    e = (MAX_DENOMINATOR * MAX_DENOMINATOR - MAX_DENOMINATOR) / 2;
    if ((fr = calloc(e ,sizeof(fraction))) == NULL) {
        fprintf(stderr, "Failed to allocate RAM: %s\n", strerror(errno));
        return 1;
    }

    i = 0;
    for (d = 2; d <= MAX_DENOMINATOR; d++) {
        for (n = 1; n < d; n++) {
            fr[i].num = n;
            fr[i].den = d;
            if (gdc(n, d) == 1)
                fr[i].ld = fr[i].num*1.0/fr[i].den*1.0;
            i++;
        }
    }

    qsort(fr, e, sizeof(fraction), qs_func);

    // for (i = 0; i < e; i++)
    //     printf("[%d] %d/%d = %Lf\n", i, fr[i].num, fr[i].den, fr[i].ld);

    // advance to first fraction with ld > 0
    i = 0;
    d = 0;
    while (fr[d].ld == 0) d++;

    //find first fr[d] where fr[d].den == 3    
    while (fr[d].den > 3) d++;

    d++;    // skip 1/3
    // find first fr[d] where fr[d].den == 2
    while (fr[d].den > 2) {
        d++;
        i++;
    }

    printf("Between 1/3 to 1/2, there are %d fractions\n", i);

    free(fr);

    return 0;

}