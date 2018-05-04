#include <stdlib.h>
#include <stdio.h>

#include "core.h"
#include "instruction.h"

void core_init(struct core *c, size_t m) {
    c->core = malloc(sizeof(*c->core)*m);
    c->m = m;
}

void core_del(struct core *c) {
    free(c->core);
    c->m = 0;
}

void core_free(struct core *c) {
    core_del(c);
    free(c);
}

struct instruction *core_get(struct core *c, addr_t addr) {
    return &c->core[addr % c->m];
}

void core_put(struct core *c, addr_t addr, struct instruction ir) {
    c->core[addr % c->m] = ir;
}

static void print_opcode(enum opcode code) {
    switch (code) {
    case DAT: printf("DAT"); break;
    case MOV: printf("MOV"); break;
    case ADD: printf("ADD"); break;
    case SUB: printf("SUB"); break;
    case MUL: printf("MUL"); break;
    case DIV: printf("DIV"); break;
    case MOD: printf("MOD"); break;
    case JMP: printf("JMP"); break;
    //case JMZ: printf("JMZ"); break;
    //case JMN: printf("JMN"); break;
    //case DJN: printf("DJN"); break;
    case CMP: printf("CMP"); break;
    //case SLT: printf("SLT"); break;
    case SPL: printf("SPL"); break;
    }
}

static void print_modifier(enum modifier m) {
    switch (m) {
    case A: printf("A"); break;
    case B: printf("B"); break;
    case AB: printf("AB"); break;
    case BA: printf("BA"); break;
    case F: printf("F"); break;
    case X: printf("X"); break;
    case I: printf("I"); break;
    }
}

static void print_mode(enum mode m) {
    switch (m) {
    case IMMEDIATE: printf("#"); break;
    case DIRECT: printf("$"); break;
    case INDIRECT: printf("@"); break;
    case DECREMENT: printf("<"); break;
    case INCREMENT: printf(">"); break;
    }
}

void core_print(struct core *core) {
    for (int j = 0; j < core->m; j++) {
        struct instruction ir = *core_get(core, j);
        print_opcode(ir.opcode);
        printf(".");
        print_modifier(ir.modifier);
        printf(" ");
        print_mode(ir.a.mode);
        printf("%d", ir.a.number);
        printf(" ");
        print_mode(ir.b.mode);
        printf("%d\n", ir.b.number);
    }
}
