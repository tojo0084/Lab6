CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror -pedantic -g
LDFLAGS=-lpower -lresistance -lcomponent -lm
DIR=lib
LIBS=$(addprefix $(DIR)/,libpower.so libresistance.so libcomponent.so)
BIN=electrotest
DEST_LIB=/usr/local/lib
DEST_BIN=/usr/local/bin

.PHONY: all clean install uninstall

all: $(LIBS) $(BIN)

clean:
	rm -rf *.o lib electrotest

install:
	install -m 755 $(DIR)/*.so $(DEST_LIB)
	install -m 755 $(BIN) $(DEST_BIN)
	@ldconfig

uninstall:
	rm -f $(DEST_LIB)/libpower.so
	rm -f $(DEST_LIB)/libresistance.so
	rm -f $(DEST_LIB)/libcomponent.so
	rm -f $(DEST_BIN)/$(BIN)

$(DIR): 
	mkdir -p $(DIR)

$(BIN): electrotest.o
	$(CC) $(CFLAGS) -o $@ $^ -L$(DIR) $(LDFLAGS)

$(DIR)/libpower.so: ../libpower/power.c ../libpower/power.h | $(DIR)
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^

$(DIR)/libresistance.so: ../libresistance/src/libresistance.c ../libresistance/src/libresistance.h | $(DIR)
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^

$(DIR)/libcomponent.so: ../libcomponent/main/libcomponent.c ../libcomponent/main/libcomponent.h | $(DIR)
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^

electrotest.o: main/electrotest.c main/electrotest.h
	$(CC) -I../libresistance/src -I../libcomponent/main -I../libpower $(CFLAGS) -c $<
