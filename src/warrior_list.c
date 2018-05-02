#include "warrior_list.h"

void warrior_list_init(struct warrior_list *l, size_t n) {
    l->l = malloc(sizeof(*l->l)*n);
    l->n = n;
    for (int i = 0; i < l->n; i++) {
        queue_init(&l->l[i]);
    }
}

void warrior_list_del(struct warrior_list *l) {
    for (int i = 0; i < l->n; i++) {
        queue_del(&l->l[i]);
    }
    free(l->l);
    l->n = 0;
}
