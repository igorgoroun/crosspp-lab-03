#if (defined(__APPLE__) && defined(__MACH__)) || defined __unix__
#define LNE "\n"
#define LNS "/"
#define FIRST_SLASH 1
#elif defined(_WIN32) || defined(WIN32) 
#define LNE "\r\n"
#define LNS "\\"
#define FIRST_SLASH 0
#endif

#define LANG_ENV_VARIABLE "LANGUAGE"
#define MAX_DIR_LEN 64
#define MAX_DIRS 16

// Declaration for unix
unsigned char dir_exists(char *dir_path);
void dir_create(char *dir_path);
unsigned char file_exists(char *file_path);
void file_create(char *file_path);
