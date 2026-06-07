CC:=gcc
BUILDDIR:=build
TARGET:=$(BUILDDIR)/maze
CFLAGS:=-O2
LFLAGS:=-lGL -lm -lpthread -ldl -lrt -lX11

SRC:=$(wildcard src/*.c)
OBJ:=$(patsubst src/%.c, $(BUILDDIR)/%.o, $(SRC))

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p build
	$(CC) $^ libs/libraylib.a $(LFLAGS) -o $@

$(BUILDDIR)/%.o: src/%.c
	@mkdir -p build
	$(CC) -c $< $(CFLAGS) -o $@

.PHONY: run
run: all
	$(TARGET)

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)
