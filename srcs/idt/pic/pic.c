#include "pic.h"
#include <stdint.h>
#include "io_port.h"

void pic_send_eoi(uint8_t irq)
{
	if(irq >= 8)
		outb(PIC2_COMMAND,PIC_EOI);	
	outb(PIC1_COMMAND,PIC_EOI);
}

void	pic_init(int offset1, int offset2)
{
	//INITIALIZE PIC IN CASCADE MODE (MASTER-SLAVE RELATION)
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4); 
	iowait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	iowait();

	//Tell the pic where are they in terms of IRQ Index
	outb(PIC1_DATA, offset1);
	iowait();
	outb(PIC2_DATA, offset2);
	iowait();

	//Configure the master pic to tell it that slave take IRQ#2
	outb(PIC1_DATA, 0x04);
	iowait();
	outb(PIC2_DATA, 0x02);
	iowait();
	
	//Tell the pic that we're in x86 mode (16 bits compatibility with 32bits)
	outb(PIC1_DATA, ICW4_8086);
	iowait();
	outb(PIC2_DATA, ICW4_8086);
	iowait();
	
	//Clear mask
	// outb(PIC1_DATA, 0x00);
	// outb(PIC2_DATA, 0x00);

	// Disable everything
	outb(PIC1_DATA, 0xFF);
	outb(PIC2_DATA, 0xFF);

	// Disable everything but keyboard
	outb(PIC1_DATA, 0xFD);
}
