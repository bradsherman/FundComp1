CFLAGS = -lm -lX11 -Wall

final: finalmain.o finalfunc.o gfx5.o
	gcc finalmain.o finalfunc.o gfx5.o gfxe.o -o final $(CFLAGS)

finalmain.o: finalmain.c finalfunc.h
	gcc -c finalmain.c $(CFLAGS)

finalfunc.o: finalfunc.c finalfunc.h
	gcc -c finalfunc.c $(CFLAGS)

gfx5.o: gfx5.c
	gcc -c gfx5.c $(CFLAGS)

clean:
	rm final finalmain.o gfx5.o finalfunc.o 
