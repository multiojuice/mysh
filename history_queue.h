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








#endif
