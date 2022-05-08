#include <stdlib.h>
#include "include/mlang.h"
#include "include/lexer.h"
#include "include/file.h"

void mlang_compile(char *src) {
    lexer_T* lexer = init_lexer(src);
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
