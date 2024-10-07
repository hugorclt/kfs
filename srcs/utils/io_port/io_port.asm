global outb
global inb
global iowait
global outw

inb:
	mov edx, [esp + 4]
	in al, dx
	ret

outb:
	mov edx, [esp + 4]
	mov eax, [esp + 8]
	out dx, al
	ret

outw:
	mov edx, [esp + 4]
	mov eax, [esp + 8]
	out dx, ax     ; Output the word in AX to the port in DX
	ret

iowait:
    mov al, 0
    out 0x80, al
    ret
