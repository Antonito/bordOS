#include "arch/arch.h"
#include "multiboot.h"

uint8_t kmain_init()
{
  /* Init gdt */
  init_gdt();
  init_idt();
  init_irq();
  set_interrupts();
  return (0);
}

void kmain(mboot_info_t *info, uint32_t eax)
{
  if (eax != MBOOT_MAGIC2)
    {
      return;
    }

  if (kmain_init())
    {
      return;
    }
  for (;;)
    {
      halt();
    }
}
