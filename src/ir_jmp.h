#ifndef IR_JMP_H
#define IR_JMP_H

#include "mars.h"
#include "core.h"

void ir_jmp(struct instruction ir, addr_t pc, struct core *core, struct queue *queue);

#endif
