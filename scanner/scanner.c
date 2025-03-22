#include "scanner.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../error/error.h"
#include "../tokenizer/token.h"
#include "../tokenizer/tokenizer.h"

extern bool hadError;

size_t lineNumber = 1;
size_t start = 0;
size_t current = 0;

void scanTokens(char *source, Token tokens_p[]) {
    size_t sourceLength = strlen(source);
    size_t counter = 0;

    while (!isEOF(current, sourceLength)) {

        char *lexeme = malloc(current - start + 1);
        lexeme = strncpy(lexeme, *(&source + start), current);

        printf("Lexeme: %s\n", lexeme);

        TokenType token = convertLexemeToToken(lexeme);

        if (token == UNDEFINED) {
            hadError = true;
            error(lineNumber, strcat("Undefined Lexeme: ", lexeme));
            break;
        }
        else {
            addToken(token, &tokens_p[counter], lexeme, lexeme);
            start = current;
            counter++;
        }

        /*tokens_p[lineNumber] = token;*/

        free(lexeme);
        advance(source, &current);
    }

    /*tokens_p[lineNumber + 1] = EOF_;*/
}

char advance(char *source, size_t *current) {
    return source[*current++];
}

bool isEOF(size_t current, size_t sourceLength) {
    return current >= sourceLength;
}

void addToken(TokenType type, Token *tokenLocation_p, char *literal, char *lexeme) {
    Token token = {
        .type = type,
        .lexeme = literal,
        .literal = literal,
        .line = lineNumber};

    *tokenLocation_p = token;
}
