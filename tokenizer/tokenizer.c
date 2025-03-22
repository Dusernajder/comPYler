#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "tokenizer.h"

TokenType convertLexemeToToken(char *lexeme) {
    TokenType token;

    regex_t variableRegex = createRegex("[a-zA-z0-9_]");
    regex_t stringRegex = createRegex("(\"|\')*(\"|\')");
    regex_t wholeNumberRegex = createRegex("[0-9]");

    switch (*lexeme) {
        case '(':
            token = LEFT_PAREN;
            break;
        case ')':
            token = RIGHT_PAREN;
            break;
        case '{':
            token = LEFT_BRACE;
            break;
        case '}':
            token = RIGHT_BRACE;
            break;
        case ',':
            token = COMMA;
            break;
        case '.':
            token = DOT;
            break;
        case '-':
            token = MINUS;
            break;
        case '+':
            token = PLUS;
            break;
        case ';':
            token = SEMICOLON;
            break;
        case '/':
            token = SLASH;
            break;
        case '*':
            token = STAR;
            break;
        /*case '=':*/
        /*    token = EQUAL;*/
        /*    break;*/
        /*case '!':*/
        /*    token = BANG;*/
        /*    break;*/
        default:
            token = UNDEFINED;
            break;
    }

    return token;
}

regex_t createRegex(char *expression) {
    regex_t regex;

    int value = regcomp(&regex, expression, 0);
    if (!value) {
        printf("regex: \"%s\" - compiled successfully", expression);
    }
    else {
        printf("regex: \"%s\" - failed to compile", expression);
        exit(EXIT_FAILURE);
    }

    return regex;
}

