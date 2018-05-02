#ifndef IR_ARITH_H
#define IR_ARITH_H

#include "mars.h"
#include "core.h"
#include "queue.h"

void ir_add(struct instruction ir, addr_t pc, struct core *core, struct queue *queue);
void ir_sub(struct instruction ir, addr_t pc, struct core *core, struct queue *queue);
void ir_mul(struct instruction ir, addr_t pc, struct core *core, struct queue *queue);

#endif
