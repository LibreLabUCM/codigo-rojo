#include "mars.h"
#include "core.h"
#include "instruction.h"
#include "queue.h"

#define ARITH(op)                                                   \
    addr_t aptr = eval_operand(ir.a, pc, core);                     \
    struct instruction *air = core_get(core, pc + aptr);            \
    addr_t bptr = eval_operand(ir.b, pc, core);                     \
    struct instruction *bir = core_get(core, pc + bptr);            \
    switch (ir.modifier) {                                          \
    case A:                                                         \
        bir->a.number = (bir->a.number op air->a.number) % core->m; \
        break;                                                      \
    case B:                                                         \
        bir->b.number = (bir->b.number op air->b.number) % core->m; \
        break;                                                      \
    case AB:                                                        \
        bir->b.number = (bir->b.number op air->a.number) % core->m; \
        break;                                                      \
    case BA:                                                        \
        bir->a.number = (bir->a.number op air->b.number) % core->m; \
        break;                                                      \
    case F:                                                         \
    case I:                                                         \
        bir->b.number = (bir->a.number op air->a.number) % core->m; \
        bir->a.number = (bir->b.number op air->b.number) % core->m; \
        break;                                                      \
    case X:                                                         \
        bir->b.number = (bir->a.number op air->b.number) % core->m; \
        bir->a.number = (bir->b.number op air->a.number) % core->m; \
        break;                                                      \
    }                                                               \
    queue_push_back(queue, (pc + 1) % core->m);

void ir_add(struct instruction ir, addr_t pc, struct core *core, struct queue *queue) {
    ARITH(+)
}

void ir_sub(struct instruction ir, addr_t pc, struct core *core, struct queue *queue) {
    ARITH(+ core->m -)
}

void ir_mul(struct instruction ir, addr_t pc, struct core *core, struct queue *queue) {
    ARITH(*)
}
