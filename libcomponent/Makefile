# Tomas Johansson
# tojo0084@gapps.umu.se
# 2017-05-14
# Bibliotek 3, libcomponent.so

CFLAGS=-std=c11

.PHONY: test

test: build/obj build/libcomponent_tests
	build/libcomponent_tests

build/obj:
	mkdir -p build/obj

build/libcomponent_tests: build/obj/unity.o build/obj/libcomponent.o build/obj/libcomponent_tests.o
	gcc $(CFLAGS) build/obj/unity.o build/obj/libcomponent.o build/obj/libcomponent_tests.o -lm -o $@

build/obj/unity.o: build/obj
	gcc $(CFLAGS) -c test/unity/unity.c -o $@

build/obj/libcomponent.o: build/obj main/libcomponent.c main/libcomponent.h
	gcc $(CFLAGS) -c -fPIC main/libcomponent.c -o $@

build/obj/libcomponent_tests.o: build/obj
	gcc $(CFLAGS) -c test/libcomponent_tests.c -o $@
