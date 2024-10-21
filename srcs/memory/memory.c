#include "multiboot.h"
#include "pmm.h"

void memory_init(multiboot_info_t *bootInfo)
{
	pmm_init(bootInfo);
}
