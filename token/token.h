#ifndef TOKEN_H
#define TOKEN_H
#include <stddef.h>

typedef enum {
    // Single characters tokens
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,
    // One or two character tokens
    EQUAL = '=',
    BANG,
    BANG_EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,
    // Keywords.
    AND,
    CLASS,
    ELSE,
    FALSE,
    FUN,
    FOR,
    IF,
    NIL,
    OR,
    PRINT,
    RETURN,
    SUPER,
    THIS,
    TRUE,
    VAR,
    WHILE,

    EOF_,
    UNDEFINED

} TokenType;

typedef struct Token {
    TokenType type;
    char *lexeme;
    char *literal;
    size_t line;
} Token;

void toString(Token, char *);
#endif
