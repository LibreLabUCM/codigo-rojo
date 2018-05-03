#ifndef MARS_H
#define MARS_H

#include "instruction.h"
#include "queue.h"
#include "core.h"
#include "warrior_list.h"

struct mars {
    struct core *core;
    struct warrior_list *wlist;
};

void mars_init(struct mars *mars, size_t warriors, size_t core_size);
void mars_del(struct mars *mars);
void mars_free(struct mars *mars);

void cycle(struct mars *mars);
addr_t eval_operand(struct operand op, addr_t pc, struct core *core);

#endif
