OPTIONS=--std=c99 -Wall -g

bcache: bcache.o main.o disk.o program.o
	gcc ${OPTIONS} bcache.o main.o disk.o program.o -lpthread -obcache

main.o: main.c bcache.h disk.h
	gcc ${OPTIONS} -c main.c -o main.o

program.o: program.c program.h
	gcc ${OPTIONS} -c program.c -o program.o

bcache.o: bcache.c bcache.h
	gcc ${OPTIONS} -c bcache.c -o bcache.o

disk.o: disk.c disk.h
	gcc ${OPTIONS} -c disk.c -o disk.o

clean:
	rm -f bcache *.o

