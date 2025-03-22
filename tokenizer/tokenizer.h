#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <regex.h>

#include "token.h"

TokenType convertLexemeToToken(char *);
regex_t createRegex(char *);

#endif
