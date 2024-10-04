#pragma once

#define CLOCK_IRQ		0
#define KEYBOARD_IRQ	1

void	keyboard_handler();
void	clock_handler();
void	exception_print();
void	gp_handler();

