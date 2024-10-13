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

#include "big_numbers.h"

#define MAX_D 60    // set number of digits in big numbers

typedef struct {
     char num[MAX_D];        // numerator
     char dem[MAX_D];        // denominato
} FRACTION;

// Recursive function to return the greatest common denominator of a and b
void gcd( char a[],  char b[], char c[])
{
    char p[DIM];

    if (is_zero(b))
        assign(a, c);
    else {
        modulo(a, b, p);
        gcd(b, p, c);  
    }
  
}

// add two fraction numbers
void add_f (FRACTION *f1, FRACTION *f2, FRACTION *result) {
    char num[DIM], dem[DIM], g[DIM], p[DIM];

    multiply(f1->num, f2->dem, p);
    multiply(f1->dem, f2->num, g);
    add(p, g, num);
    multiply(f1->dem, f2->dem, dem);

    gcd(dem, num, g);
    divide(num, g, result->num);
    divide(dem, g, result->dem);
}

// generate fraction based on index into sequance numbers going backward
// assumption sequance has >= i elements
void gen_f (int i, char seq[][MAX_D], FRACTION *f) {
    FRACTION tf;
    char t[MAX_D];

    make_int(f->dem, "1");
    assign(seq[--i], f->num);

    i--;
    while (i >= 0) {
        make_int(tf.dem, "1");
        assign(seq[i], tf.num);
        assign(f->num, t);
        assign(f->dem, f->num);
        assign(t, f->dem);
        add_f(&tf, f, f);    
        i--;      
    }
}

// generate the sequance for E
void gen_e_seq (int max, char seq[][MAX_D]) {
    int i, j;
    char p[MAX_D];

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
}

int main () {
    FRACTION f;
    char seq[100][MAX_D];
    int i, d, sum;
    char num[MAX_D+1], dem[MAX_D+1];

    if (init_big_numbers(MAX_D) != MAX_D)
		return 1;

    gen_e_seq(100, seq);

    gen_f(100, seq, &f);
    
    printf("%s/%s\n", number2str(f.num, num), number2str(f.dem, dem));

    d = digits(f.num);
    sum = 0;

    for (i = 0; i <= d; i++)
        sum += f.num[i];

    printf("Answer: %d\n", sum);

    return 0;    

}