#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define BASE 10
unsigned int DIM = 1;

bool is_bigger_equale_ (const char A[], const char B[], bool equal);
#define is_bigger(a,b) is_bigger_equale_((a), (b), false)
#define is_bigger_e(a,b) is_bigger_equale_((a), (b), true)

// this function must be called before using big_numbers function
// dim parameter will set the max number of digits in big_numbers
unsigned int init_big_numbers (unsigned int dim) {
	DIM = dim;
	return DIM;
}

// put a number represented as a string into the big int A
void make_int (char A[], char *s) {
	int	i, l;
	char *p;

	// get input number len
	l = strlen(s);
	p = s+l-1;

	// start indexing at the DIM's place
	i = 0;

	// while there is still something left to the string and we did not exceeded DIM
	// we're encoding... 
	while (p >= s && i < DIM) {
		// put the least significant digit of n into A[i] 
		A[i] = *p - '0';
		i++;
		p--;
	}

	// fill the rest of the array up with zeros 
	while (i < DIM) A[i++] = 0;
}

// A++ 
void increment (char A[]) {
	int	i;

	// start indexing at the least significant digit 
	i = 0;
	while (i < DIM) {

		// increment the digit 
		A[i]++;

		// if it overflows (i.e., it was 9, now it's 10, too
		// big to be a digit) then...
		if (A[i] == BASE) {

			// make it zero and index to the next 
			// significant digit 
			A[i] = 0;
			i++;
		} else 
			// otherwise, we are done 
			break;
	}
}

// C = A + B 
void add (const char A[], const char B[], char C[]) {
	int	i;
    char carry, sum;

	// no carry yet 
	carry = 0;

	// go from least to most significant digit 
	for (i=0; i<DIM; i++) {

		// the i'th digit of C is the sum of the
		// i'th digits of A and B, plus any carry
		sum = A[i] + B[i] + carry;

		// if the sum exceeds the base, then we have a carry. 
		if (sum >= BASE) {

			carry = 1;

			// make sum fit in a digit (same as sum %= BASE) 
			sum -= BASE;
		} else
			// otherwise no carry 
			carry = 0;

		// put the result in the sum 
		C[i] = sum;
	}
}

// return index to most significat digit in input number 
int digits (const char A[]) {
	int i;

	i =DIM- 1;
	while ((A[i] == 0) && (i > 0))
		i--;

	return i;
}

// C = A - B 
void sub (const char A[], const char B[], char C[]) {
	int i, j, k;
	char P[DIM];

	// init C 
	memset(C, 0, DIM);

	// int P[] - we need P[] so that A[] will remain unchanged 
	memcpy(P, A, DIM);

	for (i = 0; i < DIM; i++) {
		if (P[i] >= B[i])
			C[i] = P[i] - B[i];
		else {
			// make a loan from next digit 
			j = i + 1;
			P[i] += 10;

			// find location of most significant digit in B number
			k = digits(B);

			while (j <= k && P[j] == 0)
				P[j++] = 9;
			if (j < DIM)
				P[j]--;

			C[i] = P[i] - B[i];				
		}
	}
}

// check if A[] is bigger or equal (e = true) to B[] 
bool is_bigger_equale_ (const char A[], const char B[], bool equal) {
	int s1, s2;

	s1 = digits(A);
	s2 = digits(B);

	// scan down the digits
	if (s1 == s2) {
		while (s1 >= 0) {
			if (A[s1] > B[s1])
				return true;
			else if (A[s1] < B[s1])
				return false;
			s1--;
		}

		// we get here only if the two numbers are equale
		// the return value depends on the input variable 'equal'
		return equal;
	}
	
	return (s1 > s2);
}

// check if A[] is equal to B[] 
bool is_equal (const char A[], const char B[]) {
	int s1, s2;

	s1 = digits(A);
	s2 = digits(B);

	// scan down the digits
	if (s1 == s2) {
		while (s1 >= 0) {
			if (A[s1] != B[s1])
				return false;
			s1--;
		}

		// we get here only if the two numbers are equale
		return true;
	}
	
	return false;
}

