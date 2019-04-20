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


int mysh_bang(History_Queue hq, long num) {
    long low_index = hq->current_index;
    long high_index = hq->last->current_index;
    if(num >= low_index && num < high_index) {
        handle_command(hq, hq_find_command(hq, num));
    }
    //TODO Handle this error somewhere, it is that the command isnt availble
    return -1;
}


int handle_command(History_Queue hq, char *command) {
    char *token = strtok(command, " ");
    int status = 0;
    if (!strcmp("history", token)) {
        status = mysh_history(hq);
    }
    else if (token[0] == '!') {
        long num = strtol(token+1, NULL, 10); 
        status = mysh_bang(hq, num);
    } else {
        printf("Not too sure about %s\n", token);
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

