#include <stdio.h>
#include <sys/types.h> // pid
#include <unistd.h> // exec, fork




int main( int argc, char * argv[] ) {
    int should_continue = 1;
    int count  = 0;
    char *line = NULL;
    size_t length = 0;
    ssize_t nread;
    
    
    printf("mysh[%d]> ", count);

    while (nread = getline(&line, &length, stdin) != -1) {
        printf("mysh[%d]> ", count); 
        printf("%s\n", line);
        count++;
    }

}

