#ifndef HEAP_H_
#define HEAP_H_

#include <stddef.h>

__attribute__((malloc)) void *kmalloc(size_t size);
__attribute__((malloc)) void *krealloc(void *ptr, size_t size);
__attribute__((malloc)) void *kcalloc(size_t nmemb, size_t nb);
void free(void *ptr);

#endif /* !HEAP_H_ */
