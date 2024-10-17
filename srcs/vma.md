First things firt : PMA -> physical memory allocator

Second we have : VMA -> virtual memory allocator

We have PDE that link virtual address space and physical address space with 4Mib page frame

if we need to add more virtual address space we shall add more Entry in the Page Directory

And we have another structure that's called a FlatList
