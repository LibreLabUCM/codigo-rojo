#include "mars.h"
#include "core.h"
#include "instruction.h"
#include "queue.h"

#define ARITH(op)                                     \
    addr_t aptr = instruction_eval(ir.a, pc, core);   \
    struct instruction air = *core_get(core, aptr);   \
    addr_t bptr = instruction_eval(ir.b, pc, core);   \
    struct instruction bir = *core_get(core, bptr);   \
    switch (ir.modifier) {                            \
    case A:                                           \
        core_get(core, pc + bptr)->a.number =         \
            (bir.a.number op air.a.number) % core->m; \
        break;                                        \
    case B:                                           \
        core_get(core, pc + bptr)->b.number =         \
            (bir.b.number op air.b.number) % core->m; \
        break;                                        \
    case AB:                                          \
        core_get(core, pc + bptr)->b.number =         \
            (bir.b.number op air.a.number) % core->m; \
        break;                                        \
    case BA:                                          \
        core_get(core, pc + bptr)->a.number =         \
            (bir.a.number op air.b.number) % core->m; \
        break;                                        \
    case F:                                           \
    case I:                                           \
        core_get(core, pc + bptr)->b.number =         \
            (bir.a.number op air.a.number) % core->m; \
        core_get(core, pc + bptr)->a.number =         \
            (bir.b.number op air.b.number) % core->m; \
        break;                                        \
    case X:                                           \
        core_get(core, pc + bptr)->b.number =         \
            (bir.a.number op air.b.number) % core->m; \
        core_get(core, pc + bptr)->a.number =         \
            (bir.b.number op air.a.number) % core->m; \
        break;                                        \
    };                                                \
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
