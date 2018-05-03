#include <stdio.h>

#include "queue.h"
#include "core.h"
#include "mars.h"

#define CYCLES 3
#define WARRIORS 2
#define CORESIZE 7*WARRIORS // 14

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

    struct warrior_list *wlist = malloc(sizeof(*wlist));
    warrior_list_init(wlist, WARRIORS);
    for(int i = 0; i < wlist->nwrs; i++) {
        core->core[CORESIZE/WARRIORS*i] = (struct instruction) {
            .opcode = MOV,
            .modifier = I,
            .a = { .mode = DIRECT, .number = 0 },
            .b = { .mode = DIRECT, .number = 1 }
        };
        queue_push_back(&wlist->l[i], CORESIZE/WARRIORS*i);
    }

    print_core(core);
    printf("\n");
    for (int i = 0; i < CYCLES*WARRIORS; i++) {
        cycle(wlist, core);
        print_core(core);
        printf("\n");
    }

    warrior_list_del(wlist);
    core_del(core);
}
