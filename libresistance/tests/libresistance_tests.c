/* File:        libresistance_tests.c
 * Author:      Marcus Nordenberg
 * Mail:        <marcus.nordenberg@gmail.com> <mano03333@student.umu.se>
 * Student-ID:  agnon / mano0333
 * Date:        2017-04-28
 * Rev:         First draft (170428)
 */

#include "gtest/gtest.h"
#include <stdlib.h>

extern "C" {
#include "libresistance.h"
}

namespace {

// Test that the calc_resistance() method handles NULL pointers.
TEST(CalcResistance, HandlesNullArray) {
  float *array = NULL;
  EXPECT_EQ(-1, calc_resistance(3, 'P', array));
}

// Test that the calc_resistance() method handles faulty count.
TEST(CalcResistance, HandlesFaultyCount) {
  float array[] = {0, 0, 0};
  EXPECT_EQ(-1, calc_resistance(-1, 'P', array));
}

// Test that the calc_resistance() method handles zero resistance in parallel
// coupling.
TEST(CalcResistance, HandlesZeroReistanceInParallel) {
  float array[] = {100, 0, 400};
  EXPECT_EQ(-1, calc_resistance(3, 'P', array));
}

// Test that the calc_resistance() method handles parallel coupling correct.
TEST(CalcResistance, HandlesParallel) {
  float array[] = {100, 200, 400};
  EXPECT_EQ(57.1428571429f, calc_resistance(3, 'P', array));
}

// Test that the calc_resistance() method handles series coupling correct.
TEST(CalcResistance, HandlesSeries) {
  float array[] = {100, 200, 400};
  EXPECT_EQ(700, calc_resistance(3, 'S', array));
}

} // namespace
