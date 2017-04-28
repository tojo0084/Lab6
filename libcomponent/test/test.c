//gcc test.c unity/unity.c ../main/libcomponent.c -lm -o test
// -lm är för att kompilera math.h (math library is named libm.so)

#include "unity/unity.h"
#include "../main/libcomponent.h"

void test_e_resistance(void) {
	float delta = 0.00001;
	float res_array[3];
	int count;

	count = e_resistance(1200, res_array);
	TEST_ASSERT_EQUAL_INT(1, count);
	TEST_ASSERT_FLOAT_WITHIN(delta, 1200, res_array[0]);


	count = e_resistance(1380, res_array);
	TEST_ASSERT_EQUAL_INT(2, count);
	TEST_ASSERT_FLOAT_WITHIN(delta, 1200, res_array[0]);
	TEST_ASSERT_FLOAT_WITHIN(delta, 180, res_array[1]);


	count = e_resistance(1398, res_array);
	TEST_ASSERT_EQUAL_INT(3, count);
	TEST_ASSERT_FLOAT_WITHIN(delta, 1200, res_array[0]);
	TEST_ASSERT_FLOAT_WITHIN(delta, 180, res_array[1]);
	TEST_ASSERT_FLOAT_WITHIN(delta, 18, res_array[2]);

}

void test_e_resistance_2(void) {
	float delta = 0.00001;
	float res_array[3];
	int count;

	count = e_resistance(4.70, res_array);
	

	// float e12_values[] = { 1.00,  1.20,  1.50,  1.80 , 2.20,  2.70,  3.30 , 3.90 , 4.70, 5.60, 6.80, 8.20  };
	
	count = e_resistance(4.70, res_array);
	TEST_ASSERT_EQUAL_INT(1, count);
	TEST_ASSERT_FLOAT_WITHIN(delta, 4.70, res_array[0]);
/* */
	count = e_resistance(6.80, res_array);
	TEST_ASSERT_EQUAL_INT(1, count);
	TEST_ASSERT_FLOAT_WITHIN(delta, 6.80, res_array[0]);

	count = e_resistance(8.30, res_array);
	TEST_ASSERT_EQUAL_INT(2, count);
	TEST_ASSERT_FLOAT_WITHIN(delta, 8.20, res_array[0]);
	TEST_ASSERT_FLOAT_WITHIN(delta, 0.10, res_array[1]);

	count = e_resistance(8.60, res_array);
	TEST_ASSERT_EQUAL_INT(2, count);
	TEST_ASSERT_FLOAT_WITHIN(delta, 6.8, res_array[0]);
	TEST_ASSERT_FLOAT_WITHIN(delta, 1.8, res_array[1]);


	// OBS! värdet 6.1 är ett ganska bra exempel.
	// Dels fungerar inte den enklaste algoritmen jag först tänkte mig dvs att hitta det största värdet och sedan fylla på med mindre ...
	// och dessutom kan den ge både tre eller två värden som resultat och då väljer man rimligen det lägsta
	count = e_resistance(6.10, res_array);
//	TEST_ASSERT_EQUAL_INT(3, count);
//	TEST_ASSERT_FLOAT_WITHIN(delta, 3.3, res_array[0]);
//	TEST_ASSERT_FLOAT_WITHIN(delta, 2.7, res_array[1]);
//	TEST_ASSERT_FLOAT_WITHIN(delta, 0.1, res_array[2]);
// ovanstående är ett alternativ men den nedan ger färre
	TEST_ASSERT_EQUAL_INT(2, count);
	TEST_ASSERT_FLOAT_WITHIN(delta, 3.9, res_array[0]);
	TEST_ASSERT_FLOAT_WITHIN(delta, 2.2, res_array[1]);
}


int main(void) {
	UnityBegin("test/test.c");

	RUN_TEST(test_e_resistance);
	RUN_TEST(test_e_resistance_2);

	UnityEnd();

	return 0;
}
