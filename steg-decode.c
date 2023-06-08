// steg-decode.c
// Řešení IJC-DU1, příklad b), 21.3.2023
// Autor: Ondřej Přibyl, FIT
// Přeloženo: gcc 12.2.1

#include "ppm.c"
#include "utf8_check.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_PRIME 101

int main(int argc, char *argv[]) {
  struct ppm *obj = ppm_read(argv[argc - 1]);
  bitset_t array;
  bitset_alloc(array, (obj->xsize * obj->ysize * 3));

  Eratosthenes(array);

  unsigned char *message = malloc(obj->xsize * obj->ysize * 3);
  memset(message, 0, obj->xsize * obj->ysize * 3);

  unsigned long n_bit = 0;

  for (unsigned long i = START_PRIME; i < bitset_size(array); ++i) {
    if (!(bitset_getbit(array, i))) {
      unsigned char tmp = 1;
      tmp = tmp & obj->data[i];
      tmp = tmp << n_bit % 8;
      message[n_bit / 8] = message[n_bit / 8] | tmp;
      n_bit++;
    }
  }

  if (utf8_check(message) != NULL) {
    warning("Message in picture is propably not valid UTF8 string");
  };
  message[n_bit / 8 + 1] = '\0';

  printf("%s\n", message);

  free(obj);
  bitset_free(array);
  return 0;
}
