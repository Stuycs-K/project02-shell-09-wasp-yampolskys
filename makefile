.PHONY: compile clean
compile: main.o shellFunc.o
	gcc -o shell main.o shellFunc.o -Wall
shellFunc.o: shellFunc.c shellFunc.h
	gcc -c shellFunc.c -Wall
main.o: main.c shellFunc.h
	gcc -c main.c -Wall
clean:
	rm -f *.o
	rm -f shell
