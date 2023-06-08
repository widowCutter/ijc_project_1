# steg-decode.c
# Řešení IJC-DU1, příklad abc), 21.3.2023
# Autor: Ondřej Přibyl, FIT
# Spuštěno: make 4.4.1
 
CFLAGS = -std=c11 -pedantic -Wall -Wextra -O2 -lm

all: primes primes-i steg-decode

primes: primes.c bitset.h eratosthenes.c eratosthenes.h
	$(CC) $(CFLAGS) primes.c -o primes
	
primes-i: primes.c bitset.h eratosthenes.c eratosthenes.h
	$(CC) -DUSE_INLINE $(CFLAGS) primes.c -o primes-i

steg-decode: primes steg-decode.c ppm.c utf8_check.c
	$(CC) $(CFLAGS) steg-decode.c -o steg-decode
	
.SILENT: run clean
run: primes primes-i
	(ulimit -s 28600; ./primes)
	(ulimit -s 28600; ./primes-i)

clean:
	rm primes primes-i steg-decode 2>/dev/null || true
