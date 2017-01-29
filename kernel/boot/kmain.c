#include <stddef.h>
#include "arch/arch.h"
#include "boot/multiboot.h"
#include "display/vga_term.h"
#include "drivers/keyboard/keyboard.h"

#include "logger.h"

/*
** TODO:
** Each module should take care of the logging, instead of writting it here
*/
uint8_t kmain_init()
{
  init_logger(SERIAL_COM1);
  logger_write("Logger inited\n");
  term_init();
  logger_write("Term inited\n");
  init_gdt();
  logger_write("GDT installed\n");
  init_idt();
  logger_write("IDT installed\n");
  init_irq();
  logger_write("IRQs and ISRs installed\n");
  set_interrupts();
  logger_write("Interrupts activated\n");
  init_keyboard();
  logger_write("Keyboard inited\n");
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

  set_term_color(VGA_SET_COLORS(VGA_COLOR_BLUE, VGA_COLOR_BLACK));
  term_putstr("Hello");
  set_term_color(VGA_SET_COLORS(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
  term_putstr(", ");
  set_term_color(VGA_SET_COLORS(VGA_COLOR_RED, VGA_COLOR_BLACK));
  term_putstr("Kernel!");
  set_term_color(VGA_SET_COLORS(VGA_COLOR_WHITE, VGA_COLOR_BLACK));

  for (;;)
    {
      halt();
    }
}
