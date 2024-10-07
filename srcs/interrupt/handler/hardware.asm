global 	hardware_handler_wrapper
global	irq_stub_table

extern 	hardware_handler

hardware_handler_wrapper:
	cld
	call hardware_handler
	add esp, 4 ; pop first argument
	popa
	iretd            

%macro irq_stub 2
irq_stub_%+%1:
	pusha
	push byte %2
	jmp hardware_handler_wrapper 
%endmacro


irq_stub 0, 32
irq_stub 1, 33
irq_stub 2, 34
irq_stub 3, 35
irq_stub 4, 36
irq_stub 5, 37
irq_stub 6, 38
irq_stub 7, 39
irq_stub 8, 40
irq_stub 9, 41
irq_stub 10, 42
irq_stub 11, 43
irq_stub 12, 44
irq_stub 13, 45
irq_stub 14, 46
irq_stub 15, 47 

irq_stub_table:
	%assign i 0 
	%rep    16
	dd irq_stub_%+i
	%assign i i+1 
	%endrep
