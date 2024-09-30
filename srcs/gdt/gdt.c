#include "gdt.h"

void gdt_init_descriptor(uint32_t base, uint32_t limit,
	uint8_t access, uint8_t flags, t_gdt_descriptor *desc)
{
    desc->limit_low		= (limit & 0xffff);
    desc->base_low		= (base & 0xffff);
    desc->base_mid		= (base & 0xff0000) >> 16;
    desc->access		= access;
    desc->limit_high	= (limit & 0xf0000) >> 16;
    desc->flags			= (flags & 0xf);
    desc->base_high		= (base & 0xff000000) >> 24;
    return;
}

void gdt_init(void)
{
    /* initialize gdt segments */
    init_gdt_desc(0x0, 0x0, 0x0, 0x0, &gdt[0]);
    init_gdt_desc(0x0, 0xFFFFF, 0x9B, 0x0D, &gdt[1]);    /* code */
    init_gdt_desc(0x0, 0xFFFFF, 0x93, 0x0D, &gdt[2]);    /* data */
    init_gdt_desc(0x0, 0x0, 0x97, 0x0D, &gdt[3]);        /* stack */

    init_gdt_desc(0x0, 0xFFFFF, 0xFF, 0x0D, &gdt[4]);    /* ucode */
    init_gdt_desc(0x0, 0xFFFFF, 0xF3, 0x0D, &gdt[5]);    /* udata */
    init_gdt_desc(0x0, 0x0, 0xF7, 0x0D, &gdt[6]);        /* ustack */

    /* initialize the gdtr structure */
    gdtr->size = (sizeof(gdt) * GDT_SIZE) - 1;
    gdtr->gdt = &gdt;

    /* copy the gdtr to its memory area */
    memcpy((char *) kgdtr.base, (char *) kgdt, kgdtr.limite);

    /* load the gdtr registry */
    asm("lgdtl (kgdtr)");

    /* initiliaz the segments */
    asm("   movw $0x10, %ax    \n \
            movw %ax, %ds    \n \
            movw %ax, %es    \n \
            movw %ax, %fs    \n \
            movw %ax, %gs    \n \
            ljmp $0x08, $next    \n \
            next:        \n");
}
