	[BITS 32]
	section .text

	global	gdt_flush
	extern	kgdtr

;; Loads the GDT table
gdt_flush:
	lgdt		[kgdtr]
	mov		ax, 0x10
	mov		ds, ax
	mov		es, ax
	mov		fs, ax
	mov		gs, ax
	mov		ss, ax
	jmp		0x08:flush2
flush2:
	ret
