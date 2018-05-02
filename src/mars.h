#ifndef MARS_H
#define MARS_H

typedef unsigned int addr_t;

enum opcode {
    DAT,
    MOV,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    JMP,
    //JMZ,
    //JMN,
    //DJN,
    CMP
    //SLT,
    //SPL
};

enum modifier {
    A,
    B,
    AB,
    BA,
    F,
    X,
    I
};

enum mode {
    IMMEDIATE,
    DIRECT,
    INDIRECT,
    DECREMENT,
    INCREMENT
};

struct operand {
    enum mode mode;
    addr_t number;
};

struct instruction {
    enum opcode opcode;
    enum modifier modifier;
    struct operand a;
    struct operand b;
};

#endif
