all: sem-pc sem-rw sem-dining sem-barn monitor-bank monitor-pc monitor-barn

sem-pc: sem-pc.c
	gcc -Wall -g sem-pc.c -o sem-pc -pthread

sem-rw: sem-rw.c
	gcc -Wall -g sem-rw.c -o sem-rw -pthread

sem-dining: sem-dining.c
	gcc -Wall -g sem-dining.c -o sem-dining -pthread

sem-barn: sem-barn.c
	gcc -Wall -g sem-barn.c -o sem-barn -pthread

monitor-bank: monitor-bank.c
	gcc -Wall -g monitor-bank.c -o monitor-bank -pthread

monitor-barn: monitor-barn.c
	gcc -Wall -g monitor-barn.c -o monitor-barn -pthread

monitor-pc: monitor-pc.c
	gcc -Wall -g monitor-pc.c -o monitor-pc -pthread

clean:
	rm -f sem-pc sem-rw sem-barn sem-dining monitor-bank monitor-pc
