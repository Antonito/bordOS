#ifndef IRQ_H_
#define IRQ_H_

#include "arch/x86/isr.h"

/* ASM functions */
extern void _irq0();
extern void _irq1();
extern void _irq2();
extern void _irq3();
extern void _irq4();
extern void _irq5();
extern void _irq6();
extern void _irq7();
extern void _irq8();
extern void _irq9();
extern void _irq10();
extern void _irq11();
extern void _irq12();
extern void _irq13();
extern void _irq14();
extern void _irq15();

void init_irq(void);
void irq_set_routine(int32_t irq, void (*handler)(regs_t *reg));

#endif /* !IRQ_H_ */
