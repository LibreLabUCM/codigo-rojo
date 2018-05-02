#include "mars.h"
#include "core.h"
#include "instruction.h"

void ir_mov(struct instruction ir, addr_t pc, struct core *core, struct queue *queue) {
    addr_t aptr = instruction_eval(ir.a, pc, core);
    struct instruction air = *core_get(core, pc + aptr);
    addr_t bptr = instruction_eval(ir.b, pc, core);
    struct instruction bir = *core_get(core, pc + bptr);
    switch (ir.modifier) {
    case A:
        core_get(core, pc + bptr)->a.number = air.a.number;
        break;
    case B:
        core_get(core, pc + bptr)->a.number = air.b.number;
        break;
    case AB:
        core_get(core, pc + bptr)->b.number = air.a.number;
        break;
    case BA:
        core_get(core, pc + bptr)->a.number = air.b.number;
        break;
    case F:
        core_get(core, pc + bptr)->a.number = air.a.number;
        core_get(core, pc + bptr)->b.number = air.b.number;
        break;
    case X:
        core_get(core, pc + bptr)->b.number = air.a.number;
        core_get(core, pc + bptr)->a.number = air.b.number;
        break;
    case I:
        *core_get(core, pc + bptr) = air;
        break;
    }
    queue_push_back(queue, (pc + 1) % core->m);
}
