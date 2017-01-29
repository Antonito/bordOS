#include "arch/x86/gdt.h"

gdt_desc_t       kgdt[GDTSIZE]; /* GDT */
static gdt_reg_t kgdtr;         /* GDT Register */

/* ASM function */
extern void gdt_flush(void);

static void gdt_set_gate(int32_t num, uint64_t base, uint64_t limit,
                         uint8_t access, uint8_t gran)
{
  /* Set bases */
  kgdt[num].base_low = base & 0xFFFF;
  kgdt[num].base_middle = (base >> 16) & 0xFF;
  kgdt[num].base_high = (base >> 24) & 0xFF;

  /* Set limits */
  kgdt[num].limit_low = limit & 0xFFFF;
  kgdt[num].granularity = (limit >> 16) & 0x0F;

  /* Access flags and granularity */
  kgdt[num].granularity |= (gran & 0xF0);
  kgdt[num].access = access;
}

extern void init_gdt(void)
{
  /* Register */
  kgdtr.limit = (sizeof(gdt_desc_t) * 3) - 1;
  kgdtr.base = (int32_t)&kgdt;

  /* NULL Descriptor */
  gdt_set_gate(0, 0, 0, 0, 0);

  /* Code segment, 0 -> 4GB */
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

  /* Data segment, 0 -> 4GB */
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

  /* Actually install gdt */
  gdt_flush();
}
