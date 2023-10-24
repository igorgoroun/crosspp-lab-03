#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liblang.h"

char *getm(char *code) {
    char mess[128] = "";
    if (strcmp(code, "_M_CLI_HELP") == 0) {
        strcat(mess, _M_CLI_HELP);
    }
    if (strcmp(code, "_M_CLI_FEXIST") == 0) {
        strcat(mess, _M_CLI_FEXIST);
    }
    if (strcmp(code, "_M_CLI_FCREATED") == 0) {
        strcat(mess, _M_CLI_FCREATED);
    }
    char* str = malloc(strlen(mess) + 1);
    strcpy(str, mess);
    return str;
}

