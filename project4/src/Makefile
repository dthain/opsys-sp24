all: printersim

printersim: printersim.c
	gcc printersim.c gfx.c -o printersim -Wall -g -pthread -lX11 -lm

clean:
	rm -f printersim
