#ifndef LIB_H_
#define LIB_H_

#include <stdint.h>
#include <stddef.h>

/* String.h */
size_t strlen(const char *);
void *memset(void *s, int32_t c, size_t n);
int32_t memcmp(const void *s1, const void *s2, size_t n);
void *memcpy(void *dest, const void *src, size_t n);

/* Debug */
void system_abort(const char *const msg, const char *const file,
                  const char *const line);
#if defined(NDEBUG)
#define kassert(cond)                                                         \
  do                                                                          \
    {                                                                         \
      ;                                                                       \
    }                                                                         \
  while (0);
#else
#define kassert(cond)                                                         \
  do                                                                          \
    {                                                                         \
      if (!(cond))                                                            \
	system_abort(#cond, __FILE__, __LINE__);                              \
    }                                                                         \
  while (0);
#endif /* NDEBUG */

#endif /* !LIB_H_ */
