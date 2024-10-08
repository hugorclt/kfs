#include "commands.h"
#include "io_port.h"

void cmd_shutdown() 
{
   outw(0x604, 0x2000);
}
