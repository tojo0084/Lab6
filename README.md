# Lab6
## Studenter
* Marcus Nordenberg (mano0333)
* Tomas Johansson (tojo0084)
* Ludvig Lundberg (lulu0011)

## Projektets kataloger och huvudprogrammets filer
Root-katalogen innehåller följande fyra underkataloger, varav de tre första är biblioteken som ska redovisas individuellt:
* libresistance (Bibliotek 1, Marcus)
* libpower (Biliotek 2, Ludvig)
* libcomponent (Bibliotek 3, Tomas)
* electrotest (huvudprogram, gemensamt)

Huvudprogrammet och biblioteken kompileras/länkas/installeras enligt regler i följande makefile:
electrotest/Makefile
Reglerna i den makefilen beskrivs i ett separat underavsnitt längre ner.

Huvudprogrammets källkod finns i följande fil:
electrotest/main/electrotest.c
Det framgår av kommentarer i den filen var de tre funktionerna i de tre biblioteken används.
Huvudprogrammets källkod kompileras/länkas inte till källkoden eller objektfilerna för de tre biblioteken.
Det länkas istället till de shared libraries (.so-filerna) som skapas när makefilen exekveras.

## Reglerna i huvudprogrammets makefile
Nedan beskrivs resultatet av att exekvera de tre reglerna "lib", "all" och "install" (dvs de tre regler som skall redovisas).
(detaljerna om växlarna som används i makefilen beskrivs längre ner i annat underavsnitt)

"make lib"
Kompilerar och länkar de tre biblioteken så att följande tre shared libraries skapas:
* electrotest/lib/libresistance.so
* electrotest/lib/libpower.so
* electrotest/lib/libcomponent.so

"make all"
Skapar de tre biblioteken (på samma sätt som "make lib" ovan) i lib-katalogen och dessutom en objektfil "obj/electrotest.o" och ett huvudprogram "electrotest" i samma katalog som makefilen.
Programmet som skapas kan exekveras från aktuella katalogen "electrotest" genom att skriva "./electrotest".
Om man från den katalogen skriver "ldd ./electrotest" kan man konstatera att biblioteksfilerna som programmet försöker använda är de tre lokala biblioteken dvs .so-filerna som ligger i lokala katalogen "electrotest/lib".
Om man raderar filerna i den lokala lib-katalogen och sedan skriver "ldd ./electrotest" kommer det istället framgå att programmet då försöker använda motsvarande filer i katalogen "/usr/local/lib/" om de existerar d.v.s. om "make install" (se nedan) har exekverats.

"make install"
När detta kommando exekveras blir resultatet att följande fyra filer skapas:
* /usr/local/lib/libresistance.so
* /usr/local/lib/libpower.so
* /usr/local/lib/libcomponent.so
* /usr/local/bin/electrotest
Electrotest-programmet i katalogen "/usr/local/bin" kan exekveras genom att skriva "electrotest" (d.v.s. utan prefixet "./" och oavsett aktuell katalog).
Om man skriver "ldd /usr/local/bin/electrotest") kan man konstatera att biblioteksfilerna som används är de tre publika biblioteken dvs .so-filerna som ligger i katalogen "/usr/local/lib"

När man exekverar kommandot "make install" måste man ha behörighet att skapa filer under katalogen "/usr/local".
Om man t.ex. använder Ubuntu kan man lösa det genom att använda kommandot "sudo make install".

## Gemensam redovisning av växlarna som används i huvudprogrammets makefile
Den gemensamma delen för att bygga electrotest använde följande Makefile.

```make
CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror -pedantic -g
LDFLAGS=-lpower -lresistance -lcomponent -lm
LIB_DIR=lib
OBJ_DIR=obj
LIBS=$(addprefix $(LIB_DIR)/,libpower.so libresistance.so libcomponent.so)
BIN=electrotest
DEST_LIB_DIR=/usr/local/lib
DEST_BIN_DIR=/usr/local/bin

.PHONY: all clean install uninstall lib createLibDirectory

all: lib $(BIN)

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

lib:	$(LIBS)

createLibDirectory:
	mkdir -p $(LIB_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN): $(OBJ_DIR)/electrotest.o
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIB_DIR) $(LDFLAGS) -Wl,-rpath,'$$ORIGIN/$(LIB_DIR)'

$(LIB_DIR)/libpower.so: ../libpower/src/power.c ../libpower/src/power.h | createLibDirectory
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^

$(LIB_DIR)/libresistance.so: ../libresistance/src/libresistance.c ../libresistance/src/libresistance.h | createLibDirectory
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^

$(LIB_DIR)/libcomponent.so: ../libcomponent/main/libcomponent.c ../libcomponent/main/libcomponent.h | createLibDirectory
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^

$(OBJ_DIR)/electrotest.o: main/electrotest.c main/electrotest.h | $(OBJ_DIR)
	$(CC) -I../libresistance/src -I../libcomponent/main -I../libpower/src $(CFLAGS) -c -o $@ $<
```
Nedan följer förklaringar kring de växlar vi valt att kompilera/länka med. Samt lite förklaringar kring variabler och tänk bakom dessa. Allt tas inte upp utan bara det som vi tycker behöver en viss förklaring.

`CC=gcc`  
Här anger vi explicit att CC ska peka på gcc istället för att förlita oss på att cc är symlänkat mot gcc som normalt är fallet.

`CFLAGS=-std=c11 -Wall -Wextra -Werror -pedantic -g`  
CFLAGS anger våra kompileringsflaggor.
* `-std=c11`
   Anger att vi vill vara "conformant" mot c11-standarden.
