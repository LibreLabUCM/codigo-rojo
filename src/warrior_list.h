#ifndef WARRIOR_LIST_H
#define WARRIOR_LIST_H

#include <stdlib.h>

#include "queue.h"

struct warrior_list {
    struct queue *l;
    size_t n;
};

void warrior_list_init(struct warrior_list *l, size_t n);
void warrior_list_del(struct warrior_list *l);

#endif
