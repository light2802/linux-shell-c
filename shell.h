#ifndef shell_h_INCLUDED
#define shell_h_INCLUDED

#include "source.h"

void print_prompt1();
void print_prompt2();

char *read_cmnd();

int parse_and_exec(source* src);

#endif //shell_h_INCLUDED
