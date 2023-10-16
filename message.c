#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "message.h"

char *getm(char *code) {
    char mess[128] = "";
    if (strcmp(code, "_M_CLI_HELP") == 0) {
        strcat(mess, _M_CLI_HELP);
    }
    char* str = (char*) malloc(sizeof(char) * (strlen(mess) + 1));
    strcpy(str, mess);
    return str;
}
