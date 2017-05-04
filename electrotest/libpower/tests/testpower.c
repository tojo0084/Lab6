
#include <stdio.h>
#include "power.h"

int main(void) {
   float volt=50;
   float resistance=1398;

   float ret= calc_power_r(volt, resistance);

   printf("slut %f \n",ret);
   return 0;
}
