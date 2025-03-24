# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Iinclude
DEBUG_FLAGS := -g -O0

# Directories
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
BIN := matrix_app
TEST_BIN := matrix_tests

# Source files
MAIN_SRC := $(SRC_DIR)/main.cpp
TEST_SRC := $(SRC_DIR)/tests.cpp
MATRIX_SRC := $(SRC_DIR)/matrix.cpp

# Object files
MAIN_OBJ := $(BUILD_DIR)/main.o
TEST_OBJ := $(BUILD_DIR)/tests.o
MATRIX_OBJ := $(BUILD_DIR)/matrix.o

# Default target
all: release

# Release build (optimized)
release: CXXFLAGS += -O3
release: $(BIN)

# Debug build
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(BIN)

# Build main binary
$(BIN): $(MAIN_OBJ) $(MATRIX_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Build test binary
test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_OBJ) $(MATRIX_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Debug build for tests
test_debug: CXXFLAGS += $(DEBUG_FLAGS)
test_debug: $(TEST_BIN)
	./$(TEST_BIN)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(BIN) $(TEST_BIN)

.PHONY: all release debug clean test test_debug
