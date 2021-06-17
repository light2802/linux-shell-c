#ifndef executor_h_INCLUDED
#define executor_h_INCLUDED

#include "node.h"

char* search_path(char* file);
int exec_cmnd(int argc, char **argv);
int exec_simple_cmnd(node* nd);

#endif //executor_h_INCLUDED