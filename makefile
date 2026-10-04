all:
	@mkdir -p bin
	gcc -Wall -Wextra -g src/main.c -o bin/cclock

run: all
	./bin/cclock

clean:
	rm -f bin/cclock

.PHONY: all run clean
