CFLAGS= -Wall -O1 -g

all: main.o steamGames.o
	gcc main.o steamGames.o -o steamGames

main.o: main.c
	gcc -c main.c $(CFLAGS)

steamGames.o: steamGames.c
	gcc -c steamGames.c $(CFLAGS)

clean:
	rm -fr *.o
