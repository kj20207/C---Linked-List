all: list

list: list.c list.h
	gcc list.c -o list

clean:
	rm list