	[BITS 32]
	section .text

	global	idt_load
	extern	kidtr

idt_load:
	lidt	[kidtr]
	ret
