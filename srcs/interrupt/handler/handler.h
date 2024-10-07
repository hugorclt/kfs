#pragma once

#define CLOCK			32
#define KEYBOARD		33

typedef void (*t_interrupt_handler)();

void	keyboard_handler();
void	clock_handler();
void	exception_print();
void	gp_handler();

void register_interrupt_handler(int index, t_interrupt_handler func);
void interrupt_handlers_init();
void keyboard_init();
void launch_interrupt(int index);


