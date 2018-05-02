#include <stdio.h>

#include "queue.h"
#include "core.h"
#include "mars.h"

#define CYCLES 3
#define PLAYERS 2
#define CORESIZE 7*PLAYERS // 14


void print_core(struct core *core) {
    for (int j = 0; j < core->m; j++) {
        struct instruction ir = *core_get(core, j);
        printf("%d %d %d %d %d %d\n",
               ir.opcode, ir.modifier, ir.a.mode, ir.a.number, ir.b.mode, ir.b.number);
    }
}

int main() {
    struct core *core = malloc(sizeof(*core));
    core_init(core, CORESIZE);

    for (int i = 0; i < core->m; i++) {
        core->core[i] = (struct instruction) {
            .opcode = DAT,
            .modifier = F,
            .a = { .mode = IMMEDIATE, .number = 0 },
            .b = { .mode = IMMEDIATE, .number = 0 }
        };
    }

    struct queue *playerQueues[PLAYERS];
    for(int i = 0; i < PLAYERS; i++) {
        core->core[CORESIZE/PLAYERS*i] = (struct instruction) {
            .opcode = MOV,
            .modifier = I,
            .a = { .mode = DIRECT, .number = 0 },
            .b = { .mode = DIRECT, .number = 1 }
        };
        playerQueues[i] = malloc(sizeof(struct queue));
        queue_init(playerQueues[i]);
        queue_push_back(playerQueues[i], CORESIZE/PLAYERS*i);
    }

    print_core(core);
    printf("\n");
    for (int i = 0; i < CYCLES*PLAYERS; i++) {
        cycle(playerQueues[i%PLAYERS], core);
        print_core(core);
        printf("\n");
    }

    for(int i = 0; i < PLAYERS; i++) {
        queue_del(playerQueues[i]);
    }
    core_del(core);
}
