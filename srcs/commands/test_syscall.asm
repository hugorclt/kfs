global	test_syscall_read_asm
extern printk
; test_syscall_read(int fd, void * buffer, size_t count)

test_syscall_read_asm:
	push ebx
	push ecx
	push edx
	mov ebx, [esp + 4 + 12]
	mov ecx, [esp + 8 + 12]
	mov edx, [esp + 12 + 12]

	mov eax, 0 ; syscall number READ
	int 0x80	;syscall
	pop edx
	pop ecx
	pop ebx

	ret