// B = n * A 
static void multiply_one_digit_ (const char A[], char B[], char n) {
	int	i;
    char carry;

	/// no extra overflow to add yet 
	carry = 0;

	// for each digit, starting with least significant... 
	for (i=0; i<DIM; i++) {

		// multiply the digit by n, putting the result in B 
		B[i] = n * A[i];

		//add in any overflow from the last digit 
		B[i] += carry;

		// if this product is too big to fit in a digit... 
		if (B[i] >= BASE) {
			// handle the overflow 
			carry = B[i] / BASE;
			B[i] %= BASE;
		} else
			// no overflow 
			carry = 0;
	}
}


// "multiplies" a number by BASEn 
static void shift_left_ (char A[], char n) {
	int	i;

	// going from left to right, move everything over to the
	// left n spaces
	for (i=DIM-1; i>=n; i--) A[i] = A[i-n];

	// fill the last n digits with zeros 
	while (i >= 0) A[i--] = 0;
}

// C = A * B 
void multiply (const char A[], const char B[], char C[]) {
	int	i, j;
    char P[DIM];

	// C will accumulate the sum of partial products.  It's initially 0. 
	memset(C, 0, DIM);

	// for each digit in A... 
	for (i=0; i<DIM; i++) {

		// multiply B by digit A[i] 
		multiply_one_digit_(B, P, A[i]);

		// shift the partial product left i bytes 
		shift_left_(P, i);

		// add result to the running sum 
		add (C, P, C);
	}
}

// C[] = A[] / B[] (no reminders)
void divide (const char A[], const char B[], char C[]) {
	char P[DIM], M[DIM], MO[DIM];
	int p, a, sb, sa, i;
	bool done = false;

	// reset C[] & P[]
	memset(C, 0, DIM);
	memset(P, 0, DIM);

	// get index to most significant digits of A & B
	sa = digits(A);
	sb = digits(B);

	// quick check if divisor is bigger than dividend
	// first check we are not dividing by ZERO in that case return false
	if (B[sb] == 0) {
		fprintf(stderr, "DIVIDE BY ZERO!, program exit..\n");
		exit(1);
	}

	// second check if divisor has more digits than dividend
	else if (sb > sa)
		return;
	// third if both have same number of digits, check most significan digit of each number
	else if (sa == sb && A[sa] < B[sb])
		return;

	// if we get here we need to perform long division

	// get initial sub dividend
	for (i = sb; i >= 0; i--)
		P[i] = A[i+sa-sb];

	sa -= (sb+1);

	// loop untill P[]==0 or no more digits to pull from A[]
	while (!done) {
		p = 0;
		memcpy(M, B, DIM);		// to make sure we also copy all zeros
		while (is_bigger_e(P, M)) {
			memcpy(MO, M, DIM);
			p++;
			add(M, B, M);
		}

		// update C[]
		shift_left_(C, 1);
		C[0] = p;

		// check if we can proceed with subtcation
		if (p > 0) {
			if (is_bigger_e(P, MO)) {
				sub(P, MO, M);
				memcpy(P, M, DIM);
			}
		}

		// increase P[] with one more digit only if we have one more digit
		if (sa >= 0) {
			shift_left_(P, 1);
			P[0] = A[sa];
			sa--;
		}
		else
			done = true;
	}
}

// C[] A[] % B[]
void modulo (const char A[], const char B[], char C[]) {
	char P1[DIM], P2[DIM];

	divide(A, B, P1);
	multiply(P1, B, P2);
	sub(A, P2, C);
}

// check if A[] is ZERO
bool is_zero (char A[]) {
	int s;

	s = digits(A);
	return (s == 0 && A[s] == 0);
}


// convert BIG number A[] to a string s, return s. assuming s has enough space for all digits+1 (for '\0') 
char *number2str (const char A[], char *s) {
    int i;
    char *p = s;

	i = digits(A);

	while (i >= 0) {
		*p = A[i]+'0';
		i--;
		p++;
	}

	*p = '\0';

    return s;
}