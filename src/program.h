#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdbool.h>

#include "instruction.h"

struct program {
    struct instruction *irs;
    int len;
    int capacity;
};

void program_init(struct program *prg);
void program_del(struct program *prg);
void program_free(struct program *prg);
void program_push(struct program *prg, struct instruction *new);
bool program_read(struct program *prg, const char *filename);

#endif
