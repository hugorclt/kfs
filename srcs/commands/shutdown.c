#include "commands.h"
#include "io_port.h"

void shutdown() 
{
   outw(0x604, 0x2000);
}
