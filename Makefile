CC = g++
CFLAGS = -Wall -Wextra
BIN_DIR = ./bin
LIBS = -ldl -lglfw -lm

run:
	$(CC) src/main.cpp src/engine/*.cpp src/chess/*.cpp lib/glad/glad.c -Ilib $(CFLAGS) -o $(BIN_DIR)/main $(LIBS) -std=c++20
	$(BIN_DIR)/main

debug:
	$(CC) src/main.cpp src/engine/*.cpp src/chess/*.cpp lib/glad/glad.c -Ilib $(CFLAGS) -o $(BIN_DIR)/main $(LIBS) -g -Og -ggdb3 -fsanitize=address
	$(BIN_DIR)/main