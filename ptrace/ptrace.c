/* platform: x86-64
 * vim-7.4
 * author: tom
 * date: 2016-06-20
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/reg.h>

int main(int argc, char *argv[])
{
    pid_t child;
    long int orig_rax;
    struct user_regs_struct regs;

    child = fork();
    if(child == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);      // request: referrence to man ptrace
        execl("/bin/ls", "ls", NULL);
    } else {
        wait(NULL);
        memset(&regs, 0x00, sizeof(regs));
     //   orig_rax = ptrace(PTRACE_PEEKUSER, child, 8 * ORIG_RAX, NULL);
        orig_rax = ptrace(PTRACE_GETREGS, child, NULL, &regs);
        if(-1 == orig_rax){
            perror("ptrace failed");
        }else{
            fprintf(stdout, "The child made a system call %lld\n", regs.orig_rax);
        }
        ptrace(PTRACE_CONT, child, NULL, NULL);
    }

    return 0;
}
