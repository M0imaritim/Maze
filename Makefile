# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -Iinc
LIBS = -lSDL2 -lSDL2_image -lm

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

# Source and Object Files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Output Executable
TARGET = maze_game

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

re: clean all

.PHONY: all clean re
