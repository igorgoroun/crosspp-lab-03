#include "touch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Please define file path and name to be created.\n");
        printf("Usage:\n");
        printf("%s ABSOLUTE_FILE_PATH_AND_NAME\n\n", argv[0]);
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
        printf("Error: File [%s] already exists!%s", dir_path, LNE);
        return EXIT_FAILURE;
    }

    printf("Empty file [%s] created.%s", dir_path, LNE);
    return EXIT_SUCCESS;
}
