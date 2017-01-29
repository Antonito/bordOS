#ifndef ARCH_H_
#define ARCH_H_

#include <stdint.h>

/* Get registers structure */
#if defined(__i386)
#include "arch/x86/regs.h"
#else
#error "Architecture not supported"
#endif

/* Utils */
void    halt(void);
void    set_interrupts(void);
void    clear_interrupts(void);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
uint32_t inl(uint16_t port);
void outb(uint16_t port, uint8_t val);
void outw(uint16_t port, uint16_t val);
void outl(uint16_t port, uint32_t val);
void irq_set_routine(int32_t irq, void (*handler)(regs_t *reg));

/* Initialization */
void init_gdt(void);
void init_idt(void);
void init_irq(void);

#endif /* !ARCH_H_ */