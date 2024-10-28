#pragma once

#include "stddef.h"
#include "stdint.h"

#define CLOCK			32
#define KEYBOARD		33

typedef void (*t_interrupt_handler)();

void	keyboard_handler();

void	register_interrupt_handler(int index, t_interrupt_handler func);
void	interrupt_handlers_init();
void	keyboard_init();
void	launch_interrupt(int index);
void	switch_layout();

char	get_last_char();


// syscall

// typedef struct __attribute__((packed)) s_register {
// 	uint32_t eax;
// 	uint32_t ebx;
// 	uint32_t ecx;
// 	uint32_t edx;
// 	uint32_t esi;
// 	uint32_t edi;
// } t_register;

typedef struct __attribute__((packed)) s_pt_regs {
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
    uint32_t ds;
    uint32_t es;
    uint32_t fs;
    uint32_t gs;
    uint32_t eax; // Original syscall number for restarting the syscall
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t esp;
    uint32_t ss;
}	t_pt_regs;

# define SYSCALL_READ 0
# define ENOSYS 38
