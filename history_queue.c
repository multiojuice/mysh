#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history_queue.h"


History_Queue hq_create(size_t max_size, size_t current_index, char *command) {
    History_Queue hq = malloc(sizeof(struct History_Queue_S));

    hq->max_size = max_size;
    hq->current_index = current_index;

    hq->command = malloc(strlen(command) + 1);
    strcpy(hq->command, command);

    hq->next = NULL;
    hq->last = hq;
    return hq;
}


void hq_free_node(History_Queue hq) {
    free(hq->command);
    free(hq);   
}


History_Queue hq_add(History_Queue hq, char *command) {
    History_Queue new_hq = hq_create(hq->max_size, hq->last->current_index + 1, command);

    if(hq->next != NULL) {
        hq->last->next = new_hq;
        hq->last = new_hq;
    } else {
        hq->next = new_hq;
        hq->last = new_hq;
    }

    // If we are overflowing and need to remove one
    if(new_hq->current_index - hq->current_index >= hq->max_size) {
        History_Queue new_head = hq->next;
        new_head->last = hq->last;
        
        hq_free_node(hq);
        return new_head;
    }

    // Still the same head
    return hq;
}

void hq_free_all(History_Queue hq) {
    History_Queue curr = hq;

    while(curr != NULL) {
        History_Queue next = curr->next;
        hq_free_node(curr);
        curr = next;
    }
}

void hq_print(History_Queue hq) {
    History_Queue curr = hq;

    while(curr != NULL) {
        History_Queue next = curr->next;
        printf("%lu: %s\n", curr->current_index, curr->command);
        curr = next;
    }
}

int test(void) {
    History_Queue hq = hq_create(5, 0, "Command1");
    hq_add(hq, "Command2");
    hq_add(hq, "Command3");
    hq_add(hq, "Command4");
    hq = hq_add(hq, "Command5");
    hq = hq_add(hq, "Command6");
    hq = hq_add(hq, "Command7");
    hq = hq_add(hq, "Command8");
    hq_print(hq);
    
        

    hq_free_all(hq);
}


