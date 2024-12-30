# Compiler and flags
CXX = g++  # You can replace this with the full path if needed
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
STATIC_LIB = libWifiSimulator.a  # Name of the static library
EXECUTABLE = WiFiSimulator.exe    # Name of the executable

# Source and object files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Ensure build directory exists
$(shell mkdir -p $(BUILD_DIR))

# Default target
all: $(BUILD_DIR)/$(EXECUTABLE)

# Create the executable by linking the static library and object files
$(BUILD_DIR)/$(EXECUTABLE): $(OBJECTS) $(BUILD_DIR)/$(STATIC_LIB)
	$(CXX) $(CXXFLAGS) -o $@ $^ -L$(BUILD_DIR) -lWifiSimulator

# Create static library from object files
$(BUILD_DIR)/$(STATIC_LIB): $(OBJECTS)
	ar rcs $@ $^

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean build files
clean:
ifeq ($(OS),Windows_NT)
	del /q $(BUILD_DIR)\* 2>nul
else
	rm -rf $(BUILD_DIR)/*
endif

# Debug build
debug: CXXFLAGS += -g
debug: clean all

# Optimized build
optimized: CXXFLAGS += -O3
optimized: clean all

.PHONY: all clean debug optimized
