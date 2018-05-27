#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "program.h"
#include "parse.h"

#define STEP 50

void program_init(struct program *prg) {
    prg->irs = malloc(sizeof(*prg->irs)*STEP);
    prg->len = 0;
    prg->capacity = STEP;
}

void program_del(struct program *prg) {
    free(prg->irs);
    prg->len = 0;
    prg->capacity = 0;
}

void program_free(struct program *prg) {
    program_del(prg);
    free(prg);
}

void program_resize(struct program *prg) {
    struct instruction *new = malloc(sizeof(*new) * (prg->capacity + STEP));
    for (int i = 0; i < prg->len; i++) {
        new[i] = prg->irs[i];
    }
    free(prg->irs);
    prg->irs = new;
    prg->capacity += STEP;
}

void program_push(struct program *prg, struct instruction *new) {
    if (prg->len == prg->capacity)
        program_resize(prg);
    prg->irs[prg->len] = *new;
    prg->len++;
}

bool program_read(struct program *prg, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        char *str = malloc(sizeof(char)*200);
        while (!feof(file)) {
            char *line = fgets(str, 200, file);
            if (line == NULL)
                return true;
            struct instruction ir;
            if (codp_parse_instruction(line, &ir) == NULL)
                return false;
            program_push(prg, &ir);
        }
        free(str);
        return true;
    } else {
        return false;
    }
}
