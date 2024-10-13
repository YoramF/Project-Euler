#include <stdbool.h>
#include <string.h>

extern unsigned int DIM;

bool is_bigger_equale_ (const char A[], const char B[], bool equal);
#define is_bigger(a,b) is_bigger_equale_((a), (b), false)
#define is_bigger_e(a,b) is_bigger_equale_((a), (b), true)

#define assign(a,b) memcpy((b), (a), DIM)

// this function must be called before using big_numbers function
// dim parameter will set the max number of digits in big_numbers
unsigned int init_big_numbers (unsigned int dim);

// put a number represented as a string into the big int A
void make_int (char A[], char *s);

// A++ 
void increment (char A[]);

// C = A + B 
void add (const char A[], const char B[], char C[]);

// C = A - B 
void sub (const char A[], const char B[], char C[]);

// check if A[] is equal to B[] 
bool is_equal (const char A[], const char B[]);

// C = A * B 
void multiply (const char A[], const char B[], char C[]);

// C[] = A[] / B[] (no reminders)
void divide (const char A[], const char B[], char C[]);

// C[] A[] % B[]
void modulo (const char A[], const char B[], char C[]);

// check if A[] is ZERO
bool is_zero (char A[]);

// return index to most significat digit in input number 
int digits (const char A[]);

// convert BIG number A[] to a string s, return s. assuming s has enough space for all digits+1 (for '\0') 
char *number2str (const char A[], char *s);