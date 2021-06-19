#ifndef scanner_h_INCLUDED
#define scanner_h_INCLUDED

typedef struct token_s      //structure for tokens
{
    source *src;            //source of input [For structure see source.h]
    int text_len;           //length of token text
    char* text;             //token text
} token;

extern token eof_token;     //EOF token for end of input

token* tokenize(source* src);
void free_token(token* tok);

#endif //scanner_h_INCLUDED
