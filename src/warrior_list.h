#ifndef WARRIOR_LIST_H
#define WARRIOR_LIST_H

#include <stdlib.h>

#include "queue.h"

struct warrior_list {
    struct queue *l;
    size_t w;  // current warrior
    size_t nwrs;  // number of warriors
};

void codp_warrior_list_init(struct warrior_list *l, size_t n);
void codp_warrior_list_del(struct warrior_list *l);
void codp_warrior_list_free(struct warrior_list *l);
struct queue *codp_next_warrior(struct warrior_list *l);

#endif
