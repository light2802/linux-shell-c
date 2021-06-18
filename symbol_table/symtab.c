#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../shell.h"
#include "../node.h"
#include "../parser.h"
#include "symtab.h"

symtab_stack stack;
int symtab_level;

void init_symtab()
{
    stack.symtab_count=1;
    symtab_level=0;
    symtab* global_symtab = (symtab*)malloc(sizeof(symtab));

    if(!global_symtab)
    {
        fprintf(stderr,"Fatal Error : No memory for global symbol table\n");
        exit(EXIT_FAILURE);
    }
    
    memset(global_symtab, 0, sizeof(symtab));
    stack.global_symtab=global_symtab;
    stack.local_symtab=global_symtab;
    stack.list[0]=global_symtab;
    global_symtab->level=0;
}

symtab* new_symtab(int level)
{
    symtab* table = (symtab*)malloc(sizeof(symtab));

    if(!table)
    {
        fprintf(stderr, "Fatal Error: no memory for new symbol table\n");
        exit(EXIT_FAILURE);
    }

    memset(table, 0, sizeof(symtab));
    table->level = level;
    return table;
}

symtab* stack_push();

symtab* stack_push();

int rm_from_symtab(symtab_entry* entry, symtab* table);

symtab_entry* add_to_symtab(char* symbol)
{
    if(!symbol || symbol[0]=='\0')
        return NULL;
    symtab* st=stack.local_symtab;
    symtab_entry* entry=NULL;

    if( entry=do_lookup(symbol, st) )
        return entry;
    
    entry=(symtab_entry*)malloc(sizeof(symtab_entry));
    if(!entry)
    {
        fprintf(stderr, "fatal error: no memory for new symbol table entry\n");
        exit(EXIT_FAILURE);
    }

    memset(entry, 0, sizeof(symtab_entry));
    entry->name = malloc(strlen(symbol)+1);

    if(!entry->name)
    {
        fprintf(stderr, "fatal error: no memory for new symbol table entry\n");
        exit(EXIT_FAILURE);
    }

    strcpy(entry->name, symbol);

    if(!st->first)
    {
        st->first = entry;
        st->last = entry;
    }
    else
    {
        st->last->next = entry;
        st->last = entry;
    }
    return entry;
}

symtab_entry* do_lookup(char* str, symtab* table);

symtab_entry* get_symtab_entry(char* str);

symtab* get_local();

symtab* get_global();

symtab_stack* get_symtab_stack();

void symtab_entry_setval(symtab_entry* entry, char* val);

void dump_local_symtab()
{
    symtab* table= stack.local_symtab;
    int i=0;
    int indent=table->level*4;

    fprintf(stderr, "%*sSymbol table [Level %d]:\r\n", indent, " ", table->level);
    fprintf(stderr, "%*s===========================\r\n", indent, " ");
    fprintf(stderr, "%*s  No               Symbol                    Val\r\n", indent, " ");
    fprintf(stderr, "%*s------ -------------------------------- ------------\r\n", indent, " ");
    
    symtab_entry* entry=table->first;
    while(entry)
    {
        fprintf(stderr, "%*s[%04d] %-32s '%s'\r\n", indent, " ",i++, entry->name, entry->value);
        entry = entry->next;
    }

    fprintf(stderr, "%*s------ -------------------------------- ------------\r\n", indent, " ");
}

void free_symtab(symtab* table)
{
    if(table == NULL)
    {
        return;
    }
    symtab_entry* entry = table->first;
    while(entry)
    {
        if(entry->name)
        {
            free(entry->name);
        }

        if(entry->value)
        {
            free(entry->value);
        }

        if(entry->func_body)
        {
            free_node_tree(entry->func_body);
        }

        symtab_entry* next = entry->next;
        free(entry);
        entry = next;
    }
    free(table);
}