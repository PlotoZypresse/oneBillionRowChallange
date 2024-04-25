#compiler settings
CC = clang
CFLAGS=-Wall -Wextra -g -O3
SRC_DIR = src
DATA_DIR = data
BIN_DIR = bin

# List of source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# List of object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# Name of the executable
TARGET = $(BIN_DIR)/oneBillion

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)

run: $(TARGET)
	time ./$(TARGET)

clean-exec:
	rm -f $(TARGET)
