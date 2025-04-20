#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

int main(int argc, char *argv[argc]) {
    if (argc <= 1) {
        printf("Usage: ast_generator <output directory>");
        exit(EXIT_FAILURE);
    }

    char *output_dir = argv[1];
    /*char *output_dir = "tmp";*/

    char *definitions[] = {
        "Binary : Expression left, Token op, Expression right",
        "Grouping : Expression left",
        "Literal : PyObject value",
        "Unary : Token op, Expression right",
    };
    size_t definitions_length = sizeof(definitions) / sizeof(definitions[0]);

    define_ast(output_dir, "expression", definitions_length, definitions);

    return EXIT_SUCCESS;
}
