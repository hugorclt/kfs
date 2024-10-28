#include "signal.h"
#include "printk.h"

sig_handler_t	signal_function[SIGNAL_MAX];
t_sig_queue	sig_queue;

static void add_element_to_queue(int elem)
{
	sig_queue.data[sig_queue.back] = elem;
	sig_queue.back += 1;
}

static int dequeue()
{
	int temp = sig_queue.data[sig_queue.front];
	sig_queue.front += 1;	
	return (temp);
}

void	print_default_signal_type(int type)
{
	switch (type) {
		case SIGHUP:   printk("SIGHUP\n"); break;
		case SIGINT:   printk("SIGINT\n"); break;
		case SIGQUIT:  printk("SIGQUIT\n"); break;
		case SIGILL:   printk("SIGILL\n"); break;
		case SIGTRAP:  printk("SIGTRAP\n"); break;
		case SIGABRT:  printk("SIGABRT\n"); break;
		case SIGEMT:   printk("SIGEMT\n"); break;
		case SIGFPE:   printk("SIGFPE\n"); break;
		case SIGKILL:  printk("SIGKILL\n"); break;
		case SIGBUS:   printk("SIGBUS\n"); break;
		case SIGSEGV:  printk("SIGSEGV\n"); break;
		case SIGSYS:   printk("SIGSYS\n"); break;
		case SIGPIPE:  printk("SIGPIPE\n"); break;
		case SIGALRM:  printk("SIGALRM\n"); break;
		case SIGTERM:  printk("SIGTERM\n"); break;
		case SIGUSR1:  printk("SIGUSR1\n"); break;
		case SIGUSR2:  printk("SIGUSR2\n"); break;
		case SIGCHLD:  printk("SIGCHLD\n"); break;
		case SIGPWR:   printk("SIGPWR\n"); break;
		case SIGWINCH: printk("SIGWINCH\n"); break;
		case SIGURG:   printk("SIGURG\n"); break;
		case SIGPOLL:  printk("SIGPOLL\n"); break;
		case SIGSTOP:  printk("SIGSTOP\n"); break;
		case SIGTSTP:  printk("SIGTSTP\n"); break;
		case SIGCONT:  printk("SIGCONT\n"); break;
		case SIGTTIN:  printk("SIGTTIN\n"); break;
		case SIGTTOU:  printk("SIGTTOU\n"); break;
		case SIGVTALRM: printk("SIGVTALRM\n"); break;
		case SIGPROF:  printk("SIGPROF\n"); break;
		case SIGXCPU:  printk("SIGXCPU\n"); break;
		case SIGXFSZ:  printk("SIGXFSZ\n"); break;
		case SIGWAITING: printk("SIGWAITING\n"); break;
		case SIGLWP:   printk("SIGLWP\n"); break;
		case SIGAIO:   printk("SIGAIO\n"); break;
		default:       printk("Unknown Signal\n"); break;
	}
}

void	init_signal()
{
	sig_queue.back = 0;
	sig_queue.front = 0;
	for (int i = 0; i < SIGNAL_MAX; i++)
	{
		signal_function[i] = print_default_signal_type;
	}

}

void	raise(int type)
{
	signal_function[type](type);
}

void	register_signal(int sig)
{
	add_element_to_queue(sig);
}

void	raise_queue()
{
	while (sig_queue.back != sig_queue.front)
	{
		int queue_elem = dequeue();
		raise(queue_elem);
	}
}

void	signal(int sig_type, sig_handler_t func)
{
	signal_function[sig_type] = func;
}
