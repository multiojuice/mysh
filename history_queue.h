#include <stdlib.h>

#ifndef HISTORY_QUEUE
#define HISTORY_QUEUE

struct History_Queue_S {
    size_t max_size;
    size_t current_index;
    char *command;
    struct History_Queue_S *next;
    struct History_Queue_S *last;
};

typedef struct History_Queue_S *History_Queue;

History_Queue hq_create(size_t max_size, size_t current_index, char *command);

History_Queue hq_add(History_Queue hq, char *command);

void hq_free_all(History_Queue hq);

void hq_print(History_Queue hq);






#endif
