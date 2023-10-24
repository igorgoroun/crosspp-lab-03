#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "libmessage.h"
#include "touch.h"

char *get_message_lib() {
    // library pointer
    void *message_lib;
    // library file name
    char *mfile_prefix = LANG_FILE_PREFIX;
    char *mfile_ending = LANG_FILE_ENDING;
    // check for env variable
    char *mfile_lang = getenv(LANG_ENV_VARIABLE);
    if (mfile_lang == NULL) {
        mfile_lang = "en";
    }
    // prepare library file name
    int mfile_name_len = strlen(mfile_prefix) + strlen(mfile_lang) + strlen(mfile_ending) + 1;
    char *mfile_name = malloc(mfile_name_len);
    snprintf(mfile_name, mfile_name_len, "%s%s%s", mfile_prefix, mfile_lang, mfile_ending);
    // load language lib
    message_lib = dlopen(mfile_name, RTLD_LAZY);
    if (!message_lib) {
        printf("Cannot open message library %s%s", mfile_name, LNE);
        exit(EXIT_FAILURE);
    }
    return message_lib;
}

char *get_message(void *lib, char *code) {
    char *(*fptr)(char *);
    // make a pointer to method in lib
    *(void **)(&fptr) = dlsym(lib, "getm");
    char *dl_error = dlerror();
    if (dl_error) {
        printf("Cannot find or open %s function%s", code, LNE);
        return NULL;
    }
    char *r = fptr(code);
    return r;
}

void print_message(void *lib, char *code, char *ext) {
    char *msg = get_message(lib, code);
    printf("%s %s%s", msg, ext, LNE);
}

void print_simple(char *msg, char *ext) {
    printf("%s %s%s", msg, ext, LNE);
}
