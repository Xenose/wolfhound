#ifndef _wh_header_posix_signal_
#define _wh_header_posix_signal_

#include<signal.h>
#include<wh-core/common.h>
#include<wh-posix/sys/types.h>

#if (WH_SYSTEM&WH_SYS_WINDOWS)

#define SA_NOCLDSTOP 0x0001
#define SA_ONSTACK   0x0002
#define SA_RESETHAND 0x0004
#define SA_RESTART   0x0008
#define SA_SIGINFO   0x0010
#define SA_NOCKDWAIT 0x0020
#define SA_BIDEFER   0x0040

#undef SIGABRT
#undef SIGSEGV

enum {
   SIGABRT,
   SIGALRM,
   SIGBUS,
   SIGCHLD,
   SIGCONT,
   SIGHIP,
   SIGKILL,
   SIGPIPE,
   SIGQUIT,
   SIGSTOP,
   SIGTSTP,
   SIGTTIN,
   SIGSEGV,
   SIGTTOU,
   SIGUSR1,
   SIGUSR2,
   SIGPOLL,
   SIGPROF,
   SIGSYS,
   SIGTRAP,
   SIGURG,
   SIGVTALRM,
   SIGXCPU,
   SIGXFSZ,
};

typedef u64 sigset_t;

union sigval {
   int sival_int;
   void* sival_ptr;
};

struct sigevent {
   int sigev_notify;
   int sigev_signo;
   union sigval sigev_value;
   // typeof(void (union sigval))* sigev_notify_function;
   //pthread_attr_t* sigev_notify_attributes;
   pid_t sigev_notify_thread_id;
};

typedef struct {
   int si_signo;
   int si_code;
   pid_t si_pid;
   uid_t si_uid;
   void* si_addr;
   int   si_status;
   union sigval si_value;
} siginfo_t;

struct sigaction {
   void (*sa_handler)(int);
   sigset_t sa_mask;
   int sa_flags;
   void(* sa_sigaction)(int, siginfo_t*, void*);
};

typedef struct {
   void*    ss_op; // stack base or pointer
   size_t   ss_size; // stack size
   int      ss_flags; // flags
} stack_t;


extern int sigaction(int sig, const struct sigaction* restrict act, struct sigaction* restrict oact);

#endif

#endif /* _wh_header_posix_signal_ */
