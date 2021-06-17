#include <unistd.h>
#include "shell.h"
#include "parser.h"
#include "scanner.h"
#include "node.h"
#include "source.h"

node* parse_simple_command(token* tok)
{
    if(!tok)
        return NULL;
    
    node* cmnd = new_node(NODE_COMMAND);
    if(!cmnd)
        return NULL;
    
    source* src=tok->src;

    do
    {
        if(tok->text[0]=='\n')
        {
            free_token(tok);
            break;
        }
        node* word = new_node(NODE_VAR);
        if(!word)
        {
            free_node_tree(cmnd);
            free_token(tok);
            return NULL;
        }
        set_node_val_str(word, tok->text);
        add_child_node(cmnd, word);

        free_token(tok);
    }while( (tok=tokenize(src)) != &eof_token);
    return cmnd;
}