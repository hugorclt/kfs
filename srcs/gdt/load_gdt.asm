global load_gdt

load_gdt:
	mov eax, [esp + 4]
	lgdt [eax]
	mov ax, 0x10	; 0x10 --> offset of data descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ax, 0x18	; 0x18 --> offset of stack descriptor
	mov ss, ax
	jmp 0x08:.flush	; 0x08 --> offset of code descriptor
.flush:
	ret
