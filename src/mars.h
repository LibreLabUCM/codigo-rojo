#ifndef MARS_H
#define MARS_H

#include "instruction.h"
#include "queue.h"
#include "core.h"
#include "warrior_list.h"

void cycle_warrior(struct queue *queue, struct core *core);
void cycle(struct warrior_list *wlist, struct core *core);
addr_t eval_operand(struct operand op, addr_t pc, struct core *core);

#endif
