#include <stddef.h>
#include <stdint.h>
#include "multiboot.h"

void halt()
{
  __asm__("hlt");
}

uint32_t kmain(t_boot_info *info, uint32_t eax)
{
  if (eax != MBOOT_MAGIC2)
    return (1);
  for (;;)
    {
      halt();
    }
  return (0);
}
