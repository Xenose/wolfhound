#include<wh-posix/errno.h>
#include<wh-posix/unistd.h>
#include<wh-posix/libproc.h>

#include<wh-posix/string.h>
#include<wh-posix/stdio.h>

int proc_read(pid_t pid, proc_status_t* status) {
    if (nullptr == status) {
        errno = EINVAL;
        return -1;
    }

    memset(status, 0, sizeof(proc_status_t));

    status->pr_pid = pid;
    status->pr_pgid = getpgid(pid);

    if (-1 == status->pr_pgid) {
        // TODO file fallback
    }

    return 0;
}

void proc_print(proc_status_t* status) {
    printf(
        "\n[ PROC INFO ]\n\n"
        "\tProcess ID:          %i\n"
        "\tParent process ID:   %i\n"
        "\tGroup process ID:    %i\n"
        "\n",
        status->pr_pid,     // process ID:
        status->pr_ppid,    // parent process ID
        status->pr_pgid     // group process ID
    );
}
