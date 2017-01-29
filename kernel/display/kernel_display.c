#include <stdint.h>
#include <stddef.h>
#include "lib/lib.h"
#include "display/kernel_display.h"
#include "logger.h"

static termdisp_t disp;

static uint16_t vga_entry(uint8_t uc, uint8_t color)
{

  return ((uint16_t)uc | (uint16_t)color << 8);
}

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
  return (fg | bg << 4);
}

/* we set the screen buffer with space */
void term_init()
{
  disp.term_x = 0;
  disp.term_y = 0;
  disp.term_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  disp.term_buff = (uint16_t *)0xB8000;
  for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
      for (size_t x = 0; x < VGA_WIDTH; x++)
	{
	  const size_t i = y * VGA_WIDTH + x;
	  disp.term_buff[i] = vga_entry(' ', disp.term_color);
	}
    }
  logger_write("Terminal inited\n");
}

void set_term_color(uint8_t color)
{
  disp.term_color = color;
}

void term_putchar(uint8_t c)
{
  const size_t i = disp.term_y * VGA_WIDTH + disp.term_x;

  disp.term_buff[i] = vga_entry(c, disp.term_color);
  if (++disp.term_x == VGA_WIDTH)
    {
      disp.term_x = 0;
      if (++disp.term_y == VGA_HEIGHT)
	disp.term_y = 0;
    }
}

void term_putstr(const char *str)
{
  for (size_t i = 0; i < strlen(str); i++)
    term_putchar(str[i]);
}
