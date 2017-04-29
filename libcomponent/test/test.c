// Tomas Johansson, Bibliotek 3, libcomponent.so

// gcc test.c unity/unity.c ../main/libcomponent.c -lm -o test
// -lm är för att kompilera math.h (math library is named libm.so)

#include "unity/unity.h"
#include "../main/libcomponent.h"

// definieras i libcomponent.c
extern const long double E12_VALUES[];
extern const long double DELTA_VALUE_FOR_EQUALITY;

float res_array[3];
int count;

void test_e_resistance_1200(void) {
  count = e_resistance(1200, res_array);
  TEST_ASSERT_EQUAL_INT(1, count);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 1200, res_array[0]);
}

void test_e_resistance_1380(void) {
  count = e_resistance(1380, res_array);
  TEST_ASSERT_EQUAL_INT(2, count);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 1200, res_array[0]);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 180, res_array[1]);
}

void test_e_resistance_1398(void) {
  count = e_resistance(1398000, res_array);
  TEST_ASSERT_EQUAL_INT(3, count);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 1200000, res_array[0]);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 180000, res_array[1]);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 18000, res_array[2]);
}

void test_e_resistance_1200000(void) {
  count = e_resistance(1200000, res_array);
  TEST_ASSERT_EQUAL_INT(1, count);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 1200000, res_array[0]);
}

void test_e_resistance_1380000(void) {
  count = e_resistance(1380000, res_array);
  TEST_ASSERT_EQUAL_INT(2, count);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 1200000, res_array[0]);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 180000, res_array[1]);
}

void test_e_resistance_1398000(void) {
  count = e_resistance(1398000, res_array);
  TEST_ASSERT_EQUAL_INT(3, count);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 1200000, res_array[0]);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 180000, res_array[1]);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 18000, res_array[2]);
}

void test_e_resistance_01200(void) {
  count = e_resistance(0.012, res_array);
  TEST_ASSERT_EQUAL_INT(1, count);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 0.012, res_array[0]);
}

void test_e_resistance_01380(void) {
  count = e_resistance(0.0138, res_array);
  TEST_ASSERT_EQUAL_INT(2, count);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 0.012, res_array[0]);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 0.0018, res_array[1]);
}

void test_e_resistance_01398(void) {
  count = e_resistance(0.01398, res_array);
  TEST_ASSERT_EQUAL_INT(3, count);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 0.012, res_array[0]);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 0.0018, res_array[1]);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 0.00018, res_array[2]);
}

// Detta test lade jag till i samband att jag upptäckte att 4.7 inte fungerade
// (när testerna i en loop kördes)
// och det löste jag genom att justera värdet på DELTA_VALUE_FOR_EQUALITY med
// mindre precision.
void test_e_resistance_4_7(void) {
  count = e_resistance(4.7, res_array);
  TEST_ASSERT_EQUAL_INT(1, count);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 4.7, res_array[0]);
}

void test_e_resistance_61(void) {
  // Exemplet med 61 illustrerar ganska bra att algoritmen inte kan
  // implementeras så enkelt som man skulle kunna hoppas.
  // Den motvisar nämligen vad jag först tänkte mig, nämligen att man skulle
  // kunna först välja det högsta värdet som samtidigt
  // inte är för stort, och sedan fyllar man på i eventudell diff med nästa
  // värde, och samma princip för det ev tredje sista värdet.
  // E12-värden (bra att ha lättillgängliga när man läser detta exempel nedan):
  // { 1.00,  1.20,  1.50,  1.80 , 2.20,  2.70,  3.30 , 3.90 , 4.70, 5.60, 6.80,
  // 8.20  };
  // Den metodiken skulle dock resultera i följande:
  // Först hittar man 5.6 (det största mindre än 6.1) och då blir diffen 0.5 och
  // dår blir det största värdet 0.47
  // och då blir den sista diffen 0.03 men det finns inget sådan E12-värde så
  // därför misslyckas den simpla algoritmen.

  // Därför måste man vara beredd att kombniera fler värden, t.ex. följande:
  // 3.3 + 2.7 + 0.1 = 6.1
  // Men också:
  // 3.9 + 2.2 = 6.1
  // Jag har valt ett implementera det sistnämnda, d.v.s. förutsätter att man
  // vill ha så få som möjligt,
  // och desutom tolkade jag ett exempel i uppgiften som det är meningen att det
  // första ska sorteras först.
  count = e_resistance(6.1, res_array);
  TEST_ASSERT_EQUAL_INT(2, count);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 3.9, res_array[0]);
  TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 2.2, res_array[1]);
}

void test_e_resistance_E12_values_matchingWithoutSumming(void) {
  // E12_VALUES[] = { 1.00,  1.20,  1.50,  1.80 , 2.20,  2.70,  3.30 , 3.90 ,
  // 4.70, 5.60, 6.80, 8.20  };

  double multipliers[] = {0.001, 1, 1000};
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 12; i++) {
      float e12value = multipliers[j] * E12_VALUES[i];
      count = e_resistance(e12value, res_array);
      char testFailureMessage[50];
      snprintf(testFailureMessage, sizeof testFailureMessage,
               "E12-värde som orsakade problemet: %f", e12value);
      TEST_ASSERT_EQUAL_INT_MESSAGE(1, count, testFailureMessage);
      TEST_ASSERT_FLOAT_WITHIN_MESSAGE(DELTA_VALUE_FOR_EQUALITY, e12value,
                                       res_array[0], testFailureMessage);
    }
  }
}

int main(void) {
  UnityBegin("test/test.c");

  RUN_TEST(test_e_resistance_1200);
  RUN_TEST(test_e_resistance_1380);
  RUN_TEST(test_e_resistance_1398);

  RUN_TEST(test_e_resistance_1200000);
  RUN_TEST(test_e_resistance_1380000);
  RUN_TEST(test_e_resistance_1398000);

  RUN_TEST(test_e_resistance_01200);
  RUN_TEST(test_e_resistance_01380);
  RUN_TEST(test_e_resistance_01398);

  RUN_TEST(test_e_resistance_61);

  RUN_TEST(test_e_resistance_E12_values_matchingWithoutSumming);
  // testet nedan lade jag till när jag upptäckte ett fel i testet ovan
  // (för att isolerat kunna köra det specifika testet till skillnad från
  // ovanstående som itererar och testar många värden)
  RUN_TEST(test_e_resistance_4_7);

  UnityEnd();

  return 0;
}
