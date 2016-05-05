newpolar: newpolarmain.o newpolarfn.o
	gcc newpolarmain.o newpolarfn.o -lm -o newpolar

newpolarmain.o: newpolarmain.c newpolarfn.h
	gcc -c newpolarmain.c -o newpolarmain.o

newpolarfn.o: newpolarfn.c
	gcc -c newpolarfn.c -o newpolarfn.o

clean:
	rm *.o newpolar 
