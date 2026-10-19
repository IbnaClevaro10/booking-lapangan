CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic
TARGET := ucl
SOURCES := src/main.cpp src/pertandingan.cpp

.PHONY: all run clean
ji

all: $(TARGET)

$(TARGET): $(SOURCES) include/struktur.h include/pertandingan.h
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	@if exist "$(TARGET).exe" del /Q "$(TARGET).exe"
	@if exist "$(TARGET)" del /Q "$(TARGET)"
