CC=gcc
CFLAGS=-Wall -g -ansi -pedantic -Isrc

SRCDIR = src
BINDIR = bin

# Find all .c files in the src directory
SOURCES = $(wildcard $(SRCDIR)/*.c)

# Create object file names by replacing .c with .o and prepending the bin directory
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%.o,$(SOURCES))

EXEC = $(BINDIR)/security_program

all: $(EXEC)

$(EXEC): $(OBJECTS)
# Create bin directory if it doesn't exist
	@mkdir -p $(@D) 
	$(CC) $(OBJECTS) -o $@

# Compile source files into object files
$(BINDIR)/%.o: $(SRCDIR)/%.c
# Create bin directory if it doesn't exist
	@mkdir -p $(@D) 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BINDIR)

runval: all
	valgrind ./$(EXEC) $(PARAMS)

.PHONY: all clean runval