* `-Wall`
   Anger att vi vill ha varningar för alla kända vanliga missar ur programmeringsteknisk synpunkt.
   * `-Wextra`
   Anger att vi vill ha ytterligare varningar utöver de som ingår i flaggan -Wall
* `-Werror`
   Anger att vi vill att varningar skall behandlas som fel. Livet är hårt.
* `-pedantic`
   Ger varningar när vi inte följer strikt ISO C / ISO C++.
* `-g`
   Anger att vi vill ha debuginformation inbakat i våra objektsfiler.

`LDFLAGS=-lpower -lresistance -lcomponent -lm`  
LDFLAGS anger våra länkningsdirektiv.
* `-lpower`
   Ett av de mest kraftfulla biblioteken där ute. Vi länkar ju såklart mot libpower!
* `-lresistance`
   Det vore alldeles för lätt om vi inte hade något motstånd, så vi länkar mot libresistance också!
* `-lcomponent`
   Ordning och reda på våra komponenter. Vi länkar mot libcomponent för detta!
* `-lm`
   Vi länkar mot libm (matematiska funktioner).

`LIB_DIR=lib`  
Variabel för namnet på vår bibliotekskatalog.

`OBJ_DIR=obj`  
Variabel för namnet på vår katalog där vi petar in objektsfiler.

`LIBS=$(addprefix $(LIB_DIR)/,libpower.so libresistance.so libcomponent.so)`  
Här anger vi våra bibliotek i variabeln LIBS. Vi lägger till "lib/" framför alla bibliotek genom att använda $(addprefix).

`BIN=electrotest`  
Anger namnet på vår binärfil i variabeln BIN.

`DEST_LIB_DIR=/usr/local/lib`  
Variabel som håller sökvägen till där vi vill installera de dynamiska biblioteken.

`DEST_BIN_DIR=/usr/local/bin`  
Variabel som håller sökvägen till där vi vill installera vår binärfil.

`.PHONY: all clean install uninstall lib createLibDirectory`  
Vi anger här ett antal PHONY-regler som inte skall vara med att tolkas som filnamn utan mer som namn på recept vi vill peka ut. Ett bra exempel är här vårt target lib. Hade vi redan en katalog vid namn lib hade det varit up-to-date eftersom lib/ existerar. PHONY-target löser detta.

`install:`  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`install -m 755 $(LIB_DIR)/*.so $(DEST_LIB_DIR)`  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`install -m 755 $(BIN) $(DEST_BIN_DIR)`  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`@ldconfig`  
Installerar filerna i resp. katalog genom kommandot install. Ett anrop till ldconfig görs här för att direkt uppdatera ld.so-cachen så att de nya biblioteken blir synliga direkt för intresserade applikationer.

`$(BIN): $(OBJ_DIR)/electrotest.o`  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`$(CC) $(CFLAGS) -o $@ $^ -L$(LIB_DIR) $(LDFLAGS) -Wl,-rpath,'$$ORIGIN/$(LIB_DIR)'`  
Target för att länka vår binärfil. 
* `$@`
  Är en automatisk variabel som ersätts med vårt target, i detta fall "electrotest".
* `$^`
  Specar alla prereqs utom order-only, i detta fall bara vår electrotest.o.
* `-L$(LIB_DIR)`
  Talar om att vi vill att ld ska leta i LIB_DIR efter våra dynamiska bibliotek.
* `-rpath`
  Här anger vi argument till ld. Närmare bestämt att ld ska sätta rpath till $ORIGIN/lib för att först leta lokalt efter de dynamiska biblioteken för att sedan falla tillbaka på ld.so. $ORIGIN här gör att vi alltid utgår från där binären ligger. Vi kan alltså t.ex. köra den från en godtycklig plats i systemet. Anledningen till att dubbla $$ används är för att make annars vill tolka det som en variabel. Det är ett sätt att "escapa" $.

`$(LIB_DIR)/libpower.so: ../libpower/src/power.c ../libpower/src/power.h | createLibDirectory`  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`$(CC) $(CFLAGS) -shared -fPIC -o $@ $^`  
* `-shared`
  Anger att vi vill skapa ett dynamiskt bibliotek.
* `-fPIC`
  Denna växel skapar positionsoberoende kod. Och till skillnad från lillebror -fpic har denna växel ingen egentlig gräns på hur stor den globala offset-tabellen kan bli. Denna växel går hand i hand med `-shared` och är viktigt för att ld ska kunna tolka offset-tabellen och ladda ett bibliotek.
* `|`
  Anger här att vi vill att createLibDirectory skall vara ett order-only prereq. Detta kommer alltså inte med i `$^`. Utan finns bara där för att tala om att "detta recept måste köras innan, men trigga inte receptet för target p.g.a. mig om jag körs".

`$(OBJ_DIR)/electrotest.o: main/electrotest.c main/electrotest.h | $(OBJ_DIR)`  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`$(CC) -I../libresistance/src -I../libcomponent/main -I../libpower/src $(CFLAGS) -c -o $@ $<`  
Bygger objetsfil för electrotest.
* `-I`
  Talar om för kompilatorn att vi ska kika i dessa kataloger efter headers vi inkluderar i vår källkod.
* `-c`
  Vi vill bara kompilera just nu vilket denna växel anger.
* `$<`
  Automatisk variabel för endast första prereq för receptet. I detta fall alltså endast main/electrotest.c
