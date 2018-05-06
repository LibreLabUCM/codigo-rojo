#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "instruction.h"
#include "core.h"

/*
void parse_core(char *str, struct core *core) {
    
}
*/

char *parse_opcode(char *str, enum opcode *opcode) {
    char opcode_str[4] = { 0 };
    strncpy(opcode_str, str, 3);
    if (strcmp(opcode_str, "DAT") == 0)
        *opcode = DAT;
    else if (strcmp(opcode_str, "MOV") == 0)
        *opcode = MOV;
    else if (strcmp(opcode_str, "ADD") == 0)
        *opcode = ADD;
    else if (strcmp(opcode_str, "SUB") == 0)
        *opcode = SUB;
    else if (strcmp(opcode_str, "MUL") == 0)
        *opcode = MUL;
    else if (strcmp(opcode_str, "DIV") == 0)
        *opcode = DIV;
    else if (strcmp(opcode_str, "MOD") == 0)
        *opcode = MOD;
    else if (strcmp(opcode_str, "JMP") == 0)
        *opcode = JMP;
    else if (strcmp(opcode_str, "CMP") == 0)
        *opcode = CMP;
    else if (strcmp(opcode_str, "SPL") == 0)
        *opcode = SPL;
    else
        return NULL;
    return str + 3;
}

char *parse_modifier(char *str, enum modifier *modifier) {
    if (str[0] == '\0' || str[1] == '\0')
        return NULL;
    switch (str[0]) {
    case 'A':
        if (str[1] == 'B') {
            *modifier = AB;
            return str + 2;
        } else {
            *modifier = A;
        }
        break;
    case 'B':
        if (str[1] == 'A') {
            *modifier = BA;
            return str + 2;
        } else {
            *modifier = B;
        }
        break;
    case 'F': *modifier = F; break;
    case 'X': *modifier = X; break;
    case 'I': *modifier = I; break;
    default: return NULL;
    }
    return str + 1;
}

char *parse_mode(char *str, enum mode *mode) {
    switch (*str) {
    case '#': *mode = IMMEDIATE; break;
    case '$': *mode = DIRECT; break;
    case '@': *mode = INDIRECT; break;
    case '<': *mode = DECREMENT; break;
    case '>': *mode = INCREMENT; break;
    case '\0': return NULL;
    default:
        *mode = IMMEDIATE;
        return str;
    }
    return str + 1;
}

char *skip_spaces(char *str) {
    while (*str == ' ')
        str++;
    return str;
}

char *skip_spaces1(char *str) {
    if (*str != ' ')
        return NULL;
    return skip_spaces(str + 1);
}

bool is_digit(char c) {
    return c == '0'
        || c == '1'
        || c == '2'
        || c == '3'
        || c == '4'
        || c == '5'
        || c == '6'
        || c == '7'
        || c == '8'
        || c == '9';
}

int digit_to_int(char c) {
    switch (c) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    }
    return -1;
}

char *parse_number(char *str, unsigned int *number) {
    if (!is_digit(*str))
        return NULL;
    int i = 0;
    while (is_digit(str[i])) {
        if (str[i] == '\0')
            return false;
        i++;
    }
    *number = 0;
    int k = 1;
    for (int j = i - 1; j >= 0; j--) {
        *number += digit_to_int(str[j]) * k;
        k *= 10;
    }
    return str + i;
}

char *parse_instruction(char *str, struct instruction *ir) {
    str = skip_spaces(str);
    str = parse_opcode(str, &ir->opcode);
    if (str == NULL)
        return NULL;
    if (*str != '.')
        return NULL;
    str++;
    str = parse_modifier(str, &ir->modifier);
    if (str == NULL)
        return NULL;
    str = skip_spaces1(str);
    if (str == NULL)
        return NULL;
    str = parse_mode(str, &ir->a.mode);
    if (str == NULL)
        return NULL;
    str = parse_number(str, &ir->a.number);
    if (str == NULL)
        return NULL;
    str = skip_spaces(str);
    if (*str != ',')
        return NULL;
    str++;
    str = skip_spaces(str);
    str = parse_mode(str, &ir->b.mode);
    if (str == NULL)
        return NULL;
    str = parse_number(str, &ir->b.number);
    if (str == NULL)
        return NULL;
    str = skip_spaces(str);
    if (*str != '\n')
        return NULL;
    return str + 1;
}
