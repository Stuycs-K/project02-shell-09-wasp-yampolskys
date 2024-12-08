.PHONY: compile clean
compile: main.o parse.o cd.o redirect.o
	gcc -o shell main.o parse.o redirect.o cd.o -Wall
redirect.o: redirect.c redirect.h
	gcc -c redirect.c -Wall
parse.o: parse.c parse.h
	gcc -c parse.c -Wall
cd.o: cd.c cd.h
	gcc -c cd.c -Wall
main.o: main.c parse.h cd.h
	gcc -c main.c -Wall
# insert files here (I need to consider what files to make/add)
clean:
	rm -f *.o
	rm -f shell
