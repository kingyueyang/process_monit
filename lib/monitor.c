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
int check_child(void(*ptr)(), int _count);
int mni_fork(unsigned int forknum, void(*ptr)(), const char *eval, int count);

int
main(int argc, char *argv[]) {
    mni_fork(2, example_2, "", 0);

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void
example_1(void) {
    printf("%d\n", getpid());
    while(1) {
        sleep(1);
        printf("examplt 1...\n");
    }

    return ;
}

void
example_2(void) {
    printf("%d\n", getpid());
    while(1) {
        sleep(1);
        printf("examplt 2...\n");
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
            /*Do something*/
            (*ptr)();
            return 0;
        } else {
            /*printf("I am farther,child is %d,index is %d\n", pid, i);*/
        }
    }

    check_child(ptr, count);
    return 0;
}

int
check_child(void(*ptr)(), int _count) {
    pid_t pid;

    for(;;) {
        pid = waitpid(-1, NULL, 0);
        if ( pid < 0 ) {
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

        /*
         *FIXME: multi child and _count > 0
         *           parent return brfore child
         *           SO we must kill all child
         */
        if(_count > 0) {
            mni_fork(1, *ptr, "", --_count);
        } else {
            mni_fork(1, *ptr, "", -1);
        }

        return 0;
    }

    return 0;
}

