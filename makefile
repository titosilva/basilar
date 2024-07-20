# Compiler
CC := g++
# Compiler flags
CFLAGS := -Wall -Wextra -pedantic -std=c++17
DEBUG_FLAGS := -g -D DEBUG
# Source directory
SRC_DIR := src
# Output directory
BUILD_DIR := build
# Binary name
MONTADOR_TARGET := montador
LIGADOR_TARGET := ligador

# Find all cpp files in the source directory and its subdirectories
SRCS := $(shell find $(SRC_DIR) -type f -name '*.cpp')
# Generate corresponding object file names
OBJS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SRCS:.cpp=.o))
# Include directories
INCLUDES := -I$(SRC_DIR)

montador: $(OBJS) $(BUILD_DIR)/montador.o
	$(CC) $(CFLAGS) $(OBJS) $(BUILD_DIR)/montador.o -o $(MONTADOR_TARGET)

ligador: $(OBJS) $(BUILD_DIR)/ligador.o
	$(CC) $(CFLAGS) $(OBJS) $(BUILD_DIR)/ligador.o -o $(LIGADOR_TARGET)

montador_debug: CFLAGS += $(DEBUG_FLAGS)
montador_debug: montador
	mv $(MONTADOR_TARGET) $(MONTADOR_TARGET)_debug

ligador_debug: CFLAGS += $(DEBUG_FLAGS)
ligador_debug: ligador
	mv $(LIGADOR_TARGET) $(LIGADOR_TARGET)_debug

# Rule to build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule to build montador.o and ligador.o
$(BUILD_DIR)/montador.o: montador.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c montador.cpp -o $(BUILD_DIR)/montador.o

$(BUILD_DIR)/ligador.o: ligador.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c ligador.cpp -o $(BUILD_DIR)/ligador.o

# Clean rule
clean:
	rm -rf $(BUILD_DIR) $(MONTADOR_TARGET) $(LIGADOR_TARGET) $(MONTADOR_TARGET)_debug $(LIGADOR_TARGET)_debug

.PHONY: clean