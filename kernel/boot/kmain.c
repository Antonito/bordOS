#include <stddef.h>
#include "arch/arch.h"
#include "boot/multiboot.h"
#include "display/kernel_display.h"

#include "logger.h"

/*
** TODO:
** Each module should take care of the logging, instead of writting it here
*/
uint8_t kmain_init()
{
  init_logger(SERIAL_COM1);
  term_init();
  init_gdt();
  init_idt();
  init_irq();
  set_interrupts();
  logger_write("Interrupts activated\n");
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
