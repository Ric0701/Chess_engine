# Compiler
CC = gcc

# Target executable name
TARGET = Mystery.exe

# Source files
SRC = Mystery.c init.c

# Performance tuning
PERF = -O2

# Default rule to build the executable
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(PERF)

# Clean rule to remove compiled files
clean:
	rm -f $(TARGET)