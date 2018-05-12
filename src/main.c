#include <stdio.h>

#include "queue.h"
#include "core.h"
#include "mars.h"
#include "parse.h"
#include "program.h"

#define CYCLES 3
#define WARRIORS 2
#define CORESIZE 35

int main() {
    struct mars mars;
    mars_init(&mars, CORESIZE, WARRIORS);

    for (int i = 0; i < mars.core->m; i++) {
        parse_instruction("DAT.F #1, #1\n", mars.core->core + i);
    }

    // WARRIOR 1
    struct program prg1;
    program_init(&prg1);
    program_read(&prg1, "dwarf.red");
    core_load(mars.core, 0, &prg1);
    queue_push_back(&mars.wlist->l[0], 0);

    // WARRIOR 2
    struct program prg2;
    program_init(&prg2);
    program_read(&prg2, "imp.red");
    core_load(mars.core, 7, &prg2);
    queue_push_back(&mars.wlist->l[1], 7);

    core_print(mars.core);
    printf("\n");
    while (game_winner(&mars) == -1) {
        cycle(&mars);
        core_print(mars.core);
        printf("\n");
    }

    printf("The winner is %d\n", game_winner(&mars));

    mars_del(&mars);
}
