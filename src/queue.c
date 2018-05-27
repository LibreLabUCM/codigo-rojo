#include <stdlib.h>
#include "queue.h"

void codp_queue_init(struct queue *q) {
    q->front = NULL;
    q->back = NULL;
    q->len = 0;
}

static void codp_queue_free_nodes(struct queue_node *n) {
    if (n != NULL) {
        codp_queue_free_nodes(n->prev);
        free(n);
    }
}

void codp_queue_del(struct queue *q) {
    codp_queue_free_nodes(q->front);
}

void codp_queue_free(struct queue *q) {
    codp_queue_del(q);
    free(q);
}

void codp_queue_push_back(struct queue *q, int addr) {
    struct queue_node *new_back = malloc(sizeof(*new_back));
    new_back->addr = addr;
    new_back->prev = NULL;
    if (q->back == NULL) {
        q->back = new_back;
    } else {
        q->back->prev = new_back;
    }
    if (q->front == NULL) {
        q->front = new_back;
    }
    ++q->len;
}

addr_t codp_queue_pop_front(struct queue *q) {
    if (q->len <= 0) {
        return -1;
    }
    struct queue_node *front = q->front;
    q->front = front->prev;
    if (q->front == NULL) {
        q->back = NULL;
    }
    int addr = front->addr;
    free(front);
    --q->len;
    return addr;
}
