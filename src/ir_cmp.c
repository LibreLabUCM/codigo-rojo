#include <stdbool.h>

#include "mars.h"
#include "core.h"
#include "instruction.h"
#include "queue.h"

void codp_ir_cmp(struct instruction ir, addr_t pc, struct core *core, struct queue *queue) {
    addr_t aptr = codp_mars_eval_operand(ir.a, pc, core);
    struct instruction air = *codp_core_get(core, pc + aptr);
    addr_t bptr = codp_mars_eval_operand(ir.b, pc, core);
    struct instruction bir = *codp_core_get(core, pc + bptr);
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
        codp_queue_push_back(queue, (pc + 2) % core->m);
    else
        codp_queue_push_back(queue, (pc + 1) % core->m);
}
