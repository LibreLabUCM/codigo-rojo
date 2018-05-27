#include <stdbool.h>

#include "mars.h"
#include "core.h"
#include "instruction.h"
#include "queue.h"

#define ARITH_DIV(op)                                                   \
    addr_t aptr = codp_mars_eval_operand(ir.a, pc, core);               \
    struct instruction *air = codp_core_get(core, pc + aptr);           \
    addr_t bptr = codp_mars_eval_operand(ir.b, pc, core);               \
    struct instruction *bir = codp_core_get(core, pc + bptr);           \
    bool noqueue = false;                                               \
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
        if (air->a.number != 0)                                         \
            bir->b.number = (bir->a.number op air->a.number) % core->m; \
        if (air->b.number != 0)                                         \
            bir->a.number = (bir->b.number op air->b.number) % core->m; \
        if (air->a.number != 0 || air->b.number != 0)                   \
            noqueue = true;                                             \
        break;                                                          \
    case X:                                                             \
        if (air->b.number != 0)                                         \
            bir->b.number = (bir->a.number op air->b.number) % core->m; \
        if (air->a.number != 0)                                         \
            bir->a.number = (bir->b.number op air->a.number) % core->m; \
        if (air->b.number != 0 || air->a.number != 0)                   \
            noqueue = true;                                             \
        break;                                                          \
    }                                                                   \
    if (!noqueue)                                                       \
        codp_queue_push_back(queue, (pc + 1) % core->m);

void codp_ir_div(struct instruction ir, addr_t pc, struct core *core, struct queue *queue) {
    ARITH_DIV(/)
}

void codp_ir_mod(struct instruction ir, addr_t pc, struct core *core, struct queue *queue) {
    ARITH_DIV(%)
}
