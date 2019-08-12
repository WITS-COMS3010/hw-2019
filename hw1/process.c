#include "process.h"
#include "shell.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <termios.h>

/**
 *  Executes the process p.
 *  If the shell is in interactive mode and the process is a foreground process,
 *  then p should take control of the terminal.
 *
 */
void launch_process(process *p) {
    /** TODO **/
}

/**
 *  Put a process in the foreground. This function assumes that the shell
 *  is in interactive mode. If the cont argument is true, send the process
 *  group a SIGCONT signal to wake it up.
 *
 */
void put_process_in_foreground (process *p, int cont) {
    /** TODO **/
}

/**
 *  Put a process in the background. If the cont argument is true, send
 *  the process group a SIGCONT signal to wake it up. 
 *
 */
void put_process_in_background (process *p, int cont) {
    /** TODO **/
}

/**
 *  Prints the list of processes.
 *
 */
void print_process_list(void) {
    process* curr = first_process;
    while(curr) {
        if(!curr->completed) {
            printf("\n");
            printf("PID: %d\n",curr->pid);
            printf("Name: %s\n",curr->argv[0]);
            printf("Status: %d\n",curr->status);
            printf("Completed: %s\n",(curr->completed)?"true":"false");
            printf("Stopped: %s\n",(curr->stopped)?"true":"false");
            printf("Background: %s\n",(curr->background)?"true":"false");
            printf("Prev: %lx\n",(unsigned long)curr->prev);
            printf("Next: %lx\n",(unsigned long)curr->next);
        }
        curr=curr->next;
    }
}