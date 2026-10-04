CC      = gcc
CFLAGS  = -Wall -Wextra -g -Isrc
LDLIBS  = -lncurses

SRC     = src/main.c src/clock.c src/aux.c src/ui.c src/help.c
OUT     = bin/cclock

all: $(OUT)

$(OUT): $(SRC)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDLIBS)

clean:
	rm -f $(OUT)

.PHONY: all clean
