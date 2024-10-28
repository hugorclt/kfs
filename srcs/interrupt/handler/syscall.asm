global syscall_handler_wrapper
syscall_handler_wrapper:
	pushad
	push ds
	push fs
	push gs
	push es

	mov ax, 0x10 ; kernel data seg
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	push edi
	push esi
	push edx
	push ecx
	push ebx
	push eax
	call syscall_handler

	pop es
	pop gs
	pop fs
	pop ds

	popad
	iretd
