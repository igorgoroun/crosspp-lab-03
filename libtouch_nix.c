#include <stdio.h>
#include <sys/stat.h>
// необхідно підключати заголовки у файлах реалізації
#include "touch.h"

// Implementation for unix systems
unsigned char dir_exists(char *dir_path) {
    struct stat dirStat;
    if (stat(dir_path, &dirStat) == 0 && S_ISDIR(dirStat.st_mode)) return 1;
    else return 0;
}
void dir_create(char *dir_path) {
    mkdir(dir_path, 0755);
}
unsigned char file_exists(char *file_path){
    struct stat fileStat;
    if (stat(file_path, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) return 1;
    else return 0;
}
void file_create(char *file_path){
    FILE *f = fopen(file_path, "w");
    fclose(f);
}
