#ifndef IDT_H_
#define IDT_H_

#define IDTBASE 0x800 /* Physical addr */
#define IDTSIZE 0xFF  /* Max descriptors */
#define INTGATE 0x8E00

#include <stdint.h>

typedef struct s_idt_desc idt_desc_t;
typedef struct s_idt_reg  idt_reg_t;

__attribute__((packed)) struct s_idt_desc
{
  uint16_t base_low;
  uint16_t sel;
  uint8_t  always0;
  uint8_t  flags;
  uint16_t base_high;
};

__attribute__((packed)) struct s_idt_reg
{
  uint16_t limit;
  uint32_t base;
};

/* IDTs */
void init_idt(void);
void idt_set_gate(uint8_t num, uint64_t base, uint16_t sel, uint8_t flags);

#endif /* !IDT_H_ */
