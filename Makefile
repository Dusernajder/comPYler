CC = clang
CFLAGS = -g -Wall -Wextra
SRC = main.c scanner/scanner.c token/token.c error/error.c utils/utils.c
OBJ = $(SRC:.c=.o)
TARGET = comPYler

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

