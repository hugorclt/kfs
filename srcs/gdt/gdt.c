#include "gdt.h"
#include "utils.h"
#include <stdint.h>

t_gdtr *gdt_ptr = (t_gdtr*)GDT_BASE;
static t_gdt_descriptor gdt[GDT_SIZE];

// static void gdt_init_descriptor(int num, uint32_t base, uint32_t limit, uint32_t access, uint32_t gran)
// {
   // gdt[num].base_low = (base & 0xFFFF);
   // gdt[num].base_mid = (base >> 16) & 0xFF;
   // gdt[num].base_high = (base >> 24) & 0xFF;
   // gdt[num].limit_low = (limit & 0xFFFF);
   // gdt[num].flags = (limit >> 16) & 0x0F;
   // gdt[num].flags |= gran & 0xF0;
   // gdt[num].access = access;
// }

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
   //  desc->limit_low		= (limit & 0xffff);
   //  desc->base_low		= (base & 0xffff);
   //  desc->base_mid		= (base & 0xff0000) >> 16;
   //  desc->access		= access;
   // desc->flags = (limit >> 16) & 0x0F;
   // desc->flags |= flags & 0xF0;
   //  desc->base_high		= (base & 0xff000000) >> 24;
    return;
}

void	gdt_init(void)
{
    // gdt_init_descriptor(0, 0x0, 0x0, 0x0, 0x0);		/* NULL */
    // gdt_init_descriptor(1, 0x0, 0xFFFFF, 0x9A, 0xCF);	/* code */
    // gdt_init_descriptor(2, 0x0, 0xFFFFF, 0x93, 0xCF);	/* data */
    // gdt_init_descriptor(3, 0x0, 0xFFFFF, 0x97, 0xCF);	/* stack */
    //
    // gdt_init_descriptor(4, 0x0, 0xFFFFF, 0xFF, 0xCF);	/* ucode */
    // gdt_init_descriptor(5, 0x0, 0xFFFFF, 0xF3, 0xCF);	/* udata */
    // gdt_init_descriptor(6, 0x0, 0xFFFFF, 0xF7, 0xCF);	/* ustack */

        gdt_init_descriptor(0x0, 0x0, 0x0, 0x0, &gdt[0]);		/* NULL */
    gdt_init_descriptor(0x0, 0xFFFFF, 0x9A, 0xCF, &gdt[1]);	/* code */
    gdt_init_descriptor(0x0, 0xFFFFF, 0x93, 0xCF, &gdt[2]);	/* data */
    gdt_init_descriptor(0x0, 0xFFFFF, 0x97, 0xCF, &gdt[3]);	/* stack */

    gdt_init_descriptor(0x0, 0xFFFFF, 0xFF, 0xCF, &gdt[4]);	/* ucode */
    gdt_init_descriptor(0x0, 0xFFFFF, 0xF3, 0xCF, &gdt[5]);	/* udata */
    gdt_init_descriptor(0x0, 0xFFFFF, 0xF7, 0xCF, &gdt[6]);	/* ustack */
    	gdt_ptr->size = (sizeof(t_gdt_descriptor) * GDT_SIZE) - 1;
	gdt_ptr->gdt = ((uint32_t)(&gdt));

    // gdtr.size = (sizeof(t_gdt_descriptor) * GDT_SIZE) - 1;
    // gdtr.gdt = GDT_BASE;

    // memcpy((char *)gdtr.gdt, (char *)gdt, gdtr.size);

    load_gdt((uint32_t)gdt_ptr);
}
