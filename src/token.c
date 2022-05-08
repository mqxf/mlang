#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "include/token.h"

token_T* init_token(char* value, int type) {
    token_T* token = calloc(1, sizeof(struct TOKEN_STRUCT));
    token->value = value;
    token->type = type;

    return token;
}

const char* token_type_to_str(int type) {
  switch (type) {
    case TOKEN_ID: return "TOKEN_ID";
    case TOKEN_EQUALS: return "TOKEN_EQUALS";
    case TOKEN_LPAREN: return "TOKEN_LPAREN";
    case TOKEN_RPAREN: return "TOKEN_RPAREN";
    case TOKEN_LBRACE: return "TOKEN_LBRACE";
    case TOKEN_RBRACE: return "TOKEN_RBRACE";
    case TOKEN_COLON: return "TOKEN_COLON";
    case TOKEN_COMMA: return "TOKEN_COMMA";
    case TOKEN_RGRAVE: return "TOKEN_RGRAVE";
    case TOKEN_LGRAVE: return "TOKEN_LGRAVE";
    case TOKEN_STRING: return "TOKEN_STRING";
    case TOKEN_INT: return "TOKEN_INT";
    case TOKEN_SEMI: return "TOKEN_SEMI";
    case TOKEN_STAR: return "TOKEN_STAR";
    case TOKEN_DIVIDE: return "TOKEN_DIVIDe";
    case TOKEN_COMMENT: return "TOKEN_COMMENT";
    case TOKEN_MINUS: return "TOKEN_MINUS";
    case TOKEN_ARROW_SMALL: return "TOKEN_ARROW_SMALL";
    case TOKEN_ARROW_LARGE: return "TOKEN_ARROW_LARGE";
    case TOKEN_AND: return "TOKEN_AND";
    case TOKEN_OR: return "TOKEN_OR";
    case TOKEN_STATEMENT: return "TOKEN_STATEMENT";
    case TOKEN_FLOAT: return "TOKEN_FLOAT";
    case TOKEN_CHAR: return "TOKEN_CHAR";
    case TOKEN_BOOL: return "TOKEN_BOOL";
    case TOKEN_PLUS: return "TOKEN_PLUS";
    case TOKEN_NOT: return "TOKEN_NOT";
    case TOKEN_ANDSIGN: return "TOKEN_ANDSIGN";
    case TOKEN_BOR: return "TOKEN_BOR";
    case TOKEN_BSHIFTR: return "TOKEN_BSHIFTR";
    case TOKEN_BSHIFTL: return "TOKEN_BSHIFTL";
    case TOKEN_SQUOTE: return "TOKEN_SQUOTE";
    case TOKEN_DQUOTE: return "TOKEN_DQUOTE";
    case TOKEN_EOF: return "TOKEN_EOF";
  }
  return "not_stringable";
}

char* token_to_str(token_T* token) {
  const char* type_str = token_type_to_str(token->type);
  const char* template = "TOKEN(type='%s', int_type='%d', value='%s')\n";

  char* str = calloc(strlen(type_str) + strlen(template) + 8, sizeof(char));
  sprintf(str, template, type_str, token->type, token->value);

  return str; 
}
