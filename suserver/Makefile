CC	= g++

CFILES  = main.cpp ../api/player.pb.cc ../api/Network.cpp ../api/Thread.cpp ../api/Core.cpp

EXEC 	= main

OBJS	= main.o Network.o Thread.o Core.o

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

