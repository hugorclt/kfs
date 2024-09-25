global load_idt
global outb
global inb

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

