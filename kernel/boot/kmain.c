#include "multiboot.h"

void halt()
{
  __asm__("hlt;");
}

uint8_t kmain_init()
{
  /* Init gdt */
}

void kmain(mboot_info_t *info, uint32_t eax)
{
  if (eax != MBOOT_MAGIC2)
    return;

  asm("sti;");
  for (;;)
    {
      halt();
    }
}
