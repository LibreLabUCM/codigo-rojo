#include "warrior_list.h"

void codp_warrior_list_init(struct warrior_list *l, size_t n) {
    l->l = malloc(sizeof(*l->l)*n);
    l->w = 0;
    l->nwrs = n;
    for (int i = 0; i < l->nwrs; i++) {
        codp_queue_init(&l->l[i]);
    }
}

void codp_warrior_list_del(struct warrior_list *l) {
    for (int i = 0; i < l->nwrs; i++) {
        codp_queue_del(&l->l[i]);
    }
    free(l->l);
    l->nwrs = 0;
}

void codp_warrior_list_free(struct warrior_list *l) {
    codp_warrior_list_del(l);
    free(l);
}

struct queue *codp_next_warrior(struct warrior_list *l) {
    struct queue *next = &l->l[l->w];
    l->w = (l->w + 1) % l->nwrs;
    return next;
}
