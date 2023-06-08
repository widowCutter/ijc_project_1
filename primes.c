// primes.c
// Řešení IJC-DU1, příklad a), 21.3.2023
// Autor: Ondřej Přibyl, FIT
// Přeloženo: gcc 12.2.1

#include "eratosthenes.c"
#include <time.h>


int main ()
{
  clock_t start;
  start = clock();
  

  bitset_create(array, 230000000);
  unsigned long range = array[0];

  Eratosthenes(array);

  unsigned long last_primes[11] = {0,};
  last_primes[10] = 10;
  for (unsigned long i = range - 1; i > 0; i--) {
    if (bitset_getbit(array, i) == 0) {
      last_primes[last_primes[10] - 1] = i;
      last_primes[10]--;
      if (last_primes[10] <= 0) {
        break;
      }
    }
  }
  for (int i = 0; i < 10; i++) {
    printf("%lu\n",last_primes[i]);
  }
  fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
  
  return 0;
}
