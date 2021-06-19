/*
File Name: main_c
Author: Aarya Chaumal
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "shell.h"
#include "source.h"
#include "parser.h"
#include "executor.h"

char *read_cmnd()
{
    char buffer[1024];
    char *ptr=NULL;
    char ptr_len=0;
    while(fgets(buffer, 1024, stdin))
    {
        int buffer_len=strlen(buffer);
        if(!ptr)
            ptr=(char*)malloc(buffer_len+1);
        else
        {
            char* ptr2 = (char*)realloc(ptr, ptr_len+1+buffer_len);
            if(ptr2)
                ptr=ptr2;
            else
            {
                free(ptr);
                ptr=NULL;
            }
        }
        if(!ptr)
        {
            fprintf(stderr,"Error : Failed to allocate buffer %s\n!!!Command to long to read!!!",strerror(errno));
            return NULL;
        }
        strcpy(ptr+ptr_len,buffer);
        if(buffer[buffer_len-1]=='\n')
        {
            if(buffer_len==1 || buffer[buffer_len-2]!='\\')
                return ptr;
            ptr[ptr_len+buffer_len-2]='\0';
            buffer_len-=2;
            print_prompt2();
        }
        ptr_len+=buffer_len;
    }
    return ptr;
}

int parse_and_exec(source* src)
{
    skip_white_spaces(src);

    struct token_s *tok = tokenize(src);

    if(tok == &eof_token)
    {
        return 0;
    }

    while(tok && tok != &eof_token)
    {
        node* cmnd = parse_simple_command(tok);

        if(!cmnd)
        {
            break;
        }

        exec_simple_cmnd(cmnd);
        free_node_tree(cmnd);
        tok = tokenize(src);
    }

    return 1;
}

//Problem: Driver for linux shell

int main(int argc, char **argv)
{
    char* cmnd;
    init_shell();
    do{
        print_prompt1();
        cmnd = read_cmnd();
        if(!cmnd)
            exit(EXIT_SUCCESS);
        if(cmnd[0] == '\0' || !strcmp(cmnd, "\n"))
        {
            free(cmnd);
            continue;
        }
        if(!strcmp(cmnd,"exit\n"))
        {
            free(cmnd);
            break;
        }
        source src;
        src.buffer= cmnd;
        src.buffer_size= strlen(cmnd);
        src.curr_pos= INIT_SRC_POS;
        parse_and_exec(&src);
        free(cmnd);
    }while(1);
    exit(EXIT_SUCCESS);
    return 0;
}
