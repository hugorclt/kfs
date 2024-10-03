#include "gdt.h"
#include "utils.h"

t_gdtr					gdtr;
static t_gdt_descriptor gdt[GDT_SIZE];

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
    gdt_init_descriptor(0x0, 0x0, 0x0, 0x0, &gdt[0]);		/* NULL */
    gdt_init_descriptor(0x0, 0xFFFFF, 0x9B, 0x0D, &gdt[1]);	/* code */
    gdt_init_descriptor(0x0, 0xFFFFF, 0x93, 0x0D, &gdt[2]);	/* data */
    gdt_init_descriptor(0x0, 0xFFFFF, 0x97, 0x0D, &gdt[3]);	/* stack */

    gdt_init_descriptor(0x0, 0xFFFFF, 0xFF, 0x0D, &gdt[4]);	/* ucode */
    gdt_init_descriptor(0x0, 0xFFFFF, 0xF3, 0x0D, &gdt[5]);	/* udata */
    gdt_init_descriptor(0x0, 0xFFFFF, 0xF7, 0x0D, &gdt[6]);	/* ustack */

    gdtr.size = (sizeof(t_gdt_descriptor) * GDT_SIZE) - 1;
    gdtr.gdt = GDT_BASE;

    memcpy((char *)gdtr.gdt, (char *)gdt, gdtr.size);

    load_gdt(&gdtr);
}
