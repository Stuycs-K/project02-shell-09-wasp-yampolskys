.PHONY: compile clean
compile: main.o
	gcc -o shell main.o -Wall
main.o: main.c
	gcc -c main.c -Wall
# insert files here (I need to consider what files to make/add)
clean:
	rm -f *.o
	rm -f shell
