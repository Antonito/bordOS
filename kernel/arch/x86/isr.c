#include "arch/arch.h"
#include "arch/x86/isr.h"
#include "logger.h"

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
      logger_write(exception_message[r->int_no]);
      for (;;)
	{
	  halt();
	}
    }
}
