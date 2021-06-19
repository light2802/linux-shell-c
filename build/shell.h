#ifndef shell_h_INCLUDED
#define shell_h_INCLUDED

#include "source.h"

typedef struct builtin_s        //struct for builtin utilities
{
    char* name;     //utility name
    int (*func)(int argc, char **argv);     //function to call to execute the utility
} utility;

void init_shell();

void print_prompt1();
void print_prompt2();

char *read_cmnd();

int parse_and_exec(source* src);

int dump(int argc, char **argv);        //shell builtin utilities

extern utility utils[];      //list of builtin utilities
extern int utils_count;     //and their count
#endif //shell_h_INCLUDED
