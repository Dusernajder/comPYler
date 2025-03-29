#ifndef SCANNER_H
#define SCANNER_H
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "../token/token.h"

void scanner_init(char *);

void scan_tokens(Token[]);
void scan_token(Token *);
void add_token(TokenType, Token *);

bool match_char(char, char);
char advance();
char peek();
char peek_next();
bool is_EOF();

char *string_literal();
char *number_literal();
char *identifier();

bool is_alpha(char c);
bool is_number(char c);

#endif
