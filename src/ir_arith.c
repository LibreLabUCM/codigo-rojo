#include "mars.h"
#include "core.h"
#include "instruction.h"
#include "queue.h"

#define ARITH(op)                                                       \
    addr_t aptr = codp_mars_eval_operand(ir.a, pc, core);               \
    struct instruction *air = codp_core_get(core, pc + aptr);           \
    addr_t bptr = codp_mars_eval_operand(ir.b, pc, core);               \
    struct instruction *bir = codp_core_get(core, pc + bptr);           \
    switch (ir.modifier) {                                              \
    case A:                                                             \
        bir->a.number = (bir->a.number op air->a.number) % core->m;     \
        break;                                                          \
    case B:                                                             \
        bir->b.number = (bir->b.number op air->b.number) % core->m;     \
        break;                                                          \
    case AB:                                                            \
        bir->b.number = (bir->b.number op air->a.number) % core->m;     \
        break;                                                          \
    case BA:                                                            \
        bir->a.number = (bir->a.number op air->b.number) % core->m;     \
        break;                                                          \
    case F:                                                             \
    case I:                                                             \
        bir->b.number = (bir->a.number op air->a.number) % core->m;     \
        bir->a.number = (bir->b.number op air->b.number) % core->m;     \
        break;                                                          \
    case X:                                                             \
        bir->b.number = (bir->a.number op air->b.number) % core->m;     \
        bir->a.number = (bir->b.number op air->a.number) % core->m;     \
        break;                                                          \
    }                                                                   \
    codp_queue_push_back(queue, (pc + 1) % core->m);

void codp_ir_add(struct instruction ir, addr_t pc, struct core *core, struct queue *queue) {
    ARITH(+)
}

void codp_ir_sub(struct instruction ir, addr_t pc, struct core *core, struct queue *queue) {
    ARITH(+ core->m -)
}

void codp_ir_mul(struct instruction ir, addr_t pc, struct core *core, struct queue *queue) {
    ARITH(*)
}
