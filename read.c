#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "shell.h"

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