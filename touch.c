#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "touch.h"
#include "libmessage.h"


int main(int argc, char *argv[], char *envp[])
{
    // prepare library
    void *mlib = get_message_lib();

    if (argc < 2) {
        print_message(mlib, "_M_CLI_HELP", "");
        print_simple(argv[0], "ABSOLUTE_FILE_PATH_AND_NAME");
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
        // print file exists message
        print_message(mlib, "_M_CLI_FEXIST", dir_path);
        return EXIT_FAILURE;
    }

    // print success message
    print_message(mlib, "_M_CLI_FCREATED", dir_path);
    return EXIT_SUCCESS;
}
