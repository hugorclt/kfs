#include "io_port.h"
#include "printk.h"
#include "handler.h"
#include <stdint.h>

#define PIT_CHANNEL0 0x40
#define PIT_COMMAND 0x43
#define PIT_BASE_FREQ 1193182
volatile uint64_t ticks = 0;

void timer_handler(void)
{
    ticks++;
    // if ((uint32_t)ticks % 100 == 0)
    //     printk("tick %u\n", (uint32_t)ticks);
}

void timer_init(uint32_t frequency) {
    uint32_t divisor = PIT_BASE_FREQ / frequency;

    outb(PIT_COMMAND, 0x36);
    outb(PIT_CHANNEL0, divisor & 0xFF);
    outb(PIT_CHANNEL0, (divisor >> 8) & 0xFF);

    register_interrupt_handler(CLOCK, timer_handler);
}