#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"
#include "../error/error.h"
#include "../token/token.h"
#include "../utils/utils.h"

static unsigned int source_length;
static char *source;
static unsigned int line_number = 1;
static size_t start;
static size_t current;

void scanner_init(char *input_source) {
    start = 0;
    current = 0;
    source_length = strlen(input_source);
    source = check_malloc(malloc(source_length + 1));
    source = input_source;
}

void scan_tokens(Token tokens_p[]) {

    for (unsigned int i = 0; !is_EOF(); i++) {
        start = current;
        scan_token(&(tokens_p[i]));

        if (tokens_p[i].type == UNDEFINED) {
            --i;
        }
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
    current++;

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
    size_t literal_length = current - start;
    char *literal = check_malloc(malloc(literal_length + 1));
    strncpy(literal, &source[start], literal_length);

    literal[literal_length] = '\0';

    Token token = {
        .type = type,
        .lexeme = literal,
        .literal = literal,
        .line = line_number,
    };

    *token_location_p = token;
}

void add_token_literal(TokenType type, Token *token_location_p, char *literal) {
    char *lexeme = NULL;
    if (type == STRING) {
        size_t lexeme_length = strlen(literal) + 3; // +2 for quotes, +1 for null terminator
        lexeme = check_malloc(malloc(lexeme_length));
        snprintf(lexeme, lexeme_length, "\"%s\"", literal);
    }

    Token token = {
        .type = type,
        .lexeme = lexeme == NULL ? literal : lexeme,
        .literal = literal,
        .line = line_number,
    };

    *token_location_p = token;
}

char *string_literal() {
    while (peek() != '"' && !is_EOF()) {
        if (peek() == '\n') line_number++;
        advance();
    }

    if (is_EOF()) {
        error(line_number, "string literal was not terminated.");
        exit(EXIT_FAILURE);
    }

    size_t literal_length = current - start;
    char *literal = check_malloc(malloc(literal_length + 1));
    strncpy(literal, &source[start + 1], literal_length);
    literal[literal_length] = '\0';

    // closing "
    advance();

    return literal;
}

char *identifier() {
    while (is_alpha_numeric(peek())) {
        advance();
    }

    size_t identifier_length = current - start;
    char *identifier = check_malloc(malloc(identifier_length + 1));
    strncpy(identifier, &source[start], identifier_length);
    identifier[identifier_length] = '\0';

    return identifier;
}

bool is_alpha(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

bool is_alpha_numeric(char c) {
    return is_alpha(c) || is_numeric(c);
}

bool is_numeric(char c) {
    return c >= '0' && c <= '9';
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
        case '[':
            add_token(LEFT_BRACKET, token_p);
            break;
        case ']':
            add_token(RIGHT_BRACKET, token_p);
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
            add_token(SLASH, token_p);
            break;
        case '#':
            add_token(HASH, token_p);
            while (peek() != '\n') { // WARN: possible segfault? (at file end)
                advance();
            }
            break;
        case ' ':
            add_token(UNDEFINED, token_p);
            break;
        case '\r':
            add_token(UNDEFINED, token_p);
            break;
        case '\t':
            add_token(TAB, token_p);
            break;
        case '\n':
            add_token(UNDEFINED, token_p);
            line_number++;
            break;
        case '"':
            add_token_literal(STRING, token_p, string_literal());
            break;
        default:
            if (is_numeric(c)) {
                add_token_literal(NUMBER, token_p, number_literal());
                break;
            }
            else if (is_alpha_numeric(c)) {
                char *id = identifier();
                TokenType type = get_token_type(id);
                add_token_literal(type == UNDEFINED ? IDENTIFIER : type, token_p, id);
                break;
            }
            error(line_number, "Unexpected character.");
            break;
    }
}
