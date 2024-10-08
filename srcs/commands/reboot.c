#include "commands.h"
#include "io_port.h"

#define KBRD_INTRFC 0x64

#define KBRD_BIT_KDATA 0
#define KBRD_BIT_UDATA 1

#define KBRD_IO 0x60 
#define KBRD_RESET 0xFE

#define bit(n) (1<<(n)) /* Set bit n to 1 */

/* Check if bit n in flags is set */
#define check_flag(flags, n) ((flags) & bit(n))

void cmd_reboot()
{
    uint8_t temp;

    asm volatile ("cli"); /* disable all interrupts */

    do
    {
        temp = inb(KBRD_INTRFC);
        if (check_flag(temp, KBRD_BIT_KDATA) != 0)
            inb(KBRD_IO);
    } while (check_flag(temp, KBRD_BIT_UDATA) != 0);

    outb(KBRD_INTRFC, KBRD_RESET);
loop:
    asm volatile ("hlt");
    goto loop;
}
