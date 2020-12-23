#compiler
CC = g++

#target
TARGET = server

#directories, source, inculde, target, object
SRCDIR = src
INCDIR = include
BUILDDIR = obj
TARGETDIR = target

#includes
INC = -I$(INCDIR)
OBJ = -L$(BUILDDIR)

VPATH = src

#-------------------------------------------------------------
#-------------------------------------------------------------

all: directory $(TARGET)

directory: 
	mkdir $(TARGETDIR)
	mkdir $(BUILDDIR)

$(TARGET): server.o parser.o get_handler.o
	$(CC) $(OBJ) ./obj/server.o ./obj/parser.o ./obj/get_handler.o -o ./target/server

server.o: server.cpp include/parser.h include/get_handler.h
	$(CC) $(INC) -c ./src/server.cpp -o ./obj/server.o 

parser.o: parser.cpp include/parser.h
	$(CC) $(INC) -c ./src/parser.cpp -o ./obj/parser.o

get_handler.o: get_handler.cpp include/get_handler.h
	$(CC) $(INC) -c ./src/get_handler.cpp -o ./obj/get_handler.o

clean:
	rm -r $(BUILDDIR)
	rm -r $(TARGETDIR)	
