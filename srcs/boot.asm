; Declare constants for the multiboot header.
MBALIGN  equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ; provide memory map
MBFLAGS  equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + MBFLAGS)   ; checksum of above, to prove we are multiboot

; Declare a multiboot header that marks the program as a kernel. These are magic
; values that are documented in the multiboot standard. The bootloader will
; search for this signature in the first 8 KiB of the kernel file, aligned at a
; 32-bit boundary. The signature is in its own section so the header can be
; forced to be within the first 8 KiB of the kernel file.
section .multiboot
align 4
	dd MAGIC
	dd MBFLAGS
	dd CHECKSUM

KERNEL_VIRTUAL_BASE equ 0xC0000000                  ; 3GB
KERNEL_PAGE_NUMBER equ (KERNEL_VIRTUAL_BASE >> 22)  ; Page directory index of kernel's 4MB PTE.


section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB
stack_top:


section .text
global _start:function (_start.end - _start)
_start:

	; To set up a stack, we set the esp register to point to the top of our
	; stack (as it grows downwards on x86 systems). This is necessarily done
	; in assembly as languages such as C cannot function without a stack.
	mov esp, stack_top

	extern kernel_main
	call kernel_main

	
	cli
.hang:	hlt
	jmp .hang
.end:

section .data
align 4096
initial_page_dir:
	dd 10000011b	;flags: Present | Read-Write | 4MiB Page / No table
	times (KERNEL_PAGE_NUMBER - 1) dd 0 ; padding

	dd ( 0 << 22 ) | 10000011b ; address
	dd ( 1 << 22 ) | 10000011b
	dd ( 2 << 22 ) | 10000011b
	dd ( 3 << 22 ) | 10000011b
