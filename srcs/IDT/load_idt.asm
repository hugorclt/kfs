global load_idt
global outb
global inb
global segments_load_registers

inb:
	mov edx, [esp + 4]
	in al, dx
	ret

outb:
	mov edx, [esp + 4]
	mov eax, [esp + 8]
	out dx, al
	ret

load_idt:
        mov edx, [esp + 4]
        lidt [edx]
        ret

segments_load_registers:
	mov ax, 0x10
	mov ds, ax ; 0x10 - an offset into GDT for the third (kernel data segment) record.
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	jmp 0x08:flush_cs ; 0x08 - an offset into GDT for the second (kernel code segment) record. 

flush_cs:
	ret

