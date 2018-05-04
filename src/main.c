#include <stdio.h>

#include "queue.h"
#include "core.h"
#include "mars.h"

#define CYCLES 3
#define WARRIORS 2
#define CORESIZE 35

int main() {
    struct mars mars;
    mars_init(&mars, CORESIZE, WARRIORS);

    for (int i = 0; i < mars.core->m; i++) {
        mars.core->core[i] = (struct instruction) {
            .opcode = DAT,
            .modifier = F,
            .a = { .mode = IMMEDIATE, .number = 1 },
            .b = { .mode = IMMEDIATE, .number = 1 }
        };
    }

    // WARRIOR 1
    mars.core->core[0] = (struct instruction) {
        .opcode = ADD,
        .modifier = AB,
        .a = { .mode = IMMEDIATE, .number = 4 },
        .b = { .mode = DIRECT, .number = 3 }
    };
    mars.core->core[1] = (struct instruction) {
        .opcode = MOV,
        .modifier = I,
        .a = { .mode = DIRECT, .number = 2 },
        .b = { .mode = INDIRECT, .number = 2 }
    };
    mars.core->core[2] = (struct instruction) {
        .opcode = JMP,
        .modifier = B,
        .a = { .mode = DIRECT, .number = CORESIZE - 2 },
        .b = { .mode = DIRECT, .number = 1 }
    };
    mars.core->core[3] = (struct instruction) {
        .opcode = DAT,
        .modifier = F,
        .a = { .mode = IMMEDIATE, .number = 0 },
        .b = { .mode = IMMEDIATE, .number = 0 }
    };
    queue_push_back(&mars.wlist->l[0], 0);

    // WARRIOR 2
    mars.core->core[7] = (struct instruction) {
        .opcode = MOV,
        .modifier = I,
        .a = { .mode = DIRECT, .number = 0 },
        .b = { .mode = DIRECT, .number = 1 }
    };
    queue_push_back(&mars.wlist->l[1], 7);

    core_print(mars.core);
    printf("\n");
    for (int i = 0; i < CYCLES*WARRIORS; i++) {
        cycle(&mars);
        core_print(mars.core);
        printf("\n");
    }

    mars_del(&mars);
}
