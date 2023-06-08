// error.c
// Řešení IJC-DU1, příklad b), 21.3.2023
// Autor: Ondřej Přibyl, FIT
// Přeloženo: gcc 12.2.1

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void warning(const char *fmt, ...);
extern void error_exit(const char *fmt, ...);
