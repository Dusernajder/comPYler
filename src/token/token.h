#ifndef TOKEN_H
#define TOKEN_H
#include <stddef.h>

typedef enum {
    // Single characters tokens
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACKET,
    RIGHT_BRACKET,
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
    HASH,
    COLON,
    // Keywords.
    AND,
    OR,
    TRUE,
    FALSE,
    DEF,
    FOR,
    WHILE,
    IF,
    ELIF,
    ELSE,
    NIL,
    CLASS,
    PRINT,
    RETURN,
    SELF,
    // Literals.
    IDENTIFIER,
    STRING,
    NUMBER,
    // Escape character
    TAB,
    NEW_LINE,

    EOF_,
    UNDEFINED,

} TokenType;

typedef struct Token {
    TokenType type;
    char *lexeme;
    char *literal;
    size_t line;
} Token;

typedef struct KeyTokenTypePair {
    char *key;
    TokenType type;
} KeyTokenTypePair;

TokenType try_get_keyword_type(char *);
void to_string(Token, char *);

#endif
