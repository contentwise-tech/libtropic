# Define compiler and archiver
CC = gcc
AR = ar
ARFLAGS = rcs
# Define flags for compilation: -Wall for warnings, -c to compile only (no linking)
# TODO: -Wall
CFLAGS = -Wall -c -I../../include -I../../src
#CFLAGS = -c

# Define the name of the static library file (convention is lib*.a)
LIBNAME = libltmbedtls.a

# List of source files for the library
LIBSOURCES = $(wildcard *.c)

# List of object files for the library (generated from source files)
LIBOBJECTS = $(LIBSOURCES:.c=.o)

all: $(LIBNAME)

# Rule to build the static library
$(LIBNAME): $(LIBOBJECTS)
	$(AR) $(ARFLAGS) $@ $^

# Rule to compile library source files into object files
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
# Rule to clean up generated files
clean:
	rm -f $(LIBNAME) $(LIBOBJECTS)

