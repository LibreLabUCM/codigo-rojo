#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "core.h"
#include "mars.h"

addr_t instruction_eval(struct operand op, addr_t pc, struct core *core);

#endif
