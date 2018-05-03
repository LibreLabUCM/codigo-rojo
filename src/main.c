#include <stdio.h>

#include "queue.h"
#include "core.h"
#include "mars.h"

#define CYCLES 3
#define WARRIORS 2
#define CORESIZE 7*WARRIORS // 14

int main() {
    struct mars mars;
    mars_init(&mars, CORESIZE, WARRIORS);

    for (int i = 0; i < mars.core->m; i++) {
        mars.core->core[i] = (struct instruction) {
            .opcode = DAT,
            .modifier = F,
            .a = { .mode = IMMEDIATE, .number = 0 },
            .b = { .mode = IMMEDIATE, .number = 0 }
        };
    }

    for(int i = 0; i < mars.wlist->nwrs; i++) {
        mars.core->core[CORESIZE/WARRIORS*i] = (struct instruction) {
            .opcode = MOV,
            .modifier = I,
            .a = { .mode = DIRECT, .number = 0 },
            .b = { .mode = DIRECT, .number = 1 }
        };
        queue_push_back(&mars.wlist->l[i], CORESIZE/WARRIORS*i);
    }

    core_print(mars.core);
    printf("\n");
    for (int i = 0; i < CYCLES*WARRIORS; i++) {
        cycle(&mars);
        core_print(mars.core);
        printf("\n");
    }

    mars_del(&mars);
}
