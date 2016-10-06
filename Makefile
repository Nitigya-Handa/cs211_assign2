all: calc format

calc: calc.o calcfunc.o
	gcc -Wall -Werror -g -o calc calc.o calcfunc.o -lm

calc.o: calc.c calcfunc.h
	gcc -Wall -Werror -c -g calc.c

calcfunc.o: calcfunc.c
	gcc -Wall -Werror -c -g calcfunc.c -lm

format: format.o formfunc.o
	gcc -Wall -Werror -g -o format format.o formfunc.o -lm

format.o: format.c formfunc.h
	gcc -Wall -Werror -c -g format.c

formfunc.o: formfunc.c
	gcc -Wall -Werror -c -g formfunc.c -lm

clean:
	rm -f *.o calc format
