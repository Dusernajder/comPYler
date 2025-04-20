CC = clang
CFLAGS = -g -Wall -Wextra -Isrc

# Shared source files
SHARED_SRC = src/token/token.c src/error/error.c src/utils/utils.c
SHARED_OBJ = $(SHARED_SRC:.c=.o)

# comPYler:
P1_SRC = src/main.c src/scanner/scanner.c 
P1_OBJ = $(P1_SRC:.c=.o)
P1_TARGET = comPYler

# ast_generator:
P2_SRC = src/tool/ast_generator.c src/tool/ast.c src/tool/py_type/py_type.c
P2_OBJ = $(P2_SRC:.c=.o)
P2_TARGET = ast_generator

all: $(P1_TARGET) $(P2_TARGET)

# Link targets
$(P1_TARGET): $(P1_OBJ) $(SHARED_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(P2_TARGET): $(P2_OBJ) $(SHARED_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(P1_OBJ) $(P2_OBJ) $(SHARED_OBJ) $(P1_TARGET) $(P2_TARGET)
