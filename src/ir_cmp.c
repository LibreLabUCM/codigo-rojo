#include <stdbool.h>

#include "mars.h"
#include "core.h"
#include "instruction.h"
#include "queue.h"

void ir_cmp(struct instruction ir, addr_t pc, struct core *core, struct queue *queue) {
    addr_t aptr = instruction_eval(ir.a, pc, core);
    struct instruction air = *core_get(core, aptr);
    addr_t bptr = instruction_eval(ir.b, pc, core);
    struct instruction bir = *core_get(core, bptr);
    bool jump;
    switch (ir.modifier) {
    case A: jump = air.a.number == bir.a.number; break;
    case B: jump = air.b.number == bir.b.number; break;
    case AB: jump = air.a.number == bir.b.number; break;
    case BA: jump = air.b.number == bir.a.number; break;
    case F: jump = air.a.number == bir.a.number && air.b.number == bir.b.number; break;
    case X: jump = air.a.number == bir.b.number && air.b.number == bir.a.number; break;
    case I:
        jump =
            air.opcode == bir.opcode
            && air.modifier == air.modifier
            && air.a.mode == bir.a.mode
            && air.a.number == bir.a.number
            && air.b.mode == bir.b.mode
            && air.b.number == bir.b.number;
        break;
    }
    if (jump)
        queue_push_back(queue, (pc + 2) % core->m);
    else
        queue_push_back(queue, (pc + 1) % core->m);
}
