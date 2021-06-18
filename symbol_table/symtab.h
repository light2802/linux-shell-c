#ifndef symtab_h_INCLUDED
#define symtab_h_INCLUDED

#include "../node.h"

#define MAX_SYMTAB_SIZE 256
#define FLAG_EXPORT (1<<0)      //export enty to forked commands

enum symbol_type_e      //the type of a symbol table entry's value
{
    SYM_STR ,
    SYM_FUNC ,
};

typedef struct symtab_entry_s       //symbol table entry structure
{
    char name;
    enum symbol_type_e type;
    char* value;
    unsigned int flags;
    struct symtab_entry_s* next;
    node* func_body;
} symtab_entry;

typedef struct symtab_s     //symbol table structure
{
    int level;
    symtab_entry *first, *last;
} symtab;

typedef struct symtab_stack_s       //symbol table stack structure
{
    int symtab_count;
    symtab* list[MAX_SYMTAB_SIZE];
    symtab* global_symtab, *local_symtab;
} symtab_stack;

void init_symtab();
symtab* new_symtab(int level);
symtab* stack_push();
symtab* stack_pop();
int rm_from_symtab(symtab_entry* entry, symtab* table);
symtab_entry* add_to_symtab(char* symbol);
symtab_entry* do_lookup(char* str, symtab* table);
symtab_entry* get_symtab_entry(char* str);
symtab* get_local_symatab();
symtab* get_global_symatab();
symtab_stack* get_symtab_stack();
void symtab_entry_setval(symtab_entry* entry, char* val);
void dump_local_symtab();
void free_symtab(symtab* table);

#endif //symtab_h_INCLUDED
