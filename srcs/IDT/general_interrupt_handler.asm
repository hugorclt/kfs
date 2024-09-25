extern handle_keyboard_interrupt
extern printk
global interrupt_handler_33

interrupt_handler_33:
	pushad
	cld
	call handle_keyboard_interrupt
	popad
	sti
	iret
