#ifndef MARS_H
#define MARS_H

#include "instruction.h"
#include "queue.h"
#include "core.h"

void cycle(struct queue *queue, struct core *core);
addr_t eval_operand(struct operand op, addr_t pc, struct core *core);

#endif
