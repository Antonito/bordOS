#ifndef PMM_H_
#define PMM_H_

#include <stddef.h>
#include "boot/multiboot.h"

void init_pmm(mboot_info_t const *const mb);
void *pmm_alloc(void);
void pmm_free(void const *const ptr);

#endif /* !PMM_H_ */
