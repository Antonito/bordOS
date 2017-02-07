#include "arch/arch.h"
#include "arch/x86/isr.h"
#include "logger.h"

static enum {
  ISR_DIV_ZERO,
  ISR_DBG,
  ISR_NON_MASKABLE_INT,
  ISR_BRKPOINT,
  ISR_INTO_DETECTED_OVERFLOW,
  ISR_OUT_OF_BOUNDS,
  ISR_INV_OPCODE,
  ISR_NO_COPROC,
  ISR_DOUBLE_FAULT,
  ISR_COPROC_SEG_OVERRUN,
  ISR_BAD_TSS,
  ISR_SEG_NOT_PRESENT,
  ISR_STACK_FAULT,
  ISR_GENERAL_PROT_FAULT,
  ISR_PAGE_FAULT,
  ISR_UNKNOWN_INT,
  ISR_COPROC_FAULT,
  ISR_ALIGN_CHECK,
  ISR_MACHINE_CHECK,
  ISR_RSV
} e_isr;

static const char *exception_message[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt Exception",
    "Breakpoint Exception",
    "Into Detected Overflow Exception",
    "Out of Bounds Exception",
    "Invalid Opcode Exception",
    "No Coprocessor Exception",
    "Double Fault Exception",
    "Coprocessor Segment Overrun Exception",
    "Bad TSS Exception",
    "Segment Not Present Exception",
    "Stack Fault Exception",
    "General Protection Fault Exception",
    "Page Fault Exception",
    "Unknown Interrupt Exception",
    "Coprocessor Fault Exception",
    "Alignment Check Exception (486+)",
    "Machine Check Exception (Pentium/586+)",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions"};

void isr_default_int(regs_t *r)
{
  if (r->int_no < 32)
    {
      clear_interrupts();
      logger_set_level(LOG_CRITICAL);
      logger_writef("%s\n", exception_message[r->int_no]);
      if (r->int_no == ISR_PAGE_FAULT)
	{
	  uintptr_t addr;

	  __asm__ __volatile__("mov %%cr3, %0" : "=r"(addr)::);
	  logger_writef("Faulting address: 0x%x\n", addr);
	}
      for (;;)
	{
	  halt();
	}
      (void)e_isr;
    }
}
