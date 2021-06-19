#include <stdio.h>
#include "symbol_table/symtab.h"
#include "shell.h"

void print_prompt1()
{
    symtab_entry* entry=get_symtab_entry("PS1");
    if(entry && entry->value)
        fprintf(stderr,"%s", entry->value);
    else
        fprintf(stderr, "$");
}

void print_prompt2()
{
    symtab_entry* entry=get_symtab_entry("PS2");
    if(entry && entry->value)
        fprintf(stderr,"%s", entry->value);
    else
        fprintf(stderr, ">");
}