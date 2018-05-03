#include "instruction.h"
#include "queue.h"
#include "core.h"
#include "ir_mov.h"
#include "ir_arith.h"
#include "ir_arith_div.h"
#include "ir_jmp.h"
#include "ir_cmp.h"
#include "ir_spl.h"

void mars_init(struct mars *mars, size_t core_size, size_t warriors) {
    mars->core = malloc(sizeof(mars->core));
    core_init(mars->core, core_size);
    mars->wlist = malloc(sizeof(mars->wlist));
    warrior_list_init(mars->wlist, warriors);
}

void mars_del(struct mars *mars) {
    warrior_list_free(mars->wlist);
    core_free(mars->core);
}

void mars_free(struct mars *mars) {
    mars_del(mars);
    free(mars);
}

void cycle_warrior(struct queue *queue, struct core *core) {
    addr_t pc = queue_pop_front(queue);
    struct instruction ir = *core_get(core, pc);
    switch (ir.opcode) {
    case DAT: break;
    case MOV: ir_mov(ir, pc, core, queue); break;
    case ADD: ir_add(ir, pc, core, queue); break;
    case SUB: ir_sub(ir, pc, core, queue); break;
    case MUL: ir_mul(ir, pc, core, queue); break;
    case DIV: ir_div(ir, pc, core, queue); break;
    case MOD: ir_mod(ir, pc, core, queue); break;
    case JMP: ir_jmp(ir, pc, core, queue); break;
    case CMP: ir_cmp(ir, pc, core, queue); break;
    case SPL: ir_spl(ir, pc, core, queue); break;
    }
}

void cycle(struct warrior_list *wlist, struct core *core) {
    cycle_warrior(next_warrior(wlist), core);
}

addr_t eval_operand(struct operand op, addr_t pc, struct core *core) {
    addr_t res;
    switch (op.mode) {
    case IMMEDIATE:
        res = 0;
        break;
    case DIRECT:
        res = op.number;
        break;
    case INDIRECT:
        res = op.number + core_get(core, pc + op.number)->b.number;
        break;
    case DECREMENT:
        res = op.number + core_get(core, pc + op.number)->b.number + core->m - 1;
        break;
    case INCREMENT:
        break;
    }
    return res;
}
