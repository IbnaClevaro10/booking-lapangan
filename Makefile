CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic
TARGET := ucl
SRC_DIR := src
OBJ_DIR := build

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
HEADERS := $(wildcard include/*.h)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	$(CXX) $(CXXFLAGS) -Iinclude -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	@if exist "$(TARGET).exe" del /Q "$(TARGET).exe"
	@if exist "$(TARGET)" del /Q "$(TARGET)"
	@if exist "$(OBJ_DIR)" rmdir /S /Q "$(OBJ_DIR)"
