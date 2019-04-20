#include <stdio.h> // printf
#include <string.h> //strtok, strcmp
#include <sys/types.h> // pid
#include <unistd.h> // exec, fork
#include "trimit.h" // trim function
#include "history_queue.h" // all history queue functions and struct


int mysh_history(History_Queue hq) {
    hq_print(hq);
    return 1;
}


int handle_command(History_Queue hq, char *command) {
    char *token = strtok(command, " ");
    if (!strcmp("history", token)) {
        return mysh_history(hq);
    }

}


int main( int argc, char * argv[] ) {
    int should_continue = 1;
    char *line = NULL;
    size_t length = 0;
    ssize_t nread;
    

    // TODO implement the flags
    History_Queue hq = NULL; 
    

    printf("mysh[0]> ");
    while (nread = getline(&line, &length, stdin) != -1) {
        char *trimmed = trim(line);

        if(hq == NULL) {
            hq = hq_create(10, 0, trimmed);
        } else {
            hq = hq_add(hq, trimmed);
        }

        handle_command(hq, trimmed);

        printf("mysh[%lu]> ", hq->last->current_index + 1); 
    }
   
    hq_free_all(hq); 
}

