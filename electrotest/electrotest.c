#include <stdio.h>
// #include <stdbool.h> // för att kunna använda bool och true
// #include <string.h> // för att kunna använda strlen

// gcc -o electrotest electrotest.c -L. -lcomponent -lm -Wl,-rpath,/usr/local/lib/libcomponent.so
// gcc -o electrotest electrotest.c  -lcomponent -lm -Wl,-rpath,/usr/local/lib/libcomponent.so
#include "../libcomponent/main/libcomponent.h"

int main ( int argc, char *argv[] ) {
	if(argc != 3) {
    printf("Innan \n");
    float res_array[3];
    int count;
    count = e_resistance(1200, res_array);

    printf("Klart \n");
		return -1;
	}
   return 0;
}
