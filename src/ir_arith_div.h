#ifndef IR_ARITH_DIV_H
#define IR_ARITH_DIV_H

#include "mars.h"
#include "core.h"
#include "queue.h"

void copd_ir_div(struct instruction ir, addr_t pc, struct core *core, struct queue *queue);
void copd_ir_mod(struct instruction ir, addr_t pc, struct core *core, struct queue *queue);

#endif
