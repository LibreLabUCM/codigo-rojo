#include <stdio.h>

#include "instruction.h"

void codp_print_opcode(enum opcode code) {
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

void codp_print_modifier(enum modifier m) {
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

void codp_print_mode(enum mode m) {
    switch (m) {
    case IMMEDIATE: printf("#"); break;
    case DIRECT: printf("$"); break;
    case INDIRECT: printf("@"); break;
    case DECREMENT: printf("<"); break;
    case INCREMENT: printf(">"); break;
    }
}

void codp_print_instruction(struct instruction *ir) {
    codp_print_opcode(ir->opcode);
    printf(".");
    codp_print_modifier(ir->modifier);
    printf(" ");
    codp_print_mode(ir->a.mode);
    printf("%d", ir->a.number);
    printf(", ");
    codp_print_mode(ir->b.mode);
    printf("%d", ir->b.number);
}
