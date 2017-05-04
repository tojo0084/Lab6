/* File:        libresistance.c
 * Author:      Marcus Nordenberg
 * Mail:        <marcus.nordenberg@gmail.com> <mano03333@student.umu.se>
 * Student-ID:  agnon / mano0333
 * Date:        2017-04-28
 * Rev:         First draft (170428)
 */

#include "resistance.h"
#include <stdlib.h>

/**
 * @brief checkArguments Do sanity checks on the arguments
 * @param count Number of resistor values
 * @param conn Type of coupling
 * @param array The actual values
 * @return -1 on an error. 0 Otherwie
 */
static int checkArguments(int count, char conn, float *array) {
  int i;
  // Check array pointer
  if (array == NULL)
    return -1;

  // Simple check on the argument count
  if (count <= 0)
    return -1;

  // Check coupling type
  switch (conn) {
  case 'S':
    break;
  case 'P':
    // Extra checks if in parallell coupling mode
    for (i = 0; i < count; i++)
      if (array[i] <= 0.0f)
        return -1;
    break;
  default:
    return -1;
  }

  return 0;
}

/**
 * @brief parallel_resistance_term
 * @param value Resistor value for which to return the correct term
 * @return The term for the resistor value used in parallell couplings
 */
static float parallel_resistance_term(float value) { return 1 / value; }

/**
 * @brief series_resistance_term
 * @param value Resistor value for which to return the correct term
 * @return The term for the resistor value used in series couplings
 */
static float series_resistance_term(float value) { return value; }

float calc_resistance(int count, char conn, float *array) {

  float (*term_value)(float);
  int i;
  float result = 0.0f;

  // Check them arguments
  if (checkArguments(count, conn, array))
    return -1;

  // At this moment it's either S or P
  if (conn == 'S')
    term_value = series_resistance_term;
  else
    term_value = parallel_resistance_term;

  // Iterate through the resistor values and calculate the sum
  for (i = 0; i < count; i++)
    result += term_value(array[i]);

  if (conn == 'P')
    result = 1 / result;

  return result;
}
