CC = gcc

#DIR used
BIN = ./bin/
BUILD = ./build/
SRC = ./src/
INCLUDE = ./include/

CFLAGS = -g -std=c11 -I$(INCLUDE)
OBJ = $(BIN)String.o $(BIN)Array.o $(BIN)List.o

#Builds .so and places it in build
build : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -shared -fpic -o $(BUILD)cstring.so

#installs to /usr/lib/
#might need super user
install: build
	cp $(BUILD)cstring.so /usr/lib/
	cp $(INCLUDE)String.h /usr/include/cstring.h
$(BIN)String.o: $(SRC)String.c $(INCLUDE)String.h
	$(CC) $(CFLAGS) -c $(SRC)String.c

license:
	cat license
