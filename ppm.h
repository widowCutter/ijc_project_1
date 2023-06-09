// ppm.h
// Řešení IJC-DU1, příklad b), 21.3.2023
// Autor: Ondřej Přibyl, FIT
// Přeloženo: gcc 12.2.1

#include "eratosthenes.c"

struct ppm {
  unsigned xsize;
  unsigned ysize;
  char data[]; // RGB bajty, celkem 3*xsize*ysize
};

struct ppm * ppm_read(const char * filename);

void ppm_free(struct ppm *p);

