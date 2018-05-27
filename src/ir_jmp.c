#include "mars.h"
#include "core.h"
#include "instruction.h"
#include "queue.h"

void codp_ir_jmp(struct instruction ir, addr_t pc, struct core *core, struct queue *queue) {
    addr_t aptr = codp_mars_eval_operand(ir.a, pc, core);
    codp_queue_push_back(queue, (pc + aptr) % core->m);
}
