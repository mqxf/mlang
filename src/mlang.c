#include <stdlib.h>
#include "include/mlang.h"
#include "include/lexer.h"
#include "include/file.h"
#include "include/parser.h"

void mlang_compile(char *src) {
    lexer_T* lexer = init_lexer(src);
    parser_T* parser = init_parser(lexer);
    AST_T* root = parser_parse(parser);

    token_T* token = 0;
    while ((token = lexer_next_token(lexer))->type != TOKEN_EOF) {
        printf("%s", token_to_str(token));
    }
}

void mlang_init(const char* infile, const char* outfile) {
    char *src = mlang_read(infile);
    mlang_compile(src);
    free(src);
}
