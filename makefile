CC = gcc

#DIR used
BIN = ./bin/
BUILD = ./build/
SRC = ./src/
INCLUDE = ./include/
TEST = ./test/

CFLAGS = -g -std=c11 -I$(INCLUDE)
OBJ = $(BIN)String.o $(BIN)Array.o $(BIN)LinkedList.o

#Builds .so and places it in build
build : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -shared -fpic -o $(BUILD)libcstring.so

#installs to /usr/lib/
#might need super user
install: build
	cp $(BUILD)libcstring.so /usr/lib/
	cp $(INCLUDE)String.h /usr/include/cstring.h
	cp $(INCLUDE)Array.h /usr/include/
	cp $(INCLUDE)LinkedList.h /usr/include/
$(BIN)String.o: $(SRC)String.c $(INCLUDE)String.h
	$(CC) $(CFLAGS) -fpic -c $(SRC)String.c -o $@
$(BIN)Array.o: $(SRC)Array.c $(INCLUDE)Array.h
	$(CC) $(CFLAGS) -c $(SRC)Array.c -o $@
$(BIN)LinkedList.o: $(INCLUDE)LinkedList.h $(SRC)LinkedList.c
	$(CC) $(CFLAGS) -c $(SRC)LinkedList.c -o $@

#testfiles
test: build $(BIN)test.o
	$(CC) $(CFLAGS) $(BIN)test.o -L$(BUILD) -lcstring -o $(BUILD)$@

	#run program
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(BUILD) $(BUILD)test

#testfiles memory test
memtest: build $(BIN)test.o
	#set library paths for c compiler
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(BUILD);
	$(CC) $(CFLAGS) $(BIN)test.o -L$(BUILD) -lcstring -o $(BUILD)$@

	#run program
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(BUILD) valgrind  --leak-check=full $(BUILD)memtest

$(BIN)test.o: $(TEST)stringTest.c
	$(CC) $(CFLAGS) -c $(TEST)stringTest.c -o $@
license:
	cat license

clean:
	rm -rf $(BIN)* $(BUILD)*
