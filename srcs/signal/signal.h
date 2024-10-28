#pragma once

#define SIGNAL_MAX 34

#define MAX_QUEUE_ELEM 100

typedef struct s_sig_queue {
	int data[MAX_QUEUE_ELEM];
	int back;
	int front;
} t_sig_queue;

typedef void (*sig_handler_t)(int);

void init_signal();
void signal(int sig_type, sig_handler_t func);
void raise(int sig);
void register_signal(int sig);
void raise_queue();

enum sig_type {
	SIGHUP,
	SIGINT,
	SIGQUIT,
	SIGILL,
	SIGTRAP,
	SIGABRT,
	SIGEMT,
	SIGFPE,
	SIGKILL,
	SIGBUS,
	SIGSEGV,
	SIGSYS,
	SIGPIPE,
	SIGALRM,
	SIGTERM,
	SIGUSR1,
	SIGUSR2,
	SIGCHLD,
	SIGPWR,
	SIGWINCH,
	SIGURG,
	SIGPOLL,
	SIGSTOP,
	SIGTSTP,
	SIGCONT,
	SIGTTIN,
	SIGTTOU,
	SIGVTALRM,
	SIGPROF,
	SIGXCPU,
	SIGXFSZ,
	SIGWAITING,
	SIGLWP,
	SIGAIO,
};

