global outb
global inb
global iowait

inb:
	mov edx, [esp + 4]
	in al, dx
	ret

outb:
	mov edx, [esp + 4]
	mov eax, [esp + 8]
	out dx, al
	ret

iowait:
    mov al, 0
    out 0x80, al
    ret
