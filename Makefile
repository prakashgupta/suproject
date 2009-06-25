CC	= g++

CFILES  = main.cpp

OBJS	= main.o
LINKER = -lGL -lXxf86vm -lXext -lX11
LIB = -lIrrlicht
INCLUDE = -L/usr/X11R6/lib
all: cfiles compile clean

cfiles: $(CFILES)
	$(CC) -c $(CFILES)

compile: $(OBJS)
	$(CC) -o main $(CFILES) $(LIB) $(INCLUDE) $(LINKER)

clean:
	rm -f $(OBJS)

