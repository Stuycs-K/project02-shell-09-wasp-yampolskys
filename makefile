.PHONY: compile clean
compile: main.o parse.o
	gcc -o shell main.o parse.o -Wall
parse.o: parse.c
	gcc -c parse.c -Wall
main.o: main.c parse.h
	gcc -c main.c -Wall
# insert files here (I need to consider what files to make/add)
clean:
	rm -f *.o
	rm -f shell
