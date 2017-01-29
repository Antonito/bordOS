#include <stdint.h>
#include <stddef.h>
#include "lib/lib.h"
#include "display/vga_term.h"
#include "logger.h"

#define VGA_HEIGHT 25
#define VGA_WIDTH 80
#define VGA_ENTRY(a, b) ((uint16_t)((uint8_t)a) | (uint16_t)((uint8_t)b) << 8)

struct termdisp_t
{
  uint8_t   term_color;
  uint16_t *term_buff;
  size_t    term_x;
  size_t    term_y;
};

static struct termdisp_t disp;

/* we set the screen buffer with space */
void term_init()
{
  disp.term_x = 0;
  disp.term_y = 0;
  disp.term_color = VGA_SET_COLORS(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  disp.term_buff = (uint16_t *)0xB8000;
  for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
      for (size_t x = 0; x < VGA_WIDTH; x++)
	{
	  const size_t i = y * VGA_WIDTH + x;
	  disp.term_buff[i] = VGA_ENTRY(' ', disp.term_color);
	}
    }
  logger_write("Terminal inited\n");
}

void set_term_color(uint8_t color)
{
  disp.term_color = color;
}

void set_putchar_back(void)
{
  if (disp.term_x == 0)
    {
      if (disp.term_y == 0)
	{
	  return;
	}
      disp.term_x = VGA_WIDTH;
      disp.term_y -= 1;
    }
  else
    {
      --disp.term_x;
    }
  const size_t j = disp.term_y * VGA_WIDTH + disp.term_x;
  disp.term_buff[j] = VGA_ENTRY(' ', disp.term_color);
}

void set_putchar_newline(void)
{
  disp.term_x = 0;
  if (++disp.term_y == VGA_HEIGHT)
    {
      disp.term_y = 0;
    }
}

void term_putchar(uint8_t c)
{
  const size_t i = disp.term_y * VGA_WIDTH + disp.term_x;
  switch (c)
    {
    case '\n':
      set_putchar_newline();
      break;
    case '\b':
      set_putchar_back();
      break;
    default:
      disp.term_buff[i] = VGA_ENTRY(c, disp.term_color);
      if (++disp.term_x == VGA_WIDTH)
	{
	  disp.term_x = 0;
	  if (++disp.term_y == VGA_HEIGHT)
	    {
	      disp.term_y = 0;
	    }
	}
      break;
    }
}

void term_putstr(const char *str)
{
  for (size_t i = 0; i < strlen(str); i++)
    term_putchar(str[i]);
}
