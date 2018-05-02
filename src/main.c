#include <stdio.h>

#include "queue.h"
#include "core.h"
#include "mars.h"

int main() {
    struct core *core = malloc(sizeof(*core));
    core_init(core, 10);
    core->core[0] = (struct instruction) {
        .opcode = MOV,
        .modifier = I,
        .a = { .mode = DIRECT, .number = 0 },
        .b = { .mode = DIRECT, .number = 1 }
    };
    for (int i = 1; i < core->m; i++) {
        core->core[i] = (struct instruction) {
            .opcode = DAT,
            .modifier = F,
            .a = { .mode = IMMEDIATE, .number = 0 },
            .b = { .mode = IMMEDIATE, .number = 0 }
        };
    }

    struct queue *queue = malloc(sizeof(struct queue));
    queue_init(queue);
    queue_push_back(queue, 0);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < core->m; j++) {
            struct instruction ir = *core_get(core, j);
            printf("%d %d %d %d %d %d\n",
                   ir.opcode, ir.modifier, ir.a.mode, ir.a.number, ir.b.mode, ir.b.number);
        }
        printf("\n");
        cycle(queue, core);
    }

    queue_del(queue);
    core_del(core);
}

