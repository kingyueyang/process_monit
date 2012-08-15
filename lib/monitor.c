/*
 * =====================================================================================
 *
 *       Filename:  moniter.c
 *
 *    Description:  Moniter for process
 *
 *        Version:  1.0
 *        Created:  08/14/2012 04:31:46 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YueYang (feinno), yueyang@feinno.com
 *        Company:  FCT
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

void example_1(void);
void example_2(void);
int check_child(void(*_ptr)(), const char* _eval, int _count);
int mni_fork(unsigned int forknum, void(*ptr)(), const char *eval, int count);

int
main(int argc, char *argv[]) {
    mni_fork(2, example_2, "", 1);

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void
example_1(void) {
    printf("%d\n", getpid());
    while(1) {
        sleep(5);
        printf("%d:examplt 1...\n", getpid());
    }

    return ;
}

void
example_2(void) {
    printf("%d\n", getpid());
    while(1) {
        sleep(5);
        printf("%d:examplt 2...\n", getpid());
    }

    return ;
}

int
mni_fork(unsigned int forknum, void(*ptr)(), const char *eval, int count) {
    /*
     *TODO: judgment function or executed
     */
    int i;
    pid_t pid;

    for(i = 0; i < forknum; ++i) {
        pid = fork();

        if(-1 == pid) {
            /* Error */
            perror("Create process error!\n");
            return -1;
        }
        if(0 == pid) {
            /* Child */
            (*ptr)();
            return 0;
        } else {
            /* Parent */
            printf("child: %d\n", getppid());
        }
    }

    check_child(ptr, eval, count);
    return 0;
}

int
check_child(void(*_ptr)(), const char* _eval, int _count) {
    pid_t pid;

    for(;;) {
        pid = waitpid(-1, NULL, 0);
        if(pid < 0) {
            sleep(1);
            continue;
        }
        printf("terminal %d\n", pid);

        /*
         *_count equl 0:
         *     Don't up child
         *greater than 0:
         *     Up _count times
         *equl -1:
         *     always up
         */
        if(0 == _count) {
            printf("chile %d terminal\n", pid);
            return 0;
        }

        if(_count > 0) {
            mni_fork(1, *_ptr, "", --_count);
        } else {
            mni_fork(1, *_ptr, "", -1);
        }

        break;
    }

    return 0;
}

