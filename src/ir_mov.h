#ifndef IR_MOV_H
#define IR_MOV_H

#include "mars.h"
#include "core.h"

void codp_ir_mov(struct instruction ir, addr_t pc, struct core *core, struct queue *queue);

#endif
