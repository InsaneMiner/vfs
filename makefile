CC=gcc
SRC=./src
CFLAGS=-I./include -g3 -Wall -Wextra
LDFLAGS=-g3 -Wall -Wextra -I./include
TARGET=vfs
BUILDDIR=bin

CSOURCES=$(shell find $(SRC) -name '*.c')
OBJECTS = $(patsubst $(SRC)/%.c, $(BUILDDIR)/%.o, $(CSOURCES))

.PHONY: all


all: build

build: dirs $(OBJECTS) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS)  main.c -o $(TARGET)

$(BUILDDIR)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-@rm -rf $(OBJECTS) $(TARGET) $(BUILDDIR)

dirs:
	@mkdir -p $(BUILDDIR)
	@cd $(SRC) \
	&& dirs=$$(find -type d) \
	&& cd ../$(BUILDDIR) \
	&& mkdir -p $$dirs

run: build
	./$(TARGET)
