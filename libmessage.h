#define LANG_ENV_VARIABLE "LANGUAGE"
#define LANG_FILE_PREFIX "liblang_"
#define LANG_FILE_ENDING ".so"

char *get_message_lib();
char *get_message(void *lib, char *code);
void print_message(void *lib, char *code, char *ext);
void print_simple(char *msg, char *ext);
