	[BITS 32]
	section .text
	global vmm_paging_enable, vmm_paging_load_page_directory, vmm_paging_enable_pse

;; void vmm_paging_load_page_directory(void *page_directory)
vmm_paging_load_page_directory:
	mov eax, [ebp + 8]
	mov cr3, eax
	ret

;; void vmm_paging_enable_pse(void)
;; Allows 4MB pages
vmm_paging_enable_pse:
	mov	ecx, cr4
	or	ecx, 0x00000010
	mov	cr4, ecx
	ret

;; void vmm_paging_enable(void)
vmm_paging_enable:
	mov	eax, cr0
	or	eax, 0x80000000
	mov	cr0, eax
	ret