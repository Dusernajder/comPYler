#include <stdio.h>

#include "token.h"

void toString(Token token, char* out){
    sprintf(out,"%ud %s %s", token.type, token.lexeme, token.literal);
}
