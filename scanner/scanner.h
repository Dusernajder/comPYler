#ifndef SCANNER_H
#define SCANNER_H
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "../tokenizer/token.h"

void scanTokens(char *, Token[]);
char advance(char *, size_t *);
bool isEOF(size_t, size_t);
void addToken(TokenType, Token *, char *, char *);

#endif
