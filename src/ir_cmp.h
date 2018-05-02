#ifndef IR_CMP_H
#define IR_CMP_H

#include "mars.h"
#include "core.h"

void ir_cmp(struct instruction ir, addr_t pc, struct core *core, struct queue *queue);

#endif
