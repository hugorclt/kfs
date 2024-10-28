#include "signal.h"
#include "printk.h"

void	signal_test(int type)
{
	(void)type;
	printk("SIGHUP: custom handler\n");
}

void	test_default_signal()
{
	printk("Raising default signal SIGHUP:\n");
	raise(SIGHUP);	
	printk("Raising default signal SIGINT:\n");
	raise(SIGINT);
	printk("Changing signal SIGHUP handler to custom function\n");
	signal(SIGHUP, signal_test);
	printk("Raising signal SIGHUP\n");
	raise(SIGHUP);

}

void	test_queue_signal()
{
	printk("Queueing signal : SIGHUP, SIGHUP, SIGSEGV, SIGUSR1\n");
	register_signal(SIGHUP);
	register_signal(SIGHUP);
	register_signal(SIGSEGV);
	register_signal(SIGUSR1);
	raise_queue();

}
