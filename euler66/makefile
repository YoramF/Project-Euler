euler66_d: euler66.c ../big_numbers/libbig_numbers_d.a ../big_numbers/big_numbers.h
	gcc -g euler66.c -o euler66_debug.exe -lbig_numbers_d -L../big_numbers -I../big_numbers

euler66: euler66.c ../big_numbers/libbig_numbers.a ../big_numbers/big_numbers.h
	gcc -s euler66.c -o euler66.exe -lbig_numbers -L../big_numbers -I../big_numbers

cf_d: cf.c ../big_numbers/libbig_numbers_d.a ../big_numbers/big_numbers.h
	gcc -g cf.c -o cf_debug.exe -lbig_numbers_d -L../big_numbers -I../big_numbers

cf: cf.c ../big_numbers/libbig_numbers.a ../big_numbers/big_numbers.h
	gcc -s cf.c -o cf.exe -lbig_numbers -L../big_numbers -I../big_numbers
