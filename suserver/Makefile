CC	= g++

CFILES  = main.cpp ../api/Network.cpp ../api/Thread.cpp

EXEC 	= main

OBJS	= main.o Network.o Thread.o

LINKER = -lGL -lXxf86vm -lXext -lX11 -lpthread

LIB = -lIrrlicht -lprotoc

INCLUDE = -L/usr/X11R6/lib

all: cfiles compile clean

cfiles: $(CFILES)
	$(CC) -c $(CFILES)

compile: $(OBJS)
	$(CC) -g -o $(EXEC) $(CFILES) $(LIB) $(INCLUDE) $(LINKER)

clean:
	rm -f $(OBJS)

