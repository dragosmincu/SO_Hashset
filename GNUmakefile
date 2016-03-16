build: main.o list.o hashset.o hash.o
	gcc -Wall main.o list.o hashset.o hash.o -o tema1

list.o: list.c
main.o: main.c
hash.o: hash.c
hashset.o: hashset.c

.PHONY: clean
clean:
	rm -rf *.o tema1

