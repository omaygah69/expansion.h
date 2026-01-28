CC = clang
SRC = example.c
DIR= build

all: main
	./$(DIR)/example
main: $(SRC)
	$(CC) $(SRC) -o $(DIR)/example
clean:
	rm -rf $(DIR)/example

