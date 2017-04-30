#include <stdio.h>

#include "../../libcomponent/main/libcomponent.h"

int main(int argc, char *argv[]) {
  printf("\nOm anropet till biblioteket fungerar borde resultat nedan bli: 3 , 1200 , 180 , 18 \n");
  float res_array[3];
  int count;
  count = e_resistance(1398, res_array);
  printf("%d , %f , %f , %f \n", count, res_array[0], res_array[1], res_array[2]);
  return 0;
}
