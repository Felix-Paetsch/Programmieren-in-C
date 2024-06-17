#!/usr/bin/make
.SUFFIXES:
.PHONY: all pack clean

TAR = gc vec
PCK = abgabe.zip

GC_SRC = $(wildcard aufgabe2/*.c)
GC_OBJ = $(GC_SRC:%.c=%.o)
GC_DEP = $(GC_SRC:%.c=%.d)

VEC_SRC = $(wildcard aufgabe3/*.c)
VEC_OBJ = $(VEC_SRC:%.c=%.o)
VEC_DEP = $(VEC_SRC:%.c=%.d)

CFLAGS = -std=c11 -Wall -MMD -MP
-include $(GC_DEP) $(VEC_DEP)

# rule for compiling a single source file
%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

gc: $(GC_OBJ)
	$(CC) -o $@ $^

vec: $(VEC_OBJ)
	$(CC) -o $@ $^

all: $(TAR)

pack:
	zip -vr $(PCK) aufgabe2 aufgabe3 aufgaben.md -i "*.c" -i "*.h" -i "*.md"

clean:
	$(RM) $(RMFILES) $(TAR) $(PCK) $(GC_OBJ) $(GC_DEP) $(VEC_OBJ) $(VEC_DEP)
