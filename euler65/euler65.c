/*
The square root of 2 can be written as an infinite continued fraction.
sqrt(2) = 1 + 1/(2 + 1/(2 + 1/(2 + 1/(2 + ...))))
The infinite continued fraction can be written, sqrt(2) = [1; (2)], (2) indicates 
that 2 repeats ad infinitum. In a similar way, sqrt(23) = [4; (1, 3, 1, 8)].
It turns out that the sequence of partial values of continued fractions for square roots provide 
the best rational approximations. Let us consider the convergents for sqrt(2).

1 + 1/2 = 3/2
1 + 1/(2 + 1/2)) = 7/5
1 + 1/(2 + 1/2 + 1/2))) = 17/12
1 + 1/(2 + 1/2 + 1/2 + 1/2)))) = 41/29

Hence the sequence of the first ten convergents for sqrt(2) are:
1, 3/2, 7/5, 17/12, 41/29, 99/70, 239/169, 577/408, 1393/985, 3363/2378, ...
What is most surprising is that the important mathematical 
constant,
e = [2; 1, 2, 1, 1, 4, 1, 1, 6, 1, ... , 1, 2k, 1, ...].
The first ten terms in the sequence of convergents for e are:
2, 3, 8/3, 11/4, 19/7, 87/32, 106/39, 193/71, 1264/465, 1457/536, ...
The sum of digits in the numerator of the 10th convergent is 1 + 4 + 5 + 7 = 17.
Find the sum of digits in the numerator of the 100th convergent of the 
continued fraction for e.

to solve this we need to use big_numbers library.

the 100'th fraction is:
6963524437876961749120273824619538346438023188214475670667/2561737478789858711161539537921323010415623148113041714756
Answer: 272

time:
real    0m0.679s
user    0m0.030s
sys     0m0.060s


*/
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "big_numbers.h"

#define MAX_D 60    // set number of digits in big numbers

typedef struct {
     void *num;        // numerator
     void *dem;        // denominato
} FRACTION;

FRACTION *gen_fr () {
    FRACTION *f;

    if ((f = malloc(sizeof(FRACTION))) == NULL) {
        fprintf(stderr, "Failed to allocate memory for a new REACTION: %s\n", strerror(errno));
        exit (EXIT_FAILURE);
    }

    f->dem = gen_number();
    f->num = gen_number();

    return f;
}

void release_fr (FRACTION *f) {
    if (f != NULL) {
        release(f->num);
        release(f->dem);
        free(f);
    }
}

// Recursive function to return the greatest common denominator of a and b
void gcd( void *a,  void *b, void *c)
{
    void *p;

    p = gen_number();

    if (is_zero(b))
        assign(a, c);
    else {
        modulo(a, b, p);
        gcd(b, p, c);  
    }

    release(p);
  
}

// add two fraction numbers
void add_f (FRACTION *f1, FRACTION *f2, FRACTION *result) {
    void *num, *dem, *g, *p;

    num = gen_number();
    dem = gen_number();
    g = gen_number();
    p = gen_number();

    multiply(f1->num, f2->dem, p);
    multiply(f1->dem, f2->num, g);
    add(p, g, num);
    multiply(f1->dem, f2->dem, dem);

    gcd(dem, num, g);
    divide(num, g, result->num);
    divide(dem, g, result->dem);

    release(num);
    release(dem);
    release(g);
    release(p);
}

// generate fraction based on index into sequance numbers going backward
// assumption sequance has >= i elements
void gen_f (int i, void *seq[MAX_D], FRACTION *f) {
    FRACTION *tf;
    void *t;

    t = gen_number();
    tf = gen_fr();

    make_int(f->dem, "1");
    assign(seq[--i], f->num);

    i--;
    while (i >= 0) {
        make_int(tf->dem, "1");
        assign(seq[i], tf->num);
        assign(f->num, t);
        assign(f->dem, f->num);
        assign(t, f->dem);
        add_f(tf, f, f);    
        i--;      
    }

    release(t);
    release_fr(tf);
}

// generate the sequance for E
void gen_e_seq (int max, void *seq[100]) {
    int i, j;
    void *p;

    p = gen_number();
    
    make_int(seq[0], "2");
    make_int(seq[1], "1");
    make_int(seq[2], "2");

    make_int(p, "2");

    j = 1;
    for (i = 3; i < max; i++) {
        if (j % 3) {
            make_int(seq[i], "1");
        }
        else {
            add(seq[i-3], p, seq[i]);
        }
        j++;
    }

    release(p);
}

int main () {
    FRACTION *f;
    void *seq[100];
    int i, d, sum;
    char num[MAX_D+1], dem[MAX_D+1];
    char *c;

    if (init_big_numbers(MAX_D) != MAX_D)
		return 1;

    f = gen_fr();

    for (i = 0; i < 100; i++)
        seq[i] = gen_number();

    gen_e_seq(100, seq);

    gen_f(100, seq, f);
    
    printf("%s/%s\n", number2str(f->num, num), number2str(f->dem, dem));

    d = digits(f->num);
    sum = 0;
    c = num;
    for (i = 0; i < d; i++)
        sum += c[i] - '0';

    printf("Answer: %d\n", sum);

    for (i = 0; i < 100; i++)
        release(seq[i]);

    release_fr(f);

    return 0;    

}