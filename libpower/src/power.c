
/**
 * power.c
 * Ludvig Lundberg
 * lulu0011@student.umu.se
 * lulu0011
 * 2017-05-05
 */

#include "power.h"

/**
 * Funktionens syfte: Beräkna effekten enligt formeln P=U^2*R.
 * In: Spänningen samt resistansen som effekten ska beräknas utifrån.
 * Ut: Effekten utifrån den angivna spänningen samt resistansen.
 */
float calc_power_r(float volt, float resistance){
  return (volt*volt)/resistance;
}

/**
 * Funktionens syfte: Beräkna effekten utifrån formeln P=U*I.
 * In: Spänningen och strömmen effekten ska beräknas utifrån.
 * Ut: Effekten utifrån den angivna spänningen samt strömmen.
 */
float calc_power_i(float volt, float current){
  return volt*current;
}
