/*
File Name: main_c
Author: Aarya Chaumal
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "shell.h"

//Problem: Driver for linux shell
int main(int argc, char **argv)
{
    char* cmnd;
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
        printf("%s\n",cmnd);
        free(cmnd);
    }while(1);
    exit(EXIT_SUCCESS);
    return 0;
}
