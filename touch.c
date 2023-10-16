#include "touch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>


char *get_message(void *lib, char *code) {
    char *(*fptr)(char *);

    *(void **)(&fptr) = dlsym(lib, "getm");
    char *dl_error = dlerror();
    if (dl_error) {
        printf("Cannot find or open %s function%s", code, LNE);
        return NULL;
    }
    char *r = fptr(code);
    return r;
}

int main(int argc, char *argv[], char *envp[])
{
    // check for env variable LANGUAGE
    char *req_value = getenv(LANG_ENV_VARIABLE);
    if (req_value == NULL) {
        req_value = "en";
    }
    // get lang file name
    char ll_name[17] = "";
    snprintf(ll_name, 17, "libmessage_%s.so", req_value);
    // load lang lib
    void *ll_lib = dlopen(ll_name, RTLD_LAZY);
    if (!ll_lib) {
        printf("Cannot open message library %s\n", ll_name);
        exit(EXIT_FAILURE);
    }

    if (argc < 2) {
        char *help = get_message(ll_lib, "_M_CLI_HELP");
        printf("%s%s", help, LNE);
        printf("%s ABSOLUTE_FILE_PATH_AND_NAME%s", argv[0], LNE);
        exit(EXIT_FAILURE);
    }

    char *full_path = argv[1];
    char dirs[MAX_DIRS][MAX_DIR_LEN];
    for (int i = 0; i < MAX_DIRS; i++) strcpy(dirs[i], "");
    int dir_count = 0;
    char *filename;

    char *token = strtok(full_path, LNS); 
    while (token != NULL && dir_count < MAX_DIRS) {
        filename = token;
        strcpy(dirs[dir_count], token);
        dir_count++;
        token = strtok(NULL, LNS);
    }
    
    char dir_path[MAX_DIRS*MAX_DIR_LEN] = "";
    if (FIRST_SLASH == 1) strcat(dir_path, LNS);
    strcat(dir_path, dirs[0]);
    for (int i = 1; i < dir_count - 1; i++) {
        strcat(dir_path, LNS);
        strcat(dir_path, dirs[i]);
        unsigned char res = dir_exists(dir_path);
        if (res == 0) {
            dir_create(dir_path);
        }
    }

    strcat(dir_path, LNS);
    strcat(dir_path, filename);
    unsigned char file_res = file_exists(dir_path);
    if (file_res == 0) {
        file_create(dir_path);
    } else {
        char *fexists_err = get_message(ll_lib, "_M_CLI_FEXIST");
        printf("%s [%s]%s", fexists_err, dir_path, LNE);
        return EXIT_FAILURE;
    }

    char *fcreated = get_message(ll_lib, "_M_CLI_FCREATED");
    printf("%s [%s]%s", fcreated, dir_path, LNE);
    return EXIT_SUCCESS;
}
