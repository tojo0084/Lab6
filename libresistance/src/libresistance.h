/* File:        libresistance.h
 * Author:      Marcus Nordenberg
 * Mail:        <marcus.nordenberg@gmail.com> <mano03333@student.umu.se>
 * Student-ID:  agnon / mano0333
 * Date:        2017-04-28
 * Rev:         First draft (170428)
 */

#ifndef LIBRESISTANCE_H
#define LIBRESISTANCE_H

/**
 * @brief calc_resistance Calculates the resistance of a number of resistors.
 * @param count Number of resistors to calculate resistance for
 * @param conn Connection type 'S' = series, 'P' = parallell
 * @param array Resistance vector
 * @return Calculated replacement resistor value
 */
float calc_resistance(int count, char conn, float *array);

#endif // LIBRESISTANCE_H
