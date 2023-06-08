// error.c
// Řešení IJC-DU1, příklad b), 21.3.2023
// Autor: Ondřej Přibyl, FIT
// Přeloženo: gcc 12.2.1

#include "error.h"

void warning(const char *fmt, ...){
  va_list args;
  va_start(args, fmt);
  fprintf(stderr, "Warning: ");
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
  va_end(args);
  return;
}

void error_exit(const char *fmt, ...){
  va_list args;
  va_start(args, fmt);
  fprintf(stderr, "Error: ");
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
  va_end(args);
  exit(1);
}
