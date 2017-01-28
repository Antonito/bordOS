#ifndef LIB_H_
#define LIB_H_

#include <stddef.h>

size_t strlen(const char *);
void *memset(void *s, int32_t c, size_t n);
int32_t memcmp(const void *s1, const void *s2, size_t n);
void *memcpy(void *dest, const void *src, size_t n);

#endif
