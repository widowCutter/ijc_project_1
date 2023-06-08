// bitset.h
// Řešení IJC-DU1, příklad a), 21.3.2023
// Autor: Ondřej Přibyl, FIT
// Přeloženo: gcc 12.2.1

#include "error.c"
#include <assert.h>
#include <malloc.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long *bitset_t;

#define bitset_create(array, size)                                             \
  static_assert(size > 0, "Wrong size");                                       \
  unsigned long array[size / (sizeof(unsigned long) * 8) + 1 +                 \
                      (((size % sizeof(unsigned long) * 8) > 0) ? 1 : 0)] = {  \
      size, 0};

#define bitset_alloc(array_p, size)                                            \
  if (size <= 0) { error_exit("Wrong allocation size: ",size);};                                       \
  array_p = malloc(sizeof(unsigned long) * (size / (sizeof(unsigned long) * 8) + 1 +                 \
                      (((size % sizeof(unsigned long) * 8) > 0) ? 1 : 0)));  \
  if (array == NULL) {                                                         \
    error_exit("Failure to allocate memory for array with size %lu", size);    \
  }                                                                            \
  bitset_size(array_p) = size;                                                           \
  memset(array_p + 1, 0,                                                       \
         sizeof(unsigned long) *                                               \
             (size / (sizeof(unsigned long) * 8) +                             \
              (((size % sizeof(unsigned long) * 8) > 0) ? 1 : 0)));

#ifdef USE_INLINE

extern inline void bitset_free(bitset_t array_p) { free(array_p); }

extern inline unsigned long bitset_size(bitset_t array_p) { return array_p[0]; }

extern inline void bitset_setbit(bitset_t array_p, unsigned long index, int number) {
  index >= (bitset_size(array_p) + 1)
      ? error_exit(
            "Attempted to get bit at index out of bounds. Index: %lu", index), 0
            : (array_p[index / (sizeof(unsigned long) * 8) + 1] =
                   ((number != 0)
                        ? (array_p[index / (sizeof(unsigned long) * 8) + 1] |
                           (((1ul)
                             << ((sizeof(unsigned long) * 8) -
                                 (index % (sizeof(unsigned long) * 8)) - 1))))
                        : (array_p[index / (sizeof(unsigned long) * 8) + 1] &
                           ~(((1ul) << ((sizeof(unsigned long) * 8) -
                                        (index % (sizeof(unsigned long) * 8)) -
                                        1))))));
}

extern inline int bitset_getbit(bitset_t array_p, unsigned long index) {
  return index > bitset_size(array_p)
         ? error_exit("Attempted to get bit at index out of bounds. Index: %lu",
                      index),
         0
         : ((((array_p[index / (sizeof(unsigned long) * 8) + 1] &
               ((1ul) << ((sizeof(unsigned long) * 8) -
                          (index % (sizeof(unsigned long) * 8)) - 1))) > 0)
                 ? 1
                 : 0));
}

#endif // USE_INLINE

#ifndef USE_INLINE

#define bitset_free(array_p) free(array_p);

#define bitset_size(array_p) (array_p[0])

#define bitset_setbit(array_p, index, number)                                  \
  index >= (bitset_size(array_p) + 1)                                                    \
      ? error_exit("Attempted to set bit at index out of bounds. Index: %lu",  \
                   index),                                                     \
      0                                                                        \
      : (array_p[index / (sizeof(unsigned long) * 8) + 1] =                    \
             ((number != 0)                                                    \
                  ? (array_p[index / (sizeof(unsigned long) * 8) + 1] |        \
                     (((1ul) << ((sizeof(unsigned long) * 8) -                 \
                                 (index % (sizeof(unsigned long) * 8)) - 1)))) \
                  : (array_p[index / (sizeof(unsigned long) * 8) + 1] &        \
                     ~(((1ul)                                                  \
                        << ((sizeof(unsigned long) * 8) -                      \
                            (index % (sizeof(unsigned long) * 8)) - 1))))));

#define bitset_getbit(array_p, index)                                          \
  index > bitset_size(array_p)                                                           \
      ? error_exit("Attempted to get bit at index out of bounds. Index: %lu",  \
                   index),                                                     \
      0                                                                        \
      : ((((array_p[index / (sizeof(unsigned long) * 8) + 1] &                 \
            ((1ul) << ((sizeof(unsigned long) * 8) -                           \
                       (index % (sizeof(unsigned long) * 8)) - 1))) > 0)       \
              ? 1                                                              \
              : 0))

#endif // !USE_INLINE
