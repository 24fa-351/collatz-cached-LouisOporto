build:
		gcc collatz.c cache.c -o collatz.exe

test:
		bash cacheHit.sh

debug:
		gcc -g collatz.c cache.c -o debug.exe
