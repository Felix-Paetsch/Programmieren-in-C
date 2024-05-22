#!/use/bin/make
.SUFFIXES:
.PHONY: all pack clean

TAR = strings bitset
PCK = abgabe.zip

STR_SRC = $(wildcard aufgabe2/*.c)
STR_OBJ = $(STR_SRC:%.c=%.o)
STR_DEP = $(STR_SRC:%.c=%.d)

BIT_SRC = $(wildcard aufgabe3/*.c)
BIT_OBJ = $(BIT_SRC:%.c=%.o)
BIT_DEP = $(BIT_SRC:%.c=%.d)

CFLAGS = -std=c11 -Wall -MMD -MP
-include $(STR_DEP) $(BIT_DEP)

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

strings: $(STR_OBJ)
	$(CC) -o $@ $^

bitset: $(BIT_OBJ)
	$(CC) -o $@ $^

all: $(TAR)

pack:
	zip -vr $(PCK) aufgabe1 aufgabe2 aufgaben.md -i "*.c" -i "*.h" -i "*.md"

clean:
	$(RM) $(RMFILES) $(TAR) $(PCK) $(STR_OBJ) $(STR_DEP) $(BIT_OBJ) $(BIT_DEP)
