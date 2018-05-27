#include "mars.h"
#include "core.h"
#include "instruction.h"

void codp_ir_spl(struct instruction ir, addr_t pc, struct core *core, struct queue *queue) {
    addr_t aptr = codp_mars_eval_operand(ir.a, pc, core);
    codp_queue_push_back(queue, (pc + aptr) % core->m);
    codp_queue_push_back(queue, (pc + 1) % core->m);
}
