#include <stdlib.h>
#include <stdio.h>

#include "core.h"
#include "instruction.h"

void core_init(struct core *c, size_t m) {
    c->core = malloc(sizeof(*c->core)*m);
    c->m = m;
}

void core_del(struct core *c) {
    free(c->core);
    c->m = 0;
}

void core_free(struct core *c) {
    core_del(c);
    free(c);
}

struct instruction *core_get(struct core *c, addr_t addr) {
    return &c->core[addr % c->m];
}

void core_put(struct core *c, addr_t addr, struct instruction ir) {
    c->core[addr % c->m] = ir;
}

void core_print(struct core *core) {
    for (int i = 0; i < core->m; i++) {
        print_instruction(core->core + i);
        printf("\n");
    }
}
