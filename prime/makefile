libprime: prime.o aks.o
	ar rcs libprime.a prime.o aks.o

prime.o: prime.c prime.h
	gcc -c prime.c -o prime.o

aks.o: aks.c
	gcc -c aks.c -o aks.o

libprime_d: prime_d.o aks_d.o
	ar rcs libprime_d.a prime_d.o aks_d.o

prime_d.o: prime.c prime.h
	gcc -g -c prime.c -o prime_d.o

aks_d.o: aks.c
	gcc -g -c aks.c -o aks_d.o

tst_d: tst.c libprime_d.a
	gcc -g tst.c -o tst_d -lprime_d -L . -lm -lgmp
 
tst: tst.c libprime.a
	gcc -s tst.c -o tst -lprime -L . -lm -lgmp