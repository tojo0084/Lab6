# Tre krav på targets enligt nedan:
# "lib"  för att bygga enbart biblioteket.
# "all"  För att bygga både programmet och biblioteken där biblioteken läggs i en egen katalog, lib,  under den man är jus nu, tex /home/bl/electro/lib/. Här ska programmet länkas för att använda de lokala biblioteken. OBS! Ni får inte temporärt ändra libsökvägarna i LD_LIBRARY_PATH!
# "install" Här kopierar du både programmet och biblioteken till lämpliga kataloger (tex /usr/bin/ och /usr/lib/) och länkar så att programmet använder de publika biblioteken.
# Dessutom lämpligt med följande:
# "test" är egentligen inte ett krav men kan i det här fallet vara "programmet" dvs "all" ovan, med andra ord: "all" medför både "test" och "lib"
# Desutom har jag lagt till target "uninstall"

# Tomas Johansson

all: lib test


lib: build/obj lib/libcomponent.so


build/obj:
	mkdir -p build/obj

lib/libcomponent.so: build/obj/libcomponent.o
	mkdir -p lib
	gcc -shared -fPIC -o lib/libcomponent.so build/obj/libcomponent.o
#	ar crv lib/libcomponent.a build/obj/libcomponent.o

build/obj/libcomponent.o: main/libcomponent.c main/libcomponent.h
	gcc -c -fPIC main/libcomponent.c -o build/obj/libcomponent.o


test: build/obj build/libcomponent_tests
	./build/libcomponent_tests

build/libcomponent_tests: build/obj/unity.o build/obj/libcomponent.o build/obj/libcomponent_tests.o
	gcc build/obj/unity.o build/obj/libcomponent.o build/obj/libcomponent_tests.o -lm -o build/libcomponent_tests

build/obj/unity.o:
	gcc -c test/unity/unity.c -o build/obj/unity.o

build/obj/libcomponent_tests.o:
	gcc -c test/libcomponent_tests.c -o build/obj/libcomponent_tests.o



clean:
	rm -f lib/* build/libcomponent_tests build/obj/*.*


install: lib/libcomponent.so build/libcomponent_tests
	sudo cp lib/libcomponent.so /usr/local/lib/
	sudo cp build/libcomponent_tests /usr/local/bin/
#	ln -s /usr/local/bin/libcomponent_tests ./libcomponent_tests
# ToDo: I vilken katalog ska länken placeras ?
# "install. Här kopierar du både programmet och biblioteken till lämpliga kataloger (tex /usr/bin/ och /usr/lib/) och länkar så att programmet använder de publika biblioteken."
uninstall:
	sudo rm -f /usr/local/lib/libcomponent.so /usr/local/bin/libcomponent_tests
#	rm -f ./libcomponent_tests
