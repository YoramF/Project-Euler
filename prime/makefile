libprime: prime.o
	ar rcs libprime.a prime.o

prime.o: prime.c prime.h
	gcc -c prime.c -o prime.o

libprime_d: prime_d.o
	ar rcs libprime_d.a prime_d.o

prime_d.o: prime.c prime.h
	gcc -g -c prime.c -o prime_d.o

tst_d: tst.c libprime_d.a
	gcc -g tst.c -o tst_debug.exe -lprime_d -L .

tst: tst.c libprime.a
	gcc -s tst.c -o tst.exe -lprime -L .