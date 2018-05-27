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
    codp_mars_init(&mars, CORESIZE, WARRIORS);

    for (int i = 0; i < mars.core->m; i++) {
        codp_parse_instruction("DAT.F #1, #1\n", mars.core->core + i);
    }

    // WARRIOR 1
    struct program prg1;
    program_init(&prg1);
    program_read(&prg1, "dwarf.red");
    codp_core_load(mars.core, 0, &prg1);
    codp_queue_push_back(&mars.wlist->l[0], 0);

    // WARRIOR 2
    struct program prg2;
    program_init(&prg2);
    program_read(&prg2, "imp.red");
    codp_core_load(mars.core, 7, &prg2);
    codp_queue_push_back(&mars.wlist->l[1], 7);

    codp_core_print(mars.core);
    printf("\n");
    while (codp_mars_game_winner(&mars) == -1) {
        codp_mars_cycle(&mars);
        codp_core_print(mars.core);
        printf("\n");
    }

    printf("The winner is %d\n", codp_mars_game_winner(&mars));

    codp_mars_del(&mars);
}
