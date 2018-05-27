#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

#include "instruction.h"

struct queue {
    struct queue_node *front;
    struct queue_node *back;
    size_t len;
};

struct queue_node {
    addr_t addr;
    struct queue_node *prev;
};

void codp_queue_init(struct queue *q);
void codp_queue_del(struct queue *q);
void codp_queue_free(struct queue *q);
void codp_queue_push_back(struct queue *q, int addr);
addr_t codp_queue_pop_front(struct queue *q);

#endif
