#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include/lexer.h"
#include "include/macros.h"

lexer_T* init_lexer(char* src) {
    lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->src = src;
    lexer->src_size = strlen(src);
    lexer->i = 0;
    lexer->c = src[0];

    return lexer;
}

void lexer_advance(lexer_T *lexer) {
    if (lexer->i <lexer->src_size && lexer->c != '\0') {
        lexer->i += 1;
        lexer->c = lexer->src[lexer->i];
    }
}

char lexer_peek(lexer_T* lexer, int offset) {
    return lexer->src[MIN(lexer->i+offset, lexer->src_size)];
} 

token_T* lexer_advance_with(lexer_T *lexer, token_T *token) {
    lexer_advance(lexer);
    return token;
}

void lexer_skip_whitespace(lexer_T *lexer) {
    while (lexer->c == 13 || lexer->c == 10 || lexer->c == ' ' || lexer->c == '\t') {
        lexer_advance(lexer);
    }
}

token_T* lexer_parse_id(lexer_T* lexer) {

    char* value = calloc(1, sizeof(char));
    while (isalnum(lexer->c)) {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    }

    return init_token(value, TOKEN_ID);
}

token_T* lexer_next_token(lexer_T* lexer) {
    while (lexer->c != '\0') {
        if (isalnum(lexer->c)) {
            return lexer_advance_with(lexer, lexer_parse_id(lexer));
        }

        /*
        TOKEN_INT int
        TOKEN_STRING String
        TOKEN_PLUS +
        TOKEN_STAR *
        TOKEN_DIVIDE /
        TOKEN_COMMENT //
        TOKEN_MINUS -
        TOKEN_ARROW_SMALL ->
        TOKEN_AND &&
        TOKEN_OR ||
        TOKEN_NOT !
        TOKEN_ANDSIGN &
        TOKEN_BOR |
        TOKEN_BSHIFTR >>
        TOKEN_BSHIFTL <<
        TOKEN_LPAREN (
        TOKEN_RPAREN )
        TOKEN_LBRACE {
        TOKEN_RBRACE }
        TOKEN_RGRAVE <
        TOKEN_LGRAVE >
        TOKEN_COMMA ,
        TOKEN_SEMI ;
        TOKEN_COLON :
        */

        switch(lexer->c) {
            case '=': {
                if (lexer_peek(lexer, 1) == '>') return lexer_advance_with(lexer, init_token("=>", TOKEN_ARROW_LARGE));
                return lexer_advance_with(lexer, init_token("=", TOKEN_EQUALS));
            } break;
            
        }
    }

    return init_token(0, TOKEN_EOF);
}
