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
BENCH_BIN := matrix_benchmark

# Source files
MAIN_SRC := $(SRC_DIR)/main.cpp
TEST_SRC := $(SRC_DIR)/tests.cpp
BENCH_SRC := $(SRC_DIR)/benchmark.cpp
MATRIX_SRC := $(SRC_DIR)/matrix.cpp
STRASSEN_SRC := $(SRC_DIR)/strassen.cpp

# Object files
MAIN_OBJ := $(BUILD_DIR)/main.o
TEST_OBJ := $(BUILD_DIR)/tests.o
BENCH_OBJ := $(BUILD_DIR)/benchmark.o
MATRIX_OBJ := $(BUILD_DIR)/matrix.o
STRASSEN_OBJ := $(BUILD_DIR)/strassen.o

# Default target
all: release

# Release build (optimized)
release: CXXFLAGS += -O3
release: $(BIN)

# Debug build
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(BIN)

# Build main binary
$(BIN): $(MAIN_OBJ) $(MATRIX_OBJ) $(STRASSEN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Build test binary
test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_OBJ) $(MATRIX_OBJ) $(STRASSEN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Debug build for tests
test_debug: CXXFLAGS += $(DEBUG_FLAGS)
test_debug: $(TEST_BIN)
	./$(TEST_BIN)

# Build benchmark binary
benchmark: $(BENCH_BIN)
	./$(BENCH_BIN)

$(BENCH_BIN): $(BENCH_OBJ) $(MATRIX_OBJ) $(STRASSEN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(BIN) $(TEST_BIN) $(BENCH_BIN)

.PHONY: all release debug clean test test_debug benchmark
