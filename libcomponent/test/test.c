// Tomas Johansson, Bibliotek 3, libcomponent.so

//gcc test.c unity/unity.c ../main/libcomponent.c -lm -o test
// -lm är för att kompilera math.h (math library is named libm.so)

#include "unity/unity.h"
#include "../main/libcomponent.h"

 // definieras i libcomponent.c
extern const long double E12_VALUES[] ;
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

void test_e_resistance_001200(void) {
	count = e_resistance(0.0012, res_array);
	TEST_ASSERT_EQUAL_INT(1, count);
	TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 0.0012, res_array[0]);
}

void test_e_resistance_001380(void) {
	count = e_resistance(0.00138, res_array);
	TEST_ASSERT_EQUAL_INT(2, count);
	TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 0.0012, res_array[0]);
	TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 0.00018, res_array[1]);
}

void test_e_resistance_001398(void) {
	count = e_resistance(0.001398, res_array);
	TEST_ASSERT_EQUAL_INT(3, count);
	TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 0.0012, res_array[0]);
	TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 0.00018, res_array[1]);
	TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 0.000018, res_array[2]);
}

void test_e_resistance_47(void) {
	count = e_resistance(47, res_array);
	TEST_ASSERT_EQUAL_INT(1, count);
	TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 47, res_array[0]);
}

void test_e_resistance_4_7(void) {
	count = e_resistance(4.7, res_array);
	TEST_ASSERT_EQUAL_INT(1, count);
	TEST_ASSERT_FLOAT_WITHIN(DELTA_VALUE_FOR_EQUALITY, 4.7, res_array[0]);
}

void test_e_resistance_E12_values_matchingWithoutSumming(void) {
	// E12_VALUES[] = { 1.00,  1.20,  1.50,  1.80 , 2.20,  2.70,  3.30 , 3.90 , 4.70, 5.60, 6.80, 8.20  };
	for(int i=0; i<12; i++) {
		float e12value = E12_VALUES[i];
		count = e_resistance(e12value, res_array);
		char testFailureMessage[50];
		snprintf(testFailureMessage, sizeof testFailureMessage, "E12-värde som orsakade problemet: %f", e12value);
		TEST_ASSERT_EQUAL_INT_MESSAGE(1, count, testFailureMessage);
		TEST_ASSERT_FLOAT_WITHIN_MESSAGE(DELTA_VALUE_FOR_EQUALITY, e12value, res_array[0], testFailureMessage);
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

	RUN_TEST(test_e_resistance_001200);
	RUN_TEST(test_e_resistance_001380);
	RUN_TEST(test_e_resistance_001398);

	UnityEnd();

	return 0;
}
