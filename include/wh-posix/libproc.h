#ifndef _wh_header_posix_libproc_
#define _wh_header_posix_libproc_

#include <wh-core/os.h>
#include <wh-posix/signal.h>
#include <wh-posix/sys/types.h>

// Note : The name and semantics shift a bit from solaris,
// so to reflect this change we named it proc_xxx in the
// common interface over Pgrab, also the name convention
// is more inline with the rest of wh-posix.
//
// Specs:
// libproc :: https://docs.oracle.com/cd/E88353_01/html/E37842/libproc-3lib.html
// proc    :: https://docs.oracle.com/cd/E88353_01/html/E37852/proc-5.html

#if (WH_SYSTEM&WH_SYS_SOLARIS)
    #include <wh-posix/libproc.h>

    #define proc_grab       Pgrab
    #define proc_release    Prelease
    #define proc_free       Pfree
    #define proc_grab_error Pgrab_error
#else
    typedef intptr_t zoneid_t; // linux cgroup and bsd jail
    typedef intptr_t poolid_t;
    typedef intptr_t ctid_t;
    typedef intptr_t processorid_t;
    typedef intptr_t psetid_t;
    typedef intptr_t lgrp_id_t;
    typedef intptr_t hrtime_t;
    typedef intptr_t priv_chunk_t;
                               
    typedef struct {
        void* todo;
    } fltset_t;

    typedef struct{
        void* todo;
    } sysset_t;

    typedef struct{
        void* todo;
    } taskid_t;

    typedef struct{
        void* todo;
    } projid_t;

    typedef struct {
        void* todo;
    } prgregset_t;

    typedef struct {
        void* todo;
    } prfpregset_t;

    // TODO check these
    #define PRSYSARGS 1024
    #define PRCLSZ 1024
    #define PRFNSZ 1024
    #define PRARGSZ 1024
    #define PRLNSZ 1024

    typedef struct lwpstatus {
        int                  pr_flags;                /* flags (see below) */
        id_t                 pr_lwpid;                /* specific lwp identifier */
        short                pr_why;                  /* reason for lwp stop, if stopped */
        short                pr_what;                 /* more detailed reason */
        short                pr_cursig;               /* current signal, if any */
        unsigned char        pr_adi;                  /* state of ADI for this lwp */
        siginfo_t            pr_info;                 /* info associated with signal or fault */
        sigset_t             pr_lwppend;              /* set of signals pending to the lwp */
        sigset_t             pr_lwphold;              /* set of signals blocked by the lwp */
        struct sigaction     pr_action;               /* signal action for current signal */
        stack_t              pr_altstack;             /* alternate signal stack info */
        uintptr_t            pr_oldcontext;           /* address of previous ucontext */
        short                pr_syscall;              /* system call number (if in syscall) */
        short                pr_nsysarg;              /* number of arguments to this syscall */
        int                  pr_errno;                /* errno for failed syscall */
        long                 pr_sysarg[PRSYSARGS];    /* arguments to this syscall */
        long                 pr_rval1;                /* primary syscall return value */
        long                 pr_rval2;                /* second syscall return value, if any */
        char                 pr_clname[PRCLSZ];       /* scheduling class name */
        struct timespec      pr_tstamp;               /* real-time time stamp of stop */
        struct timespec      pr_utime;                /* lwp user cpu time */
        struct timespec      pr_stime;                /* lwp system cpu time */
        int                  pr_errpriv;              /* missing privilege */
        uintptr_t            pr_ustack;               /* stack boundary data (stack_t) address */
        unsigned long        pr_instr;                /* current instruction */
        prgregset_t          pr_reg;                  /* general registers */
        prfpregset_t         pr_fpreg;                /* floating-point registers */
    } lwpstatus_t;

    typedef struct pstatus {
         int                 pr_flags;        /* flags (see below) */
         int                 pr_nlwp;         /* number of active lwps in the process */
         pid_t               pr_pid;          /* process id */
         pid_t               pr_ppid;         /* parent process id */
         pid_t               pr_pgid;         /* process group id */
         pid_t               pr_sid;          /* session id */
         // id_t                pr_aslwpid;      /* obsolete */
         id_t                pr_agentid;      /* lwp-id of the agent lwp, if any */
         sigset_t            pr_sigpend;      /* set of process pending signals */
         uintptr_t           pr_brkbase;      /* virtual address of the process heap */
         size_t              pr_brksize;      /* size of the process heap, in bytes */
         uintptr_t           pr_stkbase;      /* virtual address of the process stack */
         size_t              pr_stksize;      /* size of the process stack, in bytes */
         struct timespec     pr_utime;        /* process user cpu time */
         struct timespec     pr_stime;        /* process system cpu time */
         struct timespec     pr_cutime;       /* sum of children's user times */
         struct timespec     pr_cstime;       /* sum of children's system times */
         sigset_t            pr_sigtrace;     /* set of traced signals */
         fltset_t            pr_flttrace;     /* set of traced faults */
         sysset_t            pr_sysentry;     /* set of system calls traced on entry */
         sysset_t            pr_sysexit;      /* set of system calls traced on exit */
         char                pr_dmodel;       /* data model of the process */
         unsigned char       pr_adi_nbits;    /* # of VA bits used by ADI when enabled */
         taskid_t            pr_taskid;       /* task id */
         projid_t            pr_projid;       /* project id */
         int                 pr_nzomb;        /* number of zombie lwps in the process */
         zoneid_t            pr_zoneid;       /* zone id */
         int                 pr_fdrlimit;     /* current limit for number of fds in process */
         lwpstatus_t         pr_lwp;          /* status of the representative lwp */
    } proc_status_t;

    typedef struct lwpsinfo {
        //int             pr_flag;              /* lwp flags (DEPRECATED: see below) */
        id_t            pr_lwpid;               /* lwp id */
        // uintptr_t    pr_addr;                /* DEPRECATED was internal address of lwp */
        // uintptr_t    pr_wchan;               /* DEPRECATED was wait addr for sleeping lwp */
        char            pr_stype;               /* synchronization event type */
        char            pr_state;               /* numeric lwp state */
        char            pr_sname;               /* printable character for pr_state */
        char            pr_nice;                /* nice for cpu usage */
        short           pr_syscall;             /* system call number (if in syscall) */
        char            pr_oldpri;              /* pre-SVR4, low value is high priority */
        char            pr_cpu;                 /* pre-SVR4, cpu usage for scheduling */
        int             pr_pri;                 /* priority, high value = high priority */
        unsigned short  pr_pctcpu;              /* % of recent cpu time used by this lwp */
        struct timespec pr_start;               /* lwp start time, from the epoch */
        struct timespec pr_time;                /* cpu time for this lwp */
        char            pr_clname[PRCLSZ];      /* scheduling class name */
        processorid_t   pr_onpro;               /* processor which last ran this lwp */
        processorid_t   pr_bindpro;             /* processor to which lwp is bound */
        psetid_t        pr_bindpset;            /* processor set to which lwp is bound */
        lgrp_id_t       pr_lgrp;                /* home lgroup */
        hrtime_t        pr_last_onproc;         /* Timestamp of when thread last ran on */
        /* a processor */
        char            pr_name[PRLNSZ];        /* name of system lwp */
    } lwpsinfo_t;

    typedef struct psinfo {
        // int             pr_flag;                 /* process flags (DEPRECATED: see below) */
        int             pr_nlwp;                 /* number of active lwps in the process */
        pid_t           pr_pid;                  /* process id */
        pid_t           pr_ppid;                 /* process id of parent */
        pid_t           pr_pgid;                 /* process id of process group leader */
        pid_t           pr_sid;                  /* session id */
        uid_t           pr_uid;                  /* real user id */
        uid_t           pr_euid;                 /* effective user id */
        gid_t           pr_gid;                  /* real group id */
        gid_t           pr_egid;                 /* effective group id */
        // uintptr_t       pr_addr;               /* DEPRECATED was address of process */
        size_t          pr_size;                 /* size of process image in Kbytes */
        size_t          pr_rssize;               /* resident set size in Kbytes */
        size_t          pr_rssizepriv;           /* resident set size of private mappings */
        dev_t           pr_ttydev;               /* controlling tty device (or PRNODEV) */
        unsigned short  pr_pctcpu;               /* % of recent cpu time used by all lwps */
        unsigned short  pr_pctmem;               /* % of system memory used by process */
        struct timespec pr_start;                /* process start time, from the epoch */
        struct timespec pr_time;                 /* cpu time for this process */
        struct timespec pr_ctime;                /* cpu time for reaped children */
        char            pr_fname[PRFNSZ];        /* name of exec'ed file */
        char            pr_psargs[PRARGSZ];      /* initial characters of arg list */
        int             pr_wstat;                /* if zombie, the wait() status */
        int             pr_argc;                 /* initial argument count */
        uintptr_t       pr_argv;                 /* address of initial argument vector */
        uintptr_t       pr_envp;                 /* address of initial environment vector */
        char            pr_dmodel;               /* data model of the process */
        taskid_t        pr_taskid;               /* task id */
        projid_t        pr_projid;               /* project id */
        int             pr_nzomb;                /* number of zombie lwps in the process */
        poolid_t        pr_poolid;               /* pool id */
        zoneid_t        pr_zoneid;               /* zone id */
        ctid_t          pr_contract;             /* process contract id */
        lwpsinfo_t      pr_lwp;                  /* information for representative lwp */
    } proc_sinfo_t;

    typedef struct prcred {
        uid_t pr_euid;      /* effective user id */
        uid_t pr_ruid;      /* real user id */
        uid_t pr_suid;      /* saved user id (from exec) */
        gid_t pr_egid;      /* effective group id */
        gid_t pr_rgid;      /* real group id */
        gid_t pr_sgid;      /* saved group id (from exec) */
        int pr_ngroups;     /* number of supplementary groups */
        gid_t pr_groups[1]; /* array of supplementary groups */
    } proc_rcred_t;

    typedef struct prpriv {
        uint32_t        pr_nsets;      /* number of privilege set */
        uint32_t        pr_setsize;    /* size of privilege set */
        uint32_t        pr_infosize;   /* size of supplementary data */
        priv_chunk_t    pr_sets[1];    /* array of sets */
    } proc_rpriv_t;

    pid_t proc_grab(pid_t pid, int flags, int* error);
    pid_t proc_release(pid_t pid);
    pid_t proc_free(pid_t pid);
    pid_t proc_signal(pid_t pid, int sig);
#endif

    /* Non-invasive, non-freezing information reader */
    int proc_read(pid_t pid, proc_status_t* status);

#endif /* _wh_header_posix_libproc_ */
