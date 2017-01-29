#include <stdint.h>
#include "display/vga_term.h"
#include "arch/arch.h"
#include "arch/x86/irq.h"
#include "arch/x86/isr.h"

uint8_t chars[] = {'\b', 0,   'q', 'w',  'e', 'r', 't', 'y', 'u', 'i', 'o',
                   'p',  0,   0,   '\n', 0,   'a', 's', 'd', 'f', 'g', 'h',
                   'j',  'k', 'l', 0,    0,   0,   0,   0,   'z', 'x', 'c',
                   'v',  'b', 'n', 'm',  0,   0,   0,   0,   0,   0,   ' '};

void keyboard_handler(regs_t *reg)
{
  uint8_t       keycode;
  unsigned char buff[2] = {0};

  (void)reg;
  keycode = inb(0x60);
  if (keycode - 0x80 > 0)
    return;
  buff[0] = chars[(keycode - 0x0E) % 44];
  term_putstr((const char *)&buff[0]);
  buff[0] = 0;
  buff[1] = 0;
}

void init_keyboard(void)
{
  irq_set_routine(1, keyboard_handler);
}
