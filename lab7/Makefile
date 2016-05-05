CFLAGS = -lm -lX11
all: symbol bounce animate

symbol: symbol.c
	gcc symbol.c gfx.o -o symbol $(CFLAGS) 
bounce: bounce.c
	gcc bounce.c gfx.o -o bounce $(CFLAGS)
animate: animate.c
	gcc animate.c gfx2.o -o animate $(CFLAGS)
clean:
	rm symbol.o bounce.o animate.o symbol bounce animate
