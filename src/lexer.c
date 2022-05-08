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

token_T* lexer_advance_current(lexer_T* lexer, int type) {
    char* value = calloc(2, sizeof(char));

    value[0] = lexer->c;
    value[1] = '\0';

    token_T* token = init_token(value, type);
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
    do {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    } while (isalpha(lexer_peek(lexer, 1)));
    value = realloc(value, (strlen(value) + 2) * sizeof(char));
    strcat(value, (char[]){lexer->c, 0});

    return init_token(value, TOKEN_ID);
}

token_T* lexer_parse_number(lexer_T* lexer) {
 
    char* value = calloc(1, sizeof(char));
    while (isdigit(lexer->c)) {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    }

    return init_token(value, TOKEN_INT);   
}

token_T* lexer_next_token(lexer_T* lexer) {
    while (lexer->c != '\0') {
        lexer_skip_whitespace(lexer);
        if (isalpha(lexer->c)) {
            return lexer_advance_with(lexer, lexer_parse_id(lexer));
        }

        if (isdigit(lexer->c)) {
            return lexer_advance_with(lexer, lexer_parse_number(lexer));
        }

        switch(lexer->c) {
            case '=': {
                if (lexer_peek(lexer, 1) == '>') return lexer_advance_with(lexer, init_token("=>", TOKEN_ARROW_LARGE));
                return lexer_advance_current(lexer, TOKEN_EQUALS);
            } break;
            case '/': {
                if (lexer_peek(lexer, 1) == '/') return lexer_advance_with(lexer, init_token("//", TOKEN_COMMENT));
                return lexer_advance_current(lexer, TOKEN_DIVIDE);
            } break;
            case '-': {
                if (lexer_peek(lexer, 1) == '>') return lexer_advance_with(lexer, init_token("->", TOKEN_ARROW_SMALL));
                return lexer_advance_current(lexer, TOKEN_MINUS);
            } break;
            case '&': {
                if (lexer_peek(lexer, 1) == '&') return lexer_advance_with(lexer, init_token("&&", TOKEN_AND));
                return lexer_advance_current(lexer, TOKEN_ANDSIGN);
            } break;
            case '|': {
                if (lexer_peek(lexer, 1) == '|') return lexer_advance_with(lexer, init_token("||", TOKEN_OR));
                return lexer_advance_current(lexer, TOKEN_BOR);
            } break;
            case '>': {
                if (lexer_peek(lexer, 1) == '>') return lexer_advance_with(lexer, init_token(">>", TOKEN_BSHIFTR));
                return lexer_advance_current(lexer, TOKEN_RGRAVE);
            } break;
            case '<': {
                if (lexer_peek(lexer, 1) == '<') return lexer_advance_with(lexer, init_token("<<", TOKEN_BSHIFTL));
                return lexer_advance_current(lexer, TOKEN_LGRAVE);
            } break;
            case '(': return lexer_advance_current(lexer, TOKEN_LPAREN);
            case ')': return lexer_advance_current(lexer, TOKEN_RPAREN);
            case '{': return lexer_advance_current(lexer, TOKEN_LBRACE);
            case '}': return lexer_advance_current(lexer, TOKEN_RBRACE);
            case ',': return lexer_advance_current(lexer, TOKEN_COMMA);
            case ';': return lexer_advance_current(lexer, TOKEN_SEMI);
            case ':': return lexer_advance_current(lexer, TOKEN_COLON);
            case '"': return lexer_advance_current(lexer, TOKEN_DQUOTE);
            case '\'': return lexer_advance_current(lexer, TOKEN_SQUOTE);
            case '!': return lexer_advance_current(lexer, TOKEN_NOT);
            case '+': return lexer_advance_current(lexer, TOKEN_PLUS);
            case '*': return lexer_advance_current(lexer, TOKEN_STAR);
            case '\0': break;
            default: printf("[mlang]: Unexpected token: %c.", lexer->c); exit(1); break;
        }
    }

    return init_token(0, TOKEN_EOF);
}
