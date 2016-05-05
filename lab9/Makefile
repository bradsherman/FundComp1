CFLAGS = -lm -lX11

all: fractals gallery

fractals: fractals.c
	gcc fractals.c gfx4.o -o fractals $(CFLAGS)
gallery: gallery.c
	gcc gallery.c gfx4.o -o gallery $(CFLAGS)
clean:
	rm fractals.o fractals gallery.o gallery
