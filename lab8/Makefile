CFLAGS = -lm -lX11

all: graphcalc carnival

graphcalc: graphcalc.c
	gcc graphcalc.c gfx2.o -o graphcalc $(CFLAGS)
carnival: carnival.c
	gcc carnival.c gfx2.o -o carnival $(CFLAGS)
clean:
	rm carnival.o graphcalc.o carnival graphcalc
