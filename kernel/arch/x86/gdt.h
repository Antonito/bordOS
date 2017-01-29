#ifndef GDT_H_
#define GDT_H_

#include <stdint.h>

#define GDTBASE 0x0
#define GDTSIZE 0x03

typedef struct s_gdt_desc gdt_desc_t;
typedef struct s_gdt_reg  gdt_reg_t;

__attribute__((packed)) struct s_gdt_desc
{
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t  base_middle;
  uint8_t  access;
  uint8_t  granularity;
  uint8_t  base_high;
};

__attribute__((packed)) struct s_gdt_reg
{
  uint16_t limit;
  uint32_t base;
};

void init_gdt(void);

#endif /* !GDT_H_ */