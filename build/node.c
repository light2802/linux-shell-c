#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "shell.h"
#include "parser.h"
#include "node.h"

node* new_node(enum node_type_e type)
{
    node* nd =(node*)malloc(sizeof(node));
    if(!nd)
        return NULL;
    memset(nd, 0, sizeof(node));
    nd->type = type;
    return nd;
}

void add_child_node(node* parent, node* child)
{
    if(!parent || !child)
        return;
    if(!parent->first_child)
        parent->first_child = child;
    else
    {
        node* sibling=parent->first_child;
        while(sibling->next_sibling)
            sibling=sibling->next_sibling;
        sibling->next_sibling=child;
        child->prev_sibling=sibling;
    }
    parent->children++;
}

void free_node_tree(node* root)
{
    if(!root)
        return;

    node* child=root->first_child;

    while(child)
    {
        node* next=child->next_sibling;
        free_node_tree(child);
        child=next;
    }
    
    if(root->val_type==VAL_STR)
    {
        if(root->val.str)
            free(root->val.str);
    }
    free(root);
}

void set_node_val_str(node* nd, char* val)
{
    nd->val_type=VAL_STR;
    if(!val)
        nd->val.str=NULL;
    else

    {
        char* val2 =(char*)malloc(strlen(val)+1);
        if(!val2)
            nd->val.str=NULL;
        else
        {
            strcpy(val2, val);
            nd->val.str=val2;
        }
    }
}
