<<<<<<< HEAD
/**
 * power.h
 * Ludvig Lundberg
 * lulu0011@student.umu.se
 * lulu0011
 * 2017-05-05
 */

#ifndef _POWER_
#define _POWER_

/**
 * Funktionens syfte: Beräkna effekten enligt formeln P=U^2*R.
 * In: Spänningen samt resistansen som effekten ska beräknas utifrån.
 * Ut: Effekten utifrån den angivna spänningen samt resistansen.
 */
float calc_power_r(float volt, float resistance);

/**
 * Funktionens syfte: Beräkna effekten utifrån formeln P=U*I.
 * In: Spänningen och strömmen effekten ska beräknas utifrån.
 * Ut: Effekten utifrån den angivna spänningen samt strömmen.
 */
=======
#ifndef _POWER_
#define _POWER_

float calc_power_r(float volt, float resistance);

>>>>>>> 186c84b946dcba778f661dbbfb1ce908d9a45373
float calc_power_i(float volt, float current);

#endif
