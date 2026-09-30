all:
	gcc src/main.c -o bin/cclock

run: all
	./bin/cclock

clean:
	rm -f bin/cclock
