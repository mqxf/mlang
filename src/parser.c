#include <stdlib.h>
#include <stdio.h>
#include "include/lexer.h"
#include "include/parser.h"

parser_T* init_parser(lexer_T *lexer) {
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->token = lexer_next_token(lexer);

    return parser;
}

token_T* parser_eat(parser_T* parser, int type) {
    if (parser->token->type != type) {
        printf("Unexpected token: %s. Was exection token of type: '%s'\n", token_to_str(parser->token), token_type_to_str(type));
        exit(1);
    }
    parser->token = lexer_next_token(parser->lexer);
    return parser->token;
}

AST_T* parser_parse(parser_T* parser) {
    return parser_parse_compound(parser);
}

AST_T* parser_parse_expr(parser_T* parser) {
    return init_ast(AST_NOOP);
}

AST_T* parser_parse_compound(parser_T* parser) {
    AST_T* compound = init_ast(AST_COMPOUND);
    while(parser->token->type != TOKEN_EOF) {
        list_push(compound->children, parser_parse_expr(parser));
    }
    return compound;
}
