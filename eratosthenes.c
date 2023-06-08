// eratosthenes.c
// Řešení IJC-DU1, příklad a), 21.3.2023
// Autor: Ondřej Přibyl, FIT
// Přeloženo: gcc 12.2.1

#include "eratosthenes.h"

void Eratosthenes(bitset_t array)
{
  unsigned long range = bitset_size(array);
  bitset_setbit(array, 0, 1);
  bitset_setbit(array, 1, 1);
  unsigned long N = sqrt(range);
  for (unsigned long i = 2; i < N; i++) {
    if (bitset_getbit(array, i) == 1) {
      continue;
    }
    for (unsigned long o = 2; o * i < range; o++) {
      bitset_setbit(array, i * o, 1);
    }
  }
}

