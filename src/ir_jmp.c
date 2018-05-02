#include "mars.h"
#include "core.h"
#include "instruction.h"

void ir_jmp(struct instruction ir, addr_t pc, struct core *core, struct queue *queue) {
    addr_t aptr = instruction_eval(ir.a, pc, core);
    queue_push_back(queue, (pc + aptr) % core->m);
}
