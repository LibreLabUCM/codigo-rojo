#include "instruction.h"
#include "mars.h"
#include "core.h"

addr_t instruction_eval(struct operand op, addr_t pc, struct core *core) {
    addr_t res;
    switch (op.mode) {
    case IMMEDIATE:
        res = 0;
        break;
    case DIRECT:
        res = op.number;
        break;
    case INDIRECT:
        res = op.number + core_get(core, pc + op.number)->b.number;
        break;
    case DECREMENT:
        res = op.number + core_get(core, pc + op.number)->b.number + core->m - 1;
        break;
    case INCREMENT:
        break;
    }
    return res;
}
