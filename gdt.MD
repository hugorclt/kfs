## Global Descriptor Table

The GDT is a table that contains the position of some area of memory and define their permissions, the cpu use this table to load instruction from memory.  
The GDT was invented because, a long time ago cpu addresse were referencing real memory location, this was called "real-mode", but this mode create vulnerability because all user program could access to all memory address.
The solution to that was the creation of the GDT, and the creation of the "protected mode"

Each GDT entries is a 64 bit long entries, these entries define where in memory a region start, it's size (known as limit) and it's permissions.

Their are multiple type of entries that can be set:

- CS: code segment
- DS: data segment
- ES, FS, GS: are alternate data register

Once the cpu load the GDT we will set his CS and DS register to the offset of their respective segment in the GDT.

The first entry in the GDT should always be 0 known as the null descriptor.  

Each GDT entries define on what ring is the memory. Ring 0 is kernel-space and Ring 3 is user-space
