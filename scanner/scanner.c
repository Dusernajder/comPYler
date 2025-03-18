#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../tokenizer/tokenizer.h"

void scanTokens(char *source, TokenType tokensp[]) {
    size_t sourceLength = strlen(source);
    for (int i = 0; i < sourceLength; i++) {
        char *lexeme = (source + i);
        /*if (lexeme == NULL || strcmp(lexeme, "\0")) {*/
        /*    break;*/
        /*}*/

        printf("Lexeme: %s\n", lexeme);

        TokenType token = convertLexemeToToken(lexeme);
        tokensp[i] = token;
    }
}
