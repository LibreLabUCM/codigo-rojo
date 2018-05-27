#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdbool.h>

#include "instruction.h"

struct program {
    struct instruction *irs;
    int len;
    int capacity;
};

void codp_program_init(struct program *prg);
void codp_program_del(struct program *prg);
void codp_program_free(struct program *prg);
void codp_program_push(struct program *prg, struct instruction *new);
bool codp_program_read(struct program *prg, const char *filename);

#endif
