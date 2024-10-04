#include "gdt.h"
#include "utils.h"
#include <stdint.h>

t_gdtr gdtr;
static t_gdt_descriptor gdt[GDT_SIZE];

static void	gdt_init_descriptor(uint32_t base, uint32_t limit,
		uint8_t access, uint8_t flags, t_gdt_descriptor *desc)
{
	desc->base_low = (base & 0xFFFF);
	desc->base_mid = (base >> 16) & 0xFF;
	desc->base_high = (base >> 24) & 0xFF;
	desc->limit_low = (limit & 0xFFFF);
	desc->flags = (limit >> 16) & 0x0F;
	desc->flags |= flags & 0xF0;
	desc->access = access;
	return;
}

void	gdt_init(void)
{
	gdt_init_descriptor(0x0, 0x0, 0x0, 0x0, &gdt[0]);		/* NULL */
	gdt_init_descriptor(0x0, 0xFFFFF, 0x9A, 0xCF, &gdt[1]);	/* code */
	gdt_init_descriptor(0x0, 0xFFFFF, 0x93, 0xCF, &gdt[2]);	/* data */
	gdt_init_descriptor(0x0, 0xFFFFF, 0x97, 0xCF, &gdt[3]);	/* stack */

	gdt_init_descriptor(0x0, 0xFFFFF, 0xFF, 0xCF, &gdt[4]);	/* ucode */
	gdt_init_descriptor(0x0, 0xFFFFF, 0xF3, 0xCF, &gdt[5]);	/* udata */
	gdt_init_descriptor(0x0, 0xFFFFF, 0xF7, 0xCF, &gdt[6]);	/* ustack */

	gdtr.size = (sizeof(t_gdt_descriptor) * GDT_SIZE) - 1;
	gdtr.gdt = GDT_BASE;

	memcpy((char *)gdtr.gdt, (char *)gdt, gdtr.size);

	load_gdt(&gdtr);
}
