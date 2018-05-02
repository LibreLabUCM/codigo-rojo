#include <stdbool.h>

#include "mars.h"
#include "core.h"
#include "instruction.h"
#include "queue.h"

#define ARITH_DIV(op)                                     \
    addr_t aptr = eval_operand(ir.a, pc, core);           \
    struct instruction air = *core_get(core, aptr);       \
    addr_t bptr = eval_operand(ir.b, pc, core);           \
    struct instruction bir = *core_get(core, bptr);       \
    bool noqueue = false;                                 \
    switch (ir.modifier) {                                \
    case A:                                               \
        core_get(core, pc + bptr)->a.number =             \
            (bir.a.number op air.a.number) % core->m;     \
        break;                                            \
    case B:                                               \
        core_get(core, pc + bptr)->b.number =             \
            (bir.b.number op air.b.number) % core->m;     \
        break;                                            \
    case AB:                                              \
        core_get(core, pc + bptr)->b.number =             \
            (bir.b.number op air.a.number) % core->m;     \
        break;                                            \
    case BA:                                              \
        core_get(core, pc + bptr)->a.number =             \
            (bir.a.number op air.b.number) % core->m;     \
        break;                                            \
    case F:                                               \
    case I:                                               \
        if (air.a.number != 0)                            \
            core_get(core, pc + bptr)->b.number =         \
                (bir.a.number op air.a.number) % core->m; \
        if (air.b.number != 0)                            \
            core_get(core, pc + bptr)->a.number =         \
                (bir.b.number op air.b.number) % core->m; \
        if (air.a.number != 0 || air.b.number != 0)       \
            noqueue = true;                               \
        break;                                            \
    case X:                                               \
        if (air.b.number != 0)                            \
            core_get(core, pc + bptr)->b.number =         \
                (bir.a.number op air.b.number) % core->m; \
        if (air.a.number != 0)                            \
            core_get(core, pc + bptr)->a.number =         \
                (bir.b.number op air.a.number) % core->m; \
        if (air.b.number != 0 || air.a.number != 0)       \
            noqueue = true;                               \
        break;                                            \
    };                                                    \
    if (!noqueue)                                         \
        queue_push_back(queue, (pc + 1) % core->m);

void ir_div(struct instruction ir, addr_t pc, struct core *core, struct queue *queue) {
    ARITH_DIV(/)
}

void ir_mod(struct instruction ir, addr_t pc, struct core *core, struct queue *queue) {
    ARITH_DIV(%)
}
