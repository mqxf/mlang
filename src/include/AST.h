#ifndef MLANG_AST_H
#define MLANG_AST_H
#include "list.h"
typedef struct AST_STRUCT {
    enum {
        AST_COMPOUND,
        AST_FUNCTION_DEFINITION,
        AST_VARIABLE,
        AST_STATEMENT,
        AST_NOOP,
        AST_DEFINITION_TYPE,
    } type;
    list_T* children;
} AST_T;

AST_T* init_ast(int type);
#endif
