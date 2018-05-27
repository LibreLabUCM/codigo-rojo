#include <stdlib.h>
#include <stdio.h>

#include "core.h"
#include "instruction.h"
#include "program.h"

void codp_core_init(struct core *c, size_t m) {
    c->core = malloc(sizeof(*c->core)*m);
    c->m = m;
}

void codp_core_del(struct core *c) {
    free(c->core);
    c->m = 0;
}

void codp_core_free(struct core *c) {
    codp_core_del(c);
    free(c);
}

struct instruction *codp_core_get(struct core *c, addr_t addr) {
    return &c->core[addr % c->m];
}

void codp_core_put(struct core *c, addr_t addr, struct instruction ir) {
    c->core[addr % c->m] = ir;
}

void codp_core_load(struct core *c, addr_t at, struct program *prg) {
    for (addr_t i = 0; i < prg->len; i++) {
        if (prg->irs[i].a.number < 0)
            prg->irs[i].a.number = (prg->irs[i].a.number + c->m) % c->m;
        if (prg->irs[i].b.number < 0)
            prg->irs[i].b.number = (prg->irs[i].b.number + c->m) % c->m;
        codp_core_put(c, at + i, prg->irs[i]);
    }
}

void codp_core_print(struct core *core) {
    for (int i = 0; i < core->m; i++) {
        codp_print_instruction(core->core + i);
        printf("\n");
    }
}
