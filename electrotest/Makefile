CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror -pedantic -g
LFLAGS=-lpower -lresistance -lcomponent -Wl,-rpath,.
OBJS=power.o resistance.o component.o
LIBS=libpower.so libresistance.so libcomponent.so
BIN=electrotest
DIR=lib
DEST_LIB=/usr/local/lib
DEST_BIN=/usr/local/bin


#.PHONY: all clean install uninstall

all: lib $(BIN)

clean:
	rm -rf *.o lib electrotest

install:
	install -m 755 ./$(DIR)/*.so $(DEST_LIB)/$(LIB)
	install -m 755 $(BIN) $(DEST_BIN)

uninstall:
	rm -f $(DEST_LIB)/libpower.so
	rm -f $(DEST_LIB)/libresistance.so
	rm -f $(DEST_LIB)/libcomponent.so
	rm -f $(DEST_BIN)/$(BIN)

lib: $(LIBS)
	mkdir -p $(DIR)
	mv *.so $(DIR)

$(BIN): electrotest.o
	$(CC) $(CFLAGS) -o $@ main/$@.c -L./$(DIR) $(LFLAGS)/$(DIR) -lm

libpower.so: power.o
	$(CC) $(CFLAGS) -shared -fPIC -o $@ power.o

libresistance.so: resistance.o
	$(CC) $(CFLAGS) -shared -fPIC -o $@ resistance.o

libcomponent.so: component.o
	$(CC) $(CFLAGS) -shared -fPIC -o $@ component.o

electrotest.o: $(OBJS)
	$(CC) $(CFLAGS) -c -fPIC main/$*.c

power.o: libpower/src/power.c libpower/src/power.h
	$(CC) $(CFLAGS) -c -fPIC libpower/src/$*.c

resistance.o: libresistance/src/resistance.c libresistance/src/resistance.h
	$(CC) $(CFLAGS) -c -fPIC libresistance/src/$*.c

component.o: libcomponent/main/component.c libcomponent/main/component.h
	$(CC) $(CFLAGS) -c -fPIC libcomponent/main/$*.c -lm
