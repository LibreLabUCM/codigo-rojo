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

void codp_mars_init(struct mars *mars, size_t warriors, size_t core_size);
void codp_mars_del(struct mars *mars);
void codp_mars_free(struct mars *mars);

void codp_mars_cycle(struct mars *mars);
int codp_mars_game_winner(struct mars *mars);
addr_t codp_mars_eval_operand(struct operand op, addr_t pc, struct core *core);

#endif
