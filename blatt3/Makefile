#!/usr/bin/make
.SUFFIXES:
.PHONY: all pack clean

TAR = simplify stackvec expr
PCK = abgabe.zip

SIM_SRC = $(wildcard aufgabe2/*.c)
SIM_OBJ = $(SIM_SRC:%.c=%.o)
SIM_DEP = $(SIM_SRC:%.c=%.d)

VEC_SRC = $(wildcard aufgabe3/*.c)
VEC_OBJ = $(VEC_SRC:%.c=%.o)
VEC_DEP = $(VEC_SRC:%.c=%.d)

EXP_SRC = $(wildcard aufgabe4/*.c)
EXP_OBJ = $(EXP_SRC:%.c=%.o)
EXP_DEP = $(EXP_SRC:%.c=%.d)

CFLAGS = -std=c11 -Wall -MMD -MP
-include $(SIM_DEP) $(VEC_DEP) $(EXP_DEP)

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

simplify: $(SIM_OBJ)
	$(CC) -o $@ $^

stackvec: $(VEC_OBJ)
	$(CC) -o $@ $^

expr: $(EXP_OBJ)
	$(CC) -o $@ $^

all: $(TAR)

pack:
	zip -vr $(PCK) aufgabe2 aufgabe3 aufgabe4 aufgaben.md -i "*.c" -i "*.h" -i "*.md"

clean:
	$(RM) $(RMFILES) $(TAR) $(PCK) $(SIM_OBJ) $(SIM_DEP) $(VEC_OBJ) $(VEC_DEP) $(EXP_OBJ) $(EXP_DEP)
