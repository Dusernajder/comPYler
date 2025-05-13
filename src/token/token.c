#include <stdio.h>
#include <string.h>

#include "token.h"

const KeyTokenTypePair keywords[] = {
    {"and", AND},
    {"or", OR},
    {"True", TRUE},
    {"False", FALSE},
    {"def", DEF},
    {"for", FOR},
    {"while", WHILE},
    {"if", IF},
    {"elif", ELIF},
    {"else", ELSE},
};

const unsigned int keywords_size = sizeof(keywords) / sizeof(keywords[0]);

TokenType try_get_keyword_type(const char *keyword) {
    TokenType type = UNDEFINED;
    for (unsigned int i = 0; i < keywords_size; i++) {
        if (!strcmp(keywords[i].key, keyword)) {
            type = keywords[i].type;
            break;
        }
    }

    return type;
}

void to_string(Token token, char *out) {
    sprintf(out, "%ud %s %s", token.type, token.lexeme, token.literal);
}
