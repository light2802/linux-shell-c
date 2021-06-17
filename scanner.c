#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "shell.h"
#include "source.h"
#include "scanner.h"


char* token_buffer=NULL;
int token_buffer_size=0;
int token_buffer_index=-1;

token eof_token={
                    .text_len=0              
                };
//EOF token for end of input

void add_to_buffer(char c)
{
    token_buffer[token_buffer_index]=c;
    if(token_buffer_index>=token_buffer_size)
    {
        char* temp=(char*)realloc(token_buffer, token_buffer_size*2);
        if(!temp)
        {
            errno=ENOMEM;
            return;
        }
        token_buffer=temp;
        token_buffer_size*=2;
    }
}

token* create_token(char* str)
{
    token* tok =(token*)malloc(sizeof(token));
    if(!tok)
        return NULL;

    memset(tok,0,sizeof(token));
    tok->text_len=strlen(str);

    char *nstr=(char*)malloc(tok->text_len+1);

    if(!nstr)
    {
        free(tok);
        return NULL;
    }

    strcpy(nstr,str);
    tok->text=nstr;
    return tok;
}

void free_token(token* tok)
{
    if(tok->text)
        free(tok->text);
    free(tok);
}

token* tokenize(source* src)
{
    int endloop=0;
    if(!src || !src->buffer || !src->buffer_size)
    {
        errno=ENODATA;
        return &eof_token;
    }

    if(!token_buffer)
    {
        token_buffer_size=1024;
        token_buffer=(char*)malloc(token_buffer_size);
        if(!token_buffer)
        {
            errno=ENOMEM;
            return &eof_token;
        }
    }

    token_buffer_index=0;
    token_buffer[0]='\0';

    char nc=next_char(src);

    if(nc==ERROR_CHAR || nc==EOF)
        return &eof_token;

    do
    {
        switch(nc)
        {
            case ' ':
            case '\t':
            {
                if(token_buffer_index>0)
                    endloop=1;
                break;
            }
            case '\n':
            {
                if(token_buffer_index>0)
                    unget_char(src);
                else
                    add_to_buffer(nc);
                endloop=1;
                break;
            }
            default:
            {
                add_to_buffer(nc);
                break;
            }
        }
        if(endloop)
            break;
    }while((nc=next_char(src)) != EOF);
    
    if(token_buffer==0)
        return &eof_token;
    
    if(token_buffer_index>=token_buffer_size)
        token_buffer_index--;
    
    token_buffer[token_buffer_index] = '\0';

    token* tok = create_token(token_buffer);
    if(!tok)
    {
        fprintf(stderr, "Error : failed to allocate buffer: %s\n",strerror(errno));
        return &eof_token;
    }

    tok->src=src;
    return tok;
}