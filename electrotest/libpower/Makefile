CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror -pedantic -g
LFLAGS=-lpower -Wl,-rpath,.
OBJS=power.o
LIB=libpower.so
BIN=testpower
DIR=lib
DEST_LIB=/usr/lib
DEST_BIN=/usr/bin


all:		$(LIB) $(BIN)

lib:		$(LIB)

install:
		install -m 755 ./$(DIR)/$(LIB) $(DEST_LIB)/$(LIB)
		install -m 755 $(BIN) $(DEST_BIN)/$(BIN)

uninstall:
		rm -f $(DEST_LIB)/$(LIB)
		rm -f $(DEST_BIN)/$(BIN)

$(LIB):		$(OBJS)
		$(CC) $(CFLAGS) -shared -fPIC -o $@ $(OBJS)
		mkdir -p $(DIR)
		mv $(LIB) $(DIR)

$(BIN):		testpower.o
		$(CC) $(CFLAGS) -o $@ $@.c -L./$(DIR) $(LFLAGS)/$(DIR)

testpower.o:	power.o
		$(CC) $(CFLAGS) -c -fPIC $*.c

power.o:	power.c power.h
		$(CC) $(CFLAGS) -c -fPIC $*.c

clean:
		rm -rf *.o lib testpower

