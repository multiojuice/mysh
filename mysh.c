/// Author Owen Sullivan
/// File mysh.c
/// An implementation of a simple shell

#include <errno.h> // errno
#include <stdio.h> // printf
#include <string.h> //strtok, strcmp
#include <sys/wait.h> // wait
#include <sys/types.h> // pid
#include <unistd.h> // exec, fork
#include "trimit.h" // trim function
#include "history_queue.h" // all history queue functions and struct

#define _DEFAULT_SOURCE
#define QUIT 88


// prints out the history project
int mysh_history(History_Queue hq) {
    hq_print(hq);
    return 1;
}

// Executes a command from the history
int mysh_bang(History_Queue hq, long num) {
    long low_index = hq->current_index;
    long high_index = hq->last->current_index;
    if(num >= low_index && num < high_index) {
        handle_command(hq, hq_find_command(hq, num));
    }
    //TODO Handle this error somewhere, it is that the command isnt availble
    return -1;
}


// This is the process that starts a new process and has the parent
// wait on the child to finish. Prints error and returns status
int mysh_external(int argc, char *argv[], int *verbose) {
    pid_t pid = fork();
    int status = 0;
    if(pid == 0) {
        if(*verbose) printf("execvp: %s\n", argv[0]);

        status = execlp(argv[0], argv[0], argv[1], (char *)NULL);
        if (status) perror("Error: ");
        exit(status);
    } else {
        if(*verbose) printf("wait for pid %d: %s\n", pid, argv[0]);
        wait(NULL);
    }
}


// this function prints out the help message
int mysh_help(int argc, char *argv[]) {
    printf("Welcome to mysh(ell)\n\nInternal Commands: \
    \n\thelp             - displays information about mysh and its functionality \
    \n\tquit             - exits the shell safely \
    \n\t!n               - reruns the command at the index n \
    \n\thistory          - prints out the last commands with its index next to it \
    \n\tverbose [on/off] - turn verbose mode (more information) on or off\n \
    \n\nAdditional information: \
    \n\tExternal Commands- trigger commands exactly as you would in bash! \
    \n\tAuthor - Owen Sullivan! \
    \n\tContribution - Come find me on github! \
    \n"
    );

}

// This toggles the verbose mode or prints an error
int mysh_verbose(char *option, int *verbose) {
    if (option == NULL) {
        printf("usage: verbose  on | off\n");
        return 2;
    } else if(!strncmp(option, "on", strlen(option))) {
        *verbose = 1;
    } else if(!strncmp(option, "off", strlen(option))) {
        *verbose = 0;
    } else {
        printf("usage: verbose  on | off\n");
        return 2;
    }
    return 1; 
}


// This is the general function that parses the command
// And then sends it to the correct funtion to run
int handle_command(History_Queue hq, char *command, int *verbose) {
    if(*verbose) printf("command: %s\n", command);

    char *token = strtok(command, " ");
    int status = 0;
    if (token == NULL) {
        return 1;
    } else if (!strcmp("history", token)) {
        status = mysh_history(hq);

    } else if (!strcmp("quit", token)) {
        return QUIT;

    } else if (!strcmp("help", token)) {
        status = mysh_help(0, NULL);
    
    } else if (!strncmp("verbose", token, strlen(token))) {
        status = mysh_verbose(trim(strtok(NULL, " ")), verbose);

    } else if (token[0] == '!') {
        long num = strtol(token+1, NULL, 10);
        status = mysh_bang(hq, num);

    } else {
        char *argv[2];
        argv[0] = token;
        argv[1] = strtok(NULL, "");
        status = mysh_external(2,argv, verbose);
    }
    
    if(*verbose) printf("command status: %d\n", status);
}


// Controls the main loop of the shell
// Changes things based on the input flags
int main( int argc, char * argv[] ) {
    int should_continue = 1;
    char *line = NULL;
    size_t length = 0;
    ssize_t nread;
    int opt;
    int verbose = 0;
    int history = 10;

    while((opt = getopt(argc, argv, "h:v")) != -1) {
        switch (opt) {
            case 'v':
                verbose = 1;
                break;
            case 'h':
                history = (int) strtol(optarg, NULL, 10);
                break;
        }
    }
 

    // TODO implement the flags
    History_Queue hq = NULL; 
 

    printf("mysh[0]> ");
    while (nread = getline(&line, &length, stdin) != -1) {
        char *trimmed = trim(line);

        if(hq == NULL) {
            hq = hq_create(history, 0, trimmed);
        } else {
            hq = hq_add(hq, trimmed);
        }

        int status = handle_command(hq, trimmed, &verbose);

        if(status == QUIT) {
            free(trimmed);   
            break;
        }
        printf("mysh[%lu]> ", hq->last->current_index + 1); 
    }
   
    hq_free_all(hq); 
}

