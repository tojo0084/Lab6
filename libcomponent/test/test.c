// gcc test.c unity/unity.c ../main/libcomponent.c -o test

#include "unity/unity.h"
#include "../main/libcomponent.h"

void test_e_resistance(void)
{
	float res_array[3];
	int count = e_resistance(1398, res_array);

	// ToDo: Aktivera bortkommenterade raderna nedan när funtionen är implementerad
	// TEST_ASSERT_EQUAL_INT(3, count);

	float delta = 0.001;
	// TEST_ASSERT_FLOAT_WITHIN(delta, 1200, res_array[0]);
	// TEST_ASSERT_FLOAT_WITHIN(delta, 180, res_array[1]);
	// TEST_ASSERT_FLOAT_WITHIN(delta, 18, res_array[2])
}

int main(void)
{
	UnityBegin("test/test.c");

	RUN_TEST(test_e_resistance);

	UnityEnd();

	return 0;
}
