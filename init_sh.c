#include <string.h>
#include "shell.h"
#include "symbol_table/symtab.h"

extern char** env;

void init_shell()
{
    init_symtab();
    symtab_entry* entry;
    char** p2=env;
    while(*p2)
    {
        char* eq=strchr(*p2, '=');
        if(eq)
        {
            int len=eq=(*p2);
            char name[len+1];
            strncpy(name, *p2, len);
            name[len]='\0';
            entry=add_to_symtab(name);
            if(entry)
            {
                symtab_entry_setval(entry, eq+1);
                entry->flags|=FLAG_EXPORT;
            }
        }
        else
            entry=add_to_symtab(*p2);
        p2++;
    }
    entry=add_to_symtab("PS1");
    symtab_entry_setval(entry, "$");

    entry=add_to_symtab("PS2");
    symtab_entry_setval(entry, ">");
}