#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

typedef unsigned char BIG_NUMBER;

#define BASE 10
unsigned int DIM = 1;

bool is_bigger_equale_ (const void *A, const void *B, bool equal);
#define is_bigger(a,b) is_bigger_equale_((a), (b), false)
#define is_bigger_e(a,b) is_bigger_equale_((a), (b), true)
#define release(a) free((a))
#define assign(a,b) memcpy((b), (a), DIM)


// this function must be called before using big_numbers function
// dim parameter will set the max number of digits in big_numbers
unsigned int init_big_numbers (unsigned int dim) {
	DIM = dim;
	return DIM;
}

// create a new big number
void *gen_number() {
	BIG_NUMBER *b;

	if ((b = calloc(DIM, (sizeof(BIG_NUMBER)))) == NULL) {
		fprintf(stderr, "Failed to allocate BIG_NUMBER: %d\n", strerror(errno));
		exit (EXIT_FAILURE);
	}

	return b;
}

// put a number represented as a string into the big int A
void make_int (void *A, char *s) {
	int	i, l;
	char *p;
	BIG_NUMBER *A_ = (BIG_NUMBER *)A;

	// get input number len
	l = strlen(s);
	p = s+l-1;

	// start indexing at the DIM's place
	i = 0;

	// while there is still something left to the string and we did not exceeded DIM
	// we're encoding... 
	while (p >= s && i < DIM) {
		// put the least significant digit of n into A[i] 
		A_[i] = *p - '0';
		i++;
		p--;
	}

	// fill the rest of the array up with zeros 
	while (i < DIM) A_[i++] = 0;
}

// A++ 
void increment (void *A) {
	int	i;
	BIG_NUMBER *A_ = (BIG_NUMBER *)A;

	// start indexing at the least significant digit 
	i = 0;
	while (i < DIM) {

		// increment the digit 
		A_[i]++;

		// if it overflows (i.e., it was 9, now it's 10, too
		// big to be a digit) then...
		if (A_[i] == BASE) {

			// make it zero and index to the next 
			// significant digit 
			A_[i] = 0;
			i++;
		} else 
			// otherwise, we are done 
			break;
	}
}


// return number of digits 
int digits (const void *A) {
	int i;
	BIG_NUMBER *A_ = (BIG_NUMBER *)A;

	i = DIM - 1;
	while ((A_[i] == 0) && (i > 0))
		i--;

	return i+1;
}

// C = A + B 
void add (const void *A, const void *B, void *C) {
	int	i;
    char carry, sum;
	BIG_NUMBER *A_ = (BIG_NUMBER *)A;
	BIG_NUMBER *B_ = (BIG_NUMBER *)B;
	BIG_NUMBER *C_ = (BIG_NUMBER *)C;

	// no carry yet 
	carry = 0;

	// go from least to most significant digit 
	for (i=0; i<DIM; i++) {

		// the i'th digit of C is the sum of the
		// i'th digits of A and B, plus any carry
		sum = A_[i] + B_[i] + carry;

		// if the sum exceeds the base, then we have a carry. 
		if (sum >= BASE) {

			carry = 1;

			// make sum fit in a digit (same as sum %= BASE) 
			sum -= BASE;
		} else
			// otherwise no carry 
			carry = 0;

		// put the result in the sum 
		C_[i] = sum;
	}
}


// C = A - B 
void sub (const void *A, const void *B, void *C) {
	int i, j, k;
	BIG_NUMBER *P;
	BIG_NUMBER *A_ = (BIG_NUMBER *)A;
	BIG_NUMBER *B_ = (BIG_NUMBER *)B;
	BIG_NUMBER *C_ = (BIG_NUMBER *)C;

	// init C 
	memset(C_, 0, DIM);

	// int P[] - we need P[] so that A[] will remain unchanged
	P = (BIG_NUMBER *)gen_number();	
	assign(A_, P);

	for (i = 0; i < DIM; i++) {
		if (P[i] >= B_[i])
			C_[i] = P[i] - B_[i];
		else {
			// make a loan from next digit 
			j = i + 1;
			P[i] += 10;

			// get number of digits of B
			k = digits(B);

			while (j < k && P[j] == 0)
				P[j++] = 9;
			if (j < DIM)
				P[j]--;

			C_[i] = P[i] - B_[i];				
		}
	}

	release(P);
}

// check if A[] is bigger or equal (e = true) to B[] 
bool is_bigger_equale_ (const void *A, const void *B, bool equal) {
	int s1, s2;
	BIG_NUMBER *A_ = (BIG_NUMBER *)A;
	BIG_NUMBER *B_ = (BIG_NUMBER *)B;

	s1 = digits(A) - 1;
	s2 = digits(B) - 1;

	// scan down the digits
	if (s1 == s2) {
		while (s1 >= 0) {
			if (A_[s1] > B_[s1])
				return true;
			else if (A_[s1] < B_[s1])
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
bool is_equal (const void *A, const void *B) {
	int s1, s2;
	BIG_NUMBER *A_ = (BIG_NUMBER *)A;
	BIG_NUMBER *B_ = (BIG_NUMBER *)B;

	s1 = digits(A) - 1;
	s2 = digits(B) - 1;

	// scan down the digits
	if (s1 == s2) {
		while (s1 >= 0) {
			if (A_[s1] != B_[s1])
				return false;
			s1--;
		}

		// we get here only if the two numbers are equale
		return true;
	}
	
	return false;
}

// B = n * A 
static void multiply_one_digit_ (const void *A, void *B, char n) {
	int	i;
    char carry;
	BIG_NUMBER *A_ = (BIG_NUMBER *)A;
	BIG_NUMBER *B_ = (BIG_NUMBER *)B;

	/// no extra overflow to add yet 
	carry = 0;

	// for each digit, starting with least significant... 
	for (i=0; i<DIM; i++) {

		// multiply the digit by n, putting the result in B 
		B_[i] = n * A_[i];

		//add in any overflow from the last digit 
		B_[i] += carry;

		// if this product is too big to fit in a digit... 
		if (B_[i] >= BASE) {
			// handle the overflow 
			carry = B_[i] / BASE;
			B_[i] %= BASE;
		} else
			// no overflow 
			carry = 0;
	}
}


// "multiplies" a number by BASEn 
static void shift_left_ (void *A, char n) {
	int	i;
	BIG_NUMBER *A_ = (BIG_NUMBER *)A;

	// going from left to right, move everything over to the
	// left n spaces
	for (i=DIM-1; i>=n; i--) A_[i] = A_[i-n];

	// fill the last n digits with zeros 
	while (i >= 0) A_[i--] = 0;
}

// C = A * B 
void multiply (const void *A, const void *B, void *C) {
	int	i, j;
    BIG_NUMBER *P;
	BIG_NUMBER *A_ = (BIG_NUMBER *)A;
	BIG_NUMBER *B_ = (BIG_NUMBER *)B;

	// C will accumulate the sum of partial products.  It's initially 0. 
	memset(C, 0, DIM);

	P = (BIG_NUMBER *)gen_number();

	// for each digit in A... 
	for (i=0; i<DIM; i++) {

		// multiply B by digit A[i] 
		multiply_one_digit_(B, P, A_[i]);

		// shift the partial product left i bytes 
		shift_left_(P, i);

		// add result to the running sum 
		add (C, P, C);
	}

	release(P);
}

// C[] = A[] / B[] (no reminders)
void divide (const void *A, const void *B, void *C) {
	BIG_NUMBER *P, *M, *MO;
	int p, a, sb, sa, i;
	bool done = false;
	BIG_NUMBER *A_ = (BIG_NUMBER *)A;
	BIG_NUMBER *B_ = (BIG_NUMBER *)B;
	BIG_NUMBER *C_ = (BIG_NUMBER *)C;

	P = (BIG_NUMBER *)gen_number();
	M = (BIG_NUMBER *)gen_number();
	MO = (BIG_NUMBER *)gen_number();

	// reset C[] & P[]
	memset(C, 0, DIM);
	memset(P, 0, DIM);

	// get index to most significant digits of A & B
	sa = digits(A) - 1;
	sb = digits(B) - 1;

	// quick check if divisor is bigger than dividend
	// first check we are not dividing by ZERO in that case return false
	if (B_[sb] == 0) {
		fprintf(stderr, "DIVIDE BY ZERO!, program exit..\n");
		exit(EXIT_FAILURE);
	}

	// second check if divisor has more digits than dividend
	else if (sb > sa)
		goto end;
	// third if both have same number of digits, check most significan digit of each number
	else if (sa == sb && A_[sa] < B_[sb])
		goto end;

	// if we get here we need to perform long division

	// get initial sub dividend
	for (i = sb; i >= 0; i--)
		P[i] = A_[i+sa-sb];

	sa -= (sb+1);

	// loop untill P[]==0 or no more digits to pull from A[]
	while (!done) {
		p = 0;
		assign(B, M);		// to make sure we also copy all zeros
		while (is_bigger_e(P, M)) {
			assign(M, MO);
			p++;
			add(M, B, M);
		}

		// update C[]
		shift_left_(C, 1);
		C_[0] = p;

		// check if we can proceed with subtcation
		if (p > 0) {
			if (is_bigger_e(P, MO)) {
				sub(P, MO, M);
				assign(M, P);
			}
		}

		// increase P[] with one more digit only if we have one more digit
		if (sa >= 0) {
			shift_left_(P, 1);
			P[0] = A_[sa];
			sa--;
		}
		else
			done = true;
	}

end:
	release(P);
	release(M);
	release(MO);
}

// C[] A[] % B[]
void modulo (const void *A, const void *B, void *C) {
	BIG_NUMBER *P1, *P2;
	BIG_NUMBER *A_ = (BIG_NUMBER *)A;
	BIG_NUMBER *B_ = (BIG_NUMBER *)B;
	BIG_NUMBER *C_ = (BIG_NUMBER *)C;

	P1 = (BIG_NUMBER *)gen_number();
	P2 = (BIG_NUMBER *)gen_number();

	divide(A, B, P1);
	multiply(P1, B, P2);
	sub(A, P2, C);

	release(P1);
	release(P2);
}

// check if A[] is ZERO
bool is_zero (const void *A) {
	int s;
	BIG_NUMBER *A_ = (BIG_NUMBER *)A;	

	s = digits(A) - 1;
	return (s == 0 && A_[s] == 0);
}


// convert BIG number A[] to a string s, return s. assuming s has enough space for all digits+1 (for '\0') 
char *number2str (const void *A, char *s) {
    int i;
    char *p = s;
	BIG_NUMBER *A_ = (BIG_NUMBER *)A;

	i = digits(A) - 1;

	while (i >= 0) {
		*p = A_[i]+'0';
		i--;
		p++;
	}

	*p = '\0';

    return s;
}