#include <errno.h>
#include <stdio.h>
#include "shell.h"
#include "source.h"

char next_char(source* src)
{
    if(!src || src->buffer)
    {
        errno=ENODATA;
        return ERROR_CHAR;
    }
    char c1=0;
    if(src->curr_pos == INIT_SRC_POS)
        src->curr_pos=-1;
    else
        c1=src->buffer[src->curr_pos];
    if(++src->curr_pos>=src->buffer_size)
    {
        src->curr_pos=src->buffer_size;
        return EOF;
    }
    return EOF;
}

void unget_char(source* src)
{
    if(src->curr_pos <0)
        return;
    src->curr_pos--;
}

char peek_char(source* src)
{
    if(!src || !src->buffer)
    {
        errno=ENODATA;
        return ERROR_CHAR;
    }
    long pos=src->curr_pos;
    if(pos==INIT_SRC_POS)
        pos++;
    pos++;
    if(pos>=src->buffer_size)
        return EOF;
    return src->buffer[pos];
}

void skip_white_spaces(source* src)
{
    char c;
    if(!src || !src->buffer)
        return;
    while( ( (c=peek_char(src) )!=EOF) && (c==' ' || c=='\t') )
    {
        next_char(src);
    }
}