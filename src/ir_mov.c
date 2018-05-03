#include "mars.h"
#include "core.h"
#include "instruction.h"
#include "queue.h"

void ir_mov(struct instruction ir, addr_t pc, struct core *core, struct queue *queue) {
    addr_t aptr = eval_operand(ir.a, pc, core);
    struct instruction *air = core_get(core, pc + aptr);
    addr_t bptr = eval_operand(ir.b, pc, core);
    struct instruction *bir = core_get(core, pc + bptr);
    switch (ir.modifier) {
    case A:
        bir->a.number = air->a.number;
        break;
    case B:
        bir->a.number = air->b.number;
        break;
    case AB:
        bir->b.number = air->a.number;
        break;
    case BA:
        bir->a.number = air->b.number;
        break;
    case F:
        bir->a.number = air->a.number;
        bir->b.number = air->b.number;
        break;
    case X:
        bir->b.number = air->a.number;
        bir->a.number = air->b.number;
        break;
    case I:
        *bir = *air;
        break;
    }
    queue_push_back(queue, (pc + 1) % core->m);
}
