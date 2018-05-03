#ifndef CORE_H
#define CORE_H

#include <stdlib.h>

#include "instruction.h"

struct core {
    struct instruction *core;
    size_t m;
};

void core_init(struct core *c, size_t m);
void core_del(struct core *c);
void core_free(struct core *c);
struct instruction *core_get(struct core *c, addr_t addr);
void core_put(struct core *c, addr_t addr, struct instruction ir);

#endif
