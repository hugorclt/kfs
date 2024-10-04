global	isr_stub_table
global 	keyboard_handler_wrapper
global	general_p_fault_wrapper
global	clock_handler_wrapper

extern	keyboard_handler
extern	clock_handler
extern 	exception_print
extern	gp_handler

halt_handler:
	cli
	hlt

exception_handler:
	pusha
	call exception_print
	jmp halt_handler

general_p_fault_wrapper:
	pusha
	cld
	call gp_handler
	jmp halt_handler

keyboard_handler_wrapper:
	pusha
	cld
	call keyboard_handler
	popa
	iret

clock_handler_wrapper:
	pusha
	cld
	call clock_handler
	popa
	iret

%macro isr_err_stub 1
isr_stub_%+%1:
    jmp exception_handler
    iret 
%endmacro

%macro isr_no_err_stub 1
isr_stub_%+%1:
    jmp exception_handler
    iret
%endmacro

isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31

isr_stub_table:
	%assign i 0 
	%rep    32 
	    dd isr_stub_%+i
	%assign i i+1 
	%endrep
