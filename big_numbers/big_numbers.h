#include <stdbool.h>
#include <string.h>

extern unsigned int DIM;

bool is_bigger_equale_ (const void *A, const void *B, bool equal);
#define is_bigger(a,b) is_bigger_equale_((a), (b), false)
#define is_bigger_e(a,b) is_bigger_equale_((a), (b), true)

#define assign(a,b) memcpy((b), (a), DIM)
#define release(a) free((a))

// this function must be called before using big_numbers function
// dim parameter will set the max number of digits in big_numbers
unsigned int init_big_numbers (unsigned int dim);

// create a new big number
void *gen_number();

// put a number represented as a string into the big int A
void make_int (void *A, char *s);

// A++ 
void increment (void *A);

// C = A + B 
void add (const void *A, const void *B, void *C);

// C = A - B 
void sub (const void *A, const void *B, void *C);

// check if A[] is equal to B[] 
bool is_equal (const void *A, const void *B);

// C = A * B 
void multiply (const void *A, const void *B, void *C);

// C[] = A[] / B[] (no reminders)
void divide (const void *A, const void *B, void *C);

// C[] A[] % B[]
void modulo (const void *A, const void *B, void *C);

// check if A[] is ZERO
bool is_zero (const void *A);

// return index to most significat digit in input number 
int digits (const void *A);

// convert BIG number A[] to a string s, return s. assuming s has enough space for all digits+1 (for '\0') 
char *number2str (const void *A, char *s);