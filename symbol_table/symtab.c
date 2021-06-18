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

void symtab_stack_add(symtab* table)
{
    stack.list[stack.symtab_count++]=table;
    stack.local_symtab=table;
}

symtab* stack_push()
{
    symtab* table=new_symtab(++symtab_level);
    symtab_stack_add(table);
    return table;
}

symtab* stack_pop()
{
    if(stack.symtab_count==0)
        return NULL;
    symtab* table=stack.list[stack.symtab_count-1];
    stack.list[--stack.symtab_count]=NULL;
    symtab_level--;

    if(stack.symtab_count==0)
    {
        stack.local_symtab=NULL;
        stack.global_symtab=NULL;
    }
    else
        stack.local_symtab=stack.list[stack.symtab_count-1];
    return table;

}

int rm_from_symtab(symtab_entry* entry, symtab* table)
{
    int res=0;
    if(entry->value)
        free(entry->value);
    if(entry->func_body)
        free_node_tree(entry->func_body);
    free(entry->name);
    if(table->first==entry)
    {
        table->first=table->first->next;
        if(table->last==entry)
            table->last=NULL;
        res=1;
    }
    else
    {
        symtab_entry* e=table->first, *p=NULL;
        while(e && e!=entry)
        {
            p=e;
            e=e->next;
        }
        if(e==entry)
        {
            p->next=entry->next;
            res=1;
        }
    }
    free(entry);
    return res;
}

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

symtab_entry* do_lookup(char* str, symtab* table)
{
    if(!str || !table)
        return NULL;
    symtab_entry* entry=table->first;
    while(entry)
    {
        if(!strcmp(entry->name,str))
            return entry;
        entry=entry->next;
    }
    return NULL;
}

symtab_entry* get_symtab_entry(char* str)
{
    int i=stack.symtab_count-1;
    do
    {
        symtab* tab=stack.list[i];
        symtab_entry* entry=do_lookup(str,tab);
        if(entry)
            return entry;
    }while(--i>=0);
    return NULL;
}

symtab* get_local_symatab()
{
    return stack.local_symtab;
}

symtab* get_global()
{
    return stack.global_symtab;
}

symtab_stack* get_symtab_stack()
{
    return &stack;
}

void symtab_entry_setval(symtab_entry* entry, char* val)
{
    if(entry->value)
    {
        free(entry->value);
    }

    if(!val)
    {
        entry->value = NULL;
    }
    else
    {
        char *val2 = malloc(strlen(val)+1);

        if(val2)
        {
            strcpy(val2, val);
        }
        else
        {
            fprintf(stderr, "error: no memory for symbol table entry's value\n");
        }

        entry->value = val2;
    }
}

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