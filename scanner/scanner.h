#ifndef SCANNER_H
#define SCANNER_H
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "../tokenizer/token.h"

void scanner_init(char *);
void scan_tokens(Token[]);
bool match_char(char, char);
char advance();
char peek();
char peek_next();
bool is_EOF();
void add_token(TokenType, Token *);
void scan_token(Token *);

#endif
