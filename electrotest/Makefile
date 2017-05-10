CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror -pedantic -g
LDFLAGS=-lpower -lresistance -lcomponent -lm
LIB_DIR=lib
OBJ_DIR=obj
LIBS=$(addprefix $(LIB_DIR)/,libpower.so libresistance.so libcomponent.so)
BIN=electrotest
DEST_LIB_DIR=/usr/local/lib
DEST_BIN_DIR=/usr/local/bin

.PHONY: all clean install uninstall

all: $(LIBS) $(BIN)

clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR) electrotest

install:
	install -m 755 $(LIB_DIR)/*.so $(DEST_LIB_DIR)
	install -m 755 $(BIN) $(DEST_BIN_DIR)
	@ldconfig

uninstall:
	rm -f $(DEST_LIB_DIR)/libpower.so
	rm -f $(DEST_LIB_DIR)/libresistance.so
	rm -f $(DEST_LIB_DIR)/libcomponent.so
	rm -f $(DEST_BIN_DIR)/$(BIN)

$(LIB_DIR): 
	mkdir -p $(LIB_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN): $(OBJ_DIR)/electrotest.o
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIB_DIR) $(LDFLAGS) -Wl,-rpath,'$$ORIGIN/$(LIB_DIR)'

$(LIB_DIR)/libpower.so: ../libpower/power.c ../libpower/power.h | $(LIB_DIR)
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^

$(LIB_DIR)/libresistance.so: ../libresistance/src/libresistance.c ../libresistance/src/libresistance.h | $(LIB_DIR)
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^

$(LIB_DIR)/libcomponent.so: ../libcomponent/main/libcomponent.c ../libcomponent/main/libcomponent.h | $(LIB_DIR)
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^

$(OBJ_DIR)/electrotest.o: main/electrotest.c main/electrotest.h | $(OBJ_DIR)
	$(CC) -I../libresistance/src -I../libcomponent/main -I../libpower $(CFLAGS) -c -o $@ $<
