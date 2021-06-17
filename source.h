#ifndef source_h_INCLUDED
#define source_h_INCLUDED

#define ERROR_CHAR 0

#define INIT_SRC_POS -2

typedef struct source_s    //structure for input buffer
{
    char* buffer;          //Input text buffer
    long buffer_size;      //Size of input text
    long curr_pos;         //char position in source
} source;

char next_char(source* src);
void unget_char(source* src);
char peek_char(source* src);
void skip_white_spaces(source* src);

#endif //source_h_INCLUDED
