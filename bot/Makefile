# Variables
CC      := g++
CFLAGS  := -Wall -Werror -Wextra -std=c++98
SRC     := $(wildcard *.cpp)
OBJ_DIR := obj
BIN_DIR := bin
OBJ     := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC))
TARGET  := $(BIN_DIR)/bot

# Default rule
all: $(TARGET)

# Target rule: Link object files and create the executable in bin directory
$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .cpp files into .o files inside obj directory
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure obj directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Ensure bin directory exists
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean rule: remove object files and target binary
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Rebuild everything from scratch
re: clean all

# Phony targets
.PHONY: all clean re
