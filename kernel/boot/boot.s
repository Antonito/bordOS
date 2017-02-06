[bits 32]

	;; On rend les points d'entrees visibles

	global			start
	extern			kmain, code, bss, data, end

	;; Informations relatives au boot

	STACK_SIZE		equ 0x4000
	KERNEL_OFFSET		equ 0x00000000

	;; Les macros multiboot
	MULTIBOOT_PAGE_ALIGN	equ 1 << 0
	MULTIBOOT_MEMORY_INFO	equ 1 << 1
	MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
	MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
	MULTIBOOT_CHECKSUM	equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

	section	.bss
	align	0x8
	[global	boot_stack]
boot_stack_top:
	resb	STACK_SIZE               	; On alloue 16ko
boot_stack:
	section	.text
	align	4
MultiBootHeader:
	;; Le heade multiboot GRUB
	dd	MULTIBOOT_HEADER_MAGIC
	dd	MULTIBOOT_HEADER_FLAGS
	dd	MULTIBOOT_CHECKSUM
	dd	code
	dd	bss
	dd	end
	dd	start
start:
	cli
_kernel_start:
	;; On set la stack
	mov	esp, boot_stack
	mov	ebp, boot_stack

	;; On push le magic number
	push	eax

	;; On push les infos de boot
	add	ebx, KERNEL_OFFSET
	push	ebx

	;; On lance le kernel C
	cli
	mov	ecx, kmain
	call	ecx
	hlt
