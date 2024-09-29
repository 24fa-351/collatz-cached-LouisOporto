build:
		gcc collatz.c cache.c -o collatz.exe

test:
		bash test.sh

debug:
		gcc -g collatz.c cache.c -o debug.exe
