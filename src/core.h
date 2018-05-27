#ifndef CORE_H
#define CORE_H

#include <stdlib.h>

#include "instruction.h"
#include "program.h"

struct core {
    struct instruction *core;
    size_t m;
};

void codp_core_init(struct core *c, size_t m);
void codp_core_del(struct core *c);
void codp_core_free(struct core *c);
struct instruction *codp_core_get(struct core *c, addr_t addr);
void codp_core_put(struct core *c, addr_t addr, struct instruction ir);
void codp_core_load(struct core *c, addr_t at, struct program *prg);
void codp_core_print(struct core *core);

#endif
