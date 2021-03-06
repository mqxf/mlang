#ifndef MLANG_TOKEN_H
#define MLANG_TOEKN_H
typedef struct TOKEN_STRUCT {
    char* value;
    enum {
        TOKEN_ID, //name, or identifier (int, String, for, etc...)
        TOKEN_INT, //int
        TOKEN_STRING, //string value
        TOKEN_STATEMENT, //statement
        TOKEN_FLOAT, //float
        TOKEN_PLUS, //+
        TOKEN_STAR, //*
        TOKEN_DIVIDE, // /
        TOKEN_MINUS, //-
        TOKEN_ARROW_SMALL, //->
        TOKEN_EQUALS, //=
        TOKEN_ARROW_LARGE, //=>
        TOKEN_AND, //&&
        TOKEN_OR, //||
        TOKEN_NOT, //!
        TOKEN_ANDSIGN, //&
        TOKEN_BOR, //|
        TOKEN_BSHIFTR, //>>
        TOKEN_BSHIFTL, //<<
        TOKEN_LPAREN, //(
        TOKEN_RPAREN, //)
        TOKEN_LBRACE, //{
        TOKEN_RBRACE, //}
        TOKEN_RGRAVE, //<
        TOKEN_LGRAVE, //>
        TOKEN_COMMA, //,
        TOKEN_SEMI, //;
        TOKEN_COLON, //:
        TOKEN_DOT, //.
        TOKEN_EOF, //EOF
    } type;
} token_T;
token_T* init_token(char* value, int type);
const char* token_type_to_str(int type);
char* token_to_str(token_T* token);
#endif
