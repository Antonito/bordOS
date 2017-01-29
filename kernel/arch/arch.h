#ifndef ARCH_H_
#define ARCH_H_

#include <stdint.h>

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

/* Initialization */
void init_gdt(void);
void init_idt(void);
void init_irq(void);

#endif /* !ARCH_H_ */