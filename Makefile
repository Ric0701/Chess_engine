# Compiler
CC = gcc

# Target executable name
TARGET = Mystery.exe

# Source files
SRC = Mystery.c init.c bitboard.c hashKeys.c board.c data.c moveLogic.c

# Performance tuning
PERF = -O2

# Debug flags
DEBUGFLAGS = -g -DDEBUG

# Default rule to build the executable
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(PERF)

# Build with debug info and define DEBUG
debug:
	$(CC) $(SRC) -o $(TARGET) $(DEBUGFLAGS)

# Clean rule to remove compiled files
clean:
	rm -f $(TARGET)