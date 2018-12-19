# Based on https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/

CC = clang++
CFLAGS = -std=c++11 -Wall -Wshadow -Werror
SRCDIR = src
BUILDDIR = build
TARGETDIR = bin
TARGET = $(TARGETDIR)/napkin

SRCEXT = cpp
# Find all regular files in source directory with extenstion SRCEXT
# must use shell since find is not a make function, but a shell program
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
# To get a list of object files, replace SRCDIR with BUILDDIR and replace
# SRCEXT with .o
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# Takes all .o files as prerequisites and links everything into TARGET
$(TARGET): $(OBJECTS)
	mkdir -p $(TARGETDIR)
	$(CC) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -r $(BUILDDIR)
	-rm -r $(TARGET)
