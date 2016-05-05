polar: polarmain.o polarfn.o
	gcc polarmain.o polarfn.o -lm -o polar

polarmain.o: polarmain.c polarfn.h
	gcc -c polarmain.c

polarfn.o: polarfn.c
	gcc -c polarfn.c

clean:
	rm *.o polar 

