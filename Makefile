# Compiler and flags
CXX = g++
CXXFLAGS = $(shell sdl2-config --cflags) -lSDL2_image -lSDL2_ttf $(shell sdl2-config --libs)

# Target executable
TARGET = tictactoe

# Source files
SRCS = $(wildcard *.cpp)

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Build the target
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
