#include "scanner.h"
#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../error/error.h"
#include "../tokenizer/token.h"

static unsigned int source_length;
static char *source;
static unsigned int line_number = 1;
static size_t start;
static size_t current;

void scanner_init(char *input_source) {
    start = 0;
    current = 0;
    source_length = strlen(source);
    source = malloc(source_length + 1);
    if (source == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    source = input_source;
}

void scan_tokens(Token tokens_p[]) {

    for (unsigned int i = 0; !is_EOF(); i++) {
        start = current;
        scan_token(&tokens_p[i]);
    }

    add_token(EOF_, &tokens_p[line_number]);
}

bool match_char(char lexeme, char expected) {
    if (is_EOF()) return false;
    if (lexeme != expected) return false;

    return true;
}

char advance() {
    char value = source[current];
    current = current + 1;

    return value;
}

char peek() {
    if (is_EOF()) return '\0';

    return source[current];
}

char peek_next() {
    if (current + 1 >= source_length) return '\0';

    return source[current + 1];
}

bool is_EOF() {
    return current >= source_length;
}

void add_token(TokenType type, Token *token_location_p) {
    char line[4];
    sprintf(line, "%d", line_number);
    char *literal = malloc(current - start + 1);
    literal = strncpy(literal, *(&source + start), current);

    Token token = {
        .type = type,
        .lexeme = literal,
        .literal = literal,
        .line = line_number,
    };

    *token_location_p = token;
}

void scan_token(Token *token_p) {
    char c = advance();

    switch (c) {
        case '(':
            add_token(LEFT_PAREN, token_p);
            break;
        case ')':
            add_token(RIGHT_PAREN, token_p);
            break;
        case '{':
            add_token(LEFT_BRACE, token_p);
            break;
        case '}':
            add_token(RIGHT_BRACE, token_p);
            break;
        case ',':
            add_token(COMMA, token_p);
            break;
        case '.':
            add_token(DOT, token_p);
            break;
        case '-':
            add_token(MINUS, token_p);
            break;
        case '+':
            add_token(PLUS, token_p);
            break;
        case ';':
            add_token(SEMICOLON, token_p);
            break;
        case '*':
            add_token(STAR, token_p);
            break;
        case '=':
            add_token(match_char(c, EQUAL) ? EQUAL_EQUAL : EQUAL, token_p);
            break;
        case '!':
            add_token(match_char(c, EQUAL) ? BANG_EQUAL : BANG, token_p);
            break;
        case '<':
            add_token(match_char(c, EQUAL) ? LESS_EQUAL : LESS, token_p);
        case '>':
            add_token(match_char(c, EQUAL) ? GREATER_EQUAL : GREATER, token_p);
        case '/':
            if (match_char(c, '/')) {
                while (peek() != '\n') { // possible segfault? (at file end)
                    advance();
                }
                break;
            }
            add_token(SLASH, token_p);
            break;
        case ' ':
        case '\r':
        case '\n':
            line_number++;
            break;
        default:
            error(line_number, "Unexpected character.");
            break;
    }
}
