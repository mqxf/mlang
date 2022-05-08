#include "include/mlang.h"
#include "include/lexer.h"
#include "include/file.h"

void mlang_compile(char *src) {
    lexer_T* lexer = init_lexer(src);
    token_T* token = 0;
    while ((token = lexer_next_token(lexer))->type != TOKEN_EOF) {
        printf(token_to_str(token));
    }
}

void mlang_init(const char* infile, const char* outfile) {
    mlang_compile(mlang_read(infile));
}
