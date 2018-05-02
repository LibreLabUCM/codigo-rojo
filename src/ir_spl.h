#ifndef IR_SPL_H
#define IR_SPL_H

#include "instruction.h"
#include "core.h"

void ir_spl(struct instruction ir, addr_t pc, struct core *core, struct queue *queue);

#endif
