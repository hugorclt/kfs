global	test_syscall_read_asm

; test_syscall_read(int fd, void * buffer, size_t count)

test_syscall_read_asm:
	mov ebx, [esp + 4]
	mov ecx, [esp + 8]
	mov edx, [esp + 12]

	mov eax, 0 ; syscall mumber READ
	int 0x80	;syscall
	ret 
