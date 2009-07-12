CC	= g++

CFILES  = main.cpp player.pb.cc

EXEC 	= main

OBJS	= main.o player.pb.o

LINKER = -lGL -lXxf86vm -lXext -lX11

LIB = -lIrrlicht -lprotoc

INCLUDE = -L/usr/X11R6/lib

all: cfiles compile clean

cfiles: $(CFILES)
	$(CC) -c $(CFILES)

compile: $(OBJS)
	$(CC) -o $(EXEC) $(CFILES) $(LIB) $(INCLUDE) $(LINKER)

clean:
	rm -f $(OBJS)

