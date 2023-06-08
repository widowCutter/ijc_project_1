// ppm.c
// Řešení IJC-DU1, příklad b), 21.3.2023
// Autor: Ondřej Přibyl, FIT
// Přeloženo: gcc 12.2.1

#include "ppm.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


struct ppm * ppm_read(const char * filename)
{
  FILE *fp = fopen(filename, "r");
  unsigned long xsize = 0,ysize = 0;
  int file_read = fscanf(fp, "P6 %lu %lu 255 ",&xsize, &ysize);
  if (file_read < 2) {
    error_exit("Wrong file format: %s", filename);
  }
  size_t data_lenght = 3 * xsize * ysize;
  struct ppm *obj = malloc(sizeof(struct ppm) + data_lenght + 10);
  obj->xsize = xsize;
  obj->ysize = ysize;
  size_t str_len = fread(&obj->data, 1,data_lenght + 9, fp);
  if (str_len != (3 * obj->xsize * obj->ysize)) {
    warning("Data supplied by ppm header is not valid. Expected number of data elements was %lu. Got %lu. Continuing ...", data_lenght, str_len);
  }

  fclose(fp);
  return obj;
}
