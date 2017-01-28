#ifndef KERNEL_DISPLAY_H_
#define KERNEL_DISPLAY_H_

enum vga_color
{
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_LIGHT_BROWN = 14,
  VGA_COLOR_WHITE = 15,
};

#define VGA_HEIGHT 25
#define VGA_WIDTH 80

typedef struct termdisp_s
{
  uint8_t   term_color;
  uint16_t *term_buff;
  size_t    term_x;
  size_t    term_y;
} termdisp_t;

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg);
void term_init();
void set_term_color(uint8_t color);
void term_putchar(uint8_t c);
void term_putstr(const char *str);

#endif
