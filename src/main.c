#include <stdio.h>

#include "queue.h"
#include "core.h"
#include "mars.h"
#include "parse.h"

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
    parse_instruction("ADD.AB #4, $3\n", mars.core->core);

    parse_instruction("MOV.I $2, @2\n", mars.core->core + 1);

    char tmp[20];
    sprintf(tmp, "JMP.B $%d, $0\n", CORESIZE - 2);
    parse_instruction(tmp, mars.core->core + 2);

    parse_instruction("DAT.F #0, #0\n", mars.core->core + 3);

    queue_push_back(&mars.wlist->l[0], 0);

    // WARRIOR 2
    parse_instruction("MOV.I $0, $1\n", mars.core->core + 7);
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
