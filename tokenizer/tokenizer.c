#include "tokenizer.h"

TokenType convertLexemeToToken(char *lexeme) {
    TokenType token;

    switch (*lexeme) {
        case '=':
            token = EQUAL;
            break;
        case '!':
            token = BANG;
            break;
        default:
            /*report("Wrong syntax");*/
            break;
    }
    return token;
}
