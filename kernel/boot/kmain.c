#include <stddef.h>
#include <stdint.h>
#include "boot/multiboot.h"
#include "display/kernel_display.h"

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
  term_init();
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
