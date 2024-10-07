global 	hardware_handler_wrapper
global	hardware_isr_stub_table

extern 	hardware_handler

hardware_handler_wrapper:
	cld
	call hardware_handler
	add esp, 4 ; pop first argument
	popa
	iretd            

%macro isr_stub 2
isr_stub_%+%1:
	pusha
	push byte %2
	jmp hardware_handler_wrapper 
%endmacro


isr_stub 0, 32
isr_stub 1, 33
isr_stub 2, 34
isr_stub 3, 35
isr_stub 4, 36
isr_stub 5, 37
isr_stub 6, 38
isr_stub 7, 39
isr_stub 8, 40
isr_stub 9, 41
isr_stub 10, 42
isr_stub 11, 43
isr_stub 12, 44
isr_stub 13, 45
isr_stub 14, 46
isr_stub 15, 47 

hardware_isr_stub_table:
	%assign i 0 
	%rep    16
	dd isr_stub_%+i
	%assign i i+1 
	%endrep
