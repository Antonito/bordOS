#include "arch/x86/idt.h"
#include "arch/x86/isr.h"
#include "lib/lib.h" /* memset */

idt_desc_t kidt[IDTSIZE];
idt_reg_t  kidtr; /* IDT Register */

/* ASM function */
extern void idt_load(void);

void idt_set_gate(uint8_t num, uint64_t base, uint16_t sel, uint8_t flags)
{
  /* Base */
  kidt[num].base_low = base & 0xFFFF;
  kidt[num].base_high = (base >> 16) & 0xFFFF;

  /* Segment + flags */
  kidt[num].sel = sel;
  kidt[num].always0 = 0;
  kidt[num].flags = flags;
}

void init_idt(void)
{
  /* Register */
  kidtr.limit = (sizeof(idt_reg_t) * 0xFF) - 1;
  kidtr.base = (int32_t)&kidt;

  /* Set everything to 0 */
  memset(&kidt, 0, sizeof(idt_reg_t) * 0xFF);

  /* Add ISR handlers */
  idt_set_gate(0, (unsigned)_isr0, 0x08, 0x8E);
  idt_set_gate(1, (unsigned)_isr1, 0x08, 0x8E);
  idt_set_gate(2, (unsigned)_isr2, 0x08, 0x8E);
  idt_set_gate(3, (unsigned)_isr3, 0x08, 0x8E);
  idt_set_gate(4, (unsigned)_isr4, 0x08, 0x8E);
  idt_set_gate(5, (unsigned)_isr5, 0x08, 0x8E);
  idt_set_gate(6, (unsigned)_isr6, 0x08, 0x8E);
  idt_set_gate(7, (unsigned)_isr7, 0x08, 0x8E);
  idt_set_gate(8, (unsigned)_isr8, 0x08, 0x8E);
  idt_set_gate(9, (unsigned)_isr9, 0x08, 0x8E);
  idt_set_gate(10, (unsigned)_isr10, 0x08, 0x8E);
  idt_set_gate(11, (unsigned)_isr11, 0x08, 0x8E);
  idt_set_gate(12, (unsigned)_isr12, 0x08, 0x8E);
  idt_set_gate(13, (unsigned)_isr13, 0x08, 0x8E);
  idt_set_gate(14, (unsigned)_isr14, 0x08, 0x8E);
  idt_set_gate(15, (unsigned)_isr15, 0x08, 0x8E);
  idt_set_gate(16, (unsigned)_isr16, 0x08, 0x8E);
  idt_set_gate(17, (unsigned)_isr17, 0x08, 0x8E);
  idt_set_gate(18, (unsigned)_isr18, 0x08, 0x8E);
  idt_set_gate(19, (unsigned)_isr19, 0x08, 0x8E);
  idt_set_gate(20, (unsigned)_isr20, 0x08, 0x8E);
  idt_set_gate(21, (unsigned)_isr21, 0x08, 0x8E);
  idt_set_gate(22, (unsigned)_isr22, 0x08, 0x8E);
  idt_set_gate(23, (unsigned)_isr23, 0x08, 0x8E);
  idt_set_gate(24, (unsigned)_isr24, 0x08, 0x8E);
  idt_set_gate(25, (unsigned)_isr25, 0x08, 0x8E);
  idt_set_gate(26, (unsigned)_isr26, 0x08, 0x8E);
  idt_set_gate(27, (unsigned)_isr27, 0x08, 0x8E);
  idt_set_gate(28, (unsigned)_isr28, 0x08, 0x8E);
  idt_set_gate(29, (unsigned)_isr29, 0x08, 0x8E);
  idt_set_gate(30, (unsigned)_isr30, 0x08, 0x8E);
  idt_set_gate(31, (unsigned)_isr31, 0x08, 0x8E);

  /* Actually install idt */
  idt_load();
}
