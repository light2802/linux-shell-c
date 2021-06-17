#ifndef parser_h_INCLUDED
#define parser_h_INCLUDED

#include "scanner.h"        //for struct token
#include "node.h"        //for struct node

node* parse_simple_command(token* tok);

#endif //parser_h_INCLUDED
