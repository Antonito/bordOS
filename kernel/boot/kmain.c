#include <stddef.h>
#include "arch/arch.h"
#include "boot/multiboot.h"
#include "display/kernel_display.h"

uint8_t kmain_init()
{
  /* Init gdt */
  term_init();
  term_putstr("Init term");
  init_gdt();
  term_putstr(" | Init gdt.");
  init_idt();
  term_putstr(" | Init idt.");
  init_irq();
  term_putstr(" | Init irq.");
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

  set_term_color(vga_entry_color(VGA_COLOR_BLUE, VGA_COLOR_BLACK));
  term_putstr("Hello");
  set_term_color(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
  term_putstr(", ");
  set_term_color(vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK));
  term_putstr("Kernel!");

  for (;;)
    {
      halt();
    }
}
