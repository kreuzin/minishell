CC     = gcc
CFLAGS  = -Wall -Wextra -g
TARGET  = minishell
SRC     = $(wildcard src/*.c)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean
