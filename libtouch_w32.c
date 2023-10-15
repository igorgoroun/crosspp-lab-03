#include <windows.h>
#include <stdio.h>
#include "touch.h"

// Implementation for windows
unsigned char dir_exists(char *dir_path) {
    DWORD dwAttrib = GetFileAttributes(dir_path);
    if (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) return 1;
    else return 0;
}
void dir_create(char *dir_path) {
    CreateDirectory(dir_path, NULL);
}
unsigned char file_exists(char *file_path){
    DWORD dwAttr = GetFileAttributes(file_path);
    if (dwAttr == 0xffffffff){
        DWORD dwError = GetLastError();
        if (dwError == ERROR_FILE_NOT_FOUND) return 0;
    }
    return 1;
}
void file_create(char *file_path){
    HANDLE f = CreateFile(file_path, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(f, "", 0, NULL, NULL);
    CloseHandle(f);
}
