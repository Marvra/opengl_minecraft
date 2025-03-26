# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -std=c++17 -Iexternal/glad/include -Iexternal/stb/src

# Libraries
LDFLAGS := -lGL -lglfw

# Directories
SRC_DIR := src
GLAD_DIR := external/glad
STB_DIR := external/stb
BIN_DIR := bin

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp) $(GLAD_DIR)/src/glad.c $(STB_DIR)/src/stb.cpp
OBJS := $(SRCS:.cpp=.o)
OBJS := $(OBJS:.c=.o)

# Output
TARGET := $(BIN_DIR)/main

# Default rule
all: $(TARGET)

# Compile the executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile C++ source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C source files (for glad.c)
%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create bin directory if not exists
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean build files
clean:
	rm -rf $(SRC_DIR)/*.o $(GLAD_DIR)/src/*.o  $(STB_DIR)/src/*.o $(TARGET)

# Run the program
run: all
	./$(TARGET)

