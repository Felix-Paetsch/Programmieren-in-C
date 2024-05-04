#!/use/bin/make
.PHONY: all pack clean

SRC = $(wildcard aufgabe1/*.c aufgabe2/*.c)
OBJ = $(SRC:%.c=%.o)
TAR = $(SRC:%.c=%)
PCK = abgabe.zip

CFLAGS = -std=c11 -Wall

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

%: %.o

all: $(TAR)

pack:
	zip -vr $(PCK) aufgabe1 aufgabe2 aufgaben.md -i "*.c" -i "*.h" -i "*.md"

clean:
	$(RM) $(RMFILES) $(TAR) $(PCK) $(OBJ)
