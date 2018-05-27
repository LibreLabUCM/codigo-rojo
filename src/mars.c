#include "instruction.h"
#include "queue.h"
#include "core.h"
#include "ir_mov.h"
#include "ir_arith.h"
#include "ir_arith_div.h"
#include "ir_jmp.h"
#include "ir_cmp.h"
#include "ir_spl.h"

void codp_mars_init(struct mars *mars, size_t core_size, size_t warriors) {
    mars->core = malloc(sizeof(mars->core));
    codp_core_init(mars->core, core_size);
    mars->wlist = malloc(sizeof(mars->wlist));
    codp_warrior_list_init(mars->wlist, warriors);
}

void codp_mars_del(struct mars *mars) {
    codp_warrior_list_free(mars->wlist);
    codp_core_free(mars->core);
}

void codp_mars_free(struct mars *mars) {
    codp_mars_del(mars);
    free(mars);
}

static void cycle_warrior(struct queue *queue, struct core *core) {
    addr_t pc = codp_queue_pop_front(queue);
    struct instruction ir = *codp_core_get(core, pc);
    switch (ir.opcode) {
    case DAT: break;
    case MOV: codp_ir_mov(ir, pc, core, queue); break;
    case ADD: codp_ir_add(ir, pc, core, queue); break;
    case SUB: codp_ir_sub(ir, pc, core, queue); break;
    case MUL: codp_ir_mul(ir, pc, core, queue); break;
    case DIV: codp_ir_div(ir, pc, core, queue); break;
    case MOD: codp_ir_mod(ir, pc, core, queue); break;
    case JMP: codp_ir_jmp(ir, pc, core, queue); break;
    case CMP: codp_ir_cmp(ir, pc, core, queue); break;
    case SPL: codp_ir_spl(ir, pc, core, queue); break;
    }
}

void codp_mars_cycle(struct mars *mars) {
    cycle_warrior(codp_next_warrior(mars->wlist), mars->core);
}

addr_t codp_mars_eval_operand(struct operand op, addr_t pc, struct core *core) {
    addr_t res;
    switch (op.mode) {
    case IMMEDIATE:
        res = 0;
        break;
    case DIRECT:
        res = op.number;
        break;
    case INDIRECT:
        res = op.number + codp_core_get(core, pc + op.number)->b.number;
        break;
    case DECREMENT:
        res = op.number + codp_core_get(core, pc + op.number)->b.number + core->m - 1;
        break;
    case INCREMENT:
        break;
    }
    return res;
}

int codp_mars_game_winner(struct mars *mars) {
    int counter = 0;
    int winner = -1;
    for (int i = 0; i < mars->wlist->nwrs; i++) {
        if (mars->wlist->l[i].len != 0) {
            counter++;
            winner = i;
        }
    }
    if (counter == 1) {
        return winner;
    } else {
        return -1;
    }
}
