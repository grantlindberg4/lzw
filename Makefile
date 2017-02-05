CC = gcc
CFLAGS = -std=c99 -Wall -Wpedantic -g
OBJS := $(addprefix build/,seq.o dict.o)

.DEFAULT: all

.PHONY: all

all: build/lzw

.PHONY: test

test: build/lzw_test

build:
	mkdir -p build

$(OBJS): | build

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

build/lzw: $(OBJS) build/main.o
	$(CC) $(CFLAGS) $^ -o $@

build/lzw_test: $(OBJS) build/test.o
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -rf ./build/

.PHONY: install

install: build/lzw
	cp build/lzw /encs_share/cs/class/cs360/bin
