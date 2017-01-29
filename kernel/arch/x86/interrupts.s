	[BITS 32]
	section .text

	global	set_interrupts, clear_interrupts

set_interrupts:
    sti
    ret

clear_interrupts:
    cli
    ret
