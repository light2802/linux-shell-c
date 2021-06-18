#include "../shell.h"
#include "../symbol_table/symtab.h"

int dump(int argc, char **argv)
{
    dump_local_symtab();
    return 0;
}