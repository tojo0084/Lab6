#include <stdio.h>
#include <stdlib.h> // qsort
#include <math.h> // innehåller funktionen fabs (absolutvärdet för float/double) och även pow (uppöjt till)
//vid kompilering av math.h: använd -lm (math library is named libm.so)


//#include <limits.h> // innehåller ULLONG_MAX
//#include <float.h> // FLT_MIN
//#include <tgmath.h>
//#include <errno.h>
//#include <fenv.h>

#include "libcomponent.h"

// Tomas Johansson, Bibliotek 3, libcomponent.so

float FLOAT_DELTA_VALUE_FOR_SORTING = 0.000000001;

int cmpfunc(const void * a, const void * b) {
	float val1 = *(float*)a;
	float val2 = *(float*)b;
	float diff = val1 - val2;
	if(fabs(diff) < FLOAT_DELTA_VALUE_FOR_SORTING) return 0;
	if(diff < 0) return 1; // returnerar positivt tal för att sortera i minskande ordning
	return -1;
}



int e_resistance(float orig_resistance, float *res_array) {
	long double e12_values[] = { 1.00,  1.20,  1.50,  1.80 , 2.20,  2.70,  3.30 , 3.90 , 4.70, 5.60, 6.80, 8.20  };
	int numberOfValuesPerE12sequence = sizeof(e12_values) / sizeof(long double); // istället för att hårdkdoa 12
	int maxMinusPower = 7; // 1^-7 dvs ett upphöjt till -7
	int maxPlusPower = 7; // 1^7
	int arrayIndex = 0;
	int numberOfArrayItems = numberOfValuesPerE12sequence * (maxMinusPower + maxPlusPower + 1);
	long double values[numberOfArrayItems];

	long double powerFactorDouble;

	for(int i=-maxMinusPower; i<=maxPlusPower; i++) {
		powerFactorDouble = pow(10, i);
		for(int j=0; j<12; j++) {
			long double value = powerFactorDouble * e12_values[j];
			values[arrayIndex] = value;
			arrayIndex++;
		}
	}
	for(int i=0; i<numberOfArrayItems; i++) {
		// printf("e_resistance arr i : %Lg \n", values[i]);
	}
	
	long double delta = 0.00001;
	long double sum_ij;
	
	long double sum_ijk;
	int loopCounter = 0;
	// syftet med yttersta while-loopen är att företrädesvis välja endast ett värde, och i andra hand två värden, och som sista utväg tre värden
	// därför loopas först alla värden för att se om de ensamma kan summer till önskat värde,
	// sedan summeras alla kombinationer av två värden, och sist alla kombinationer av tre värden
	while(loopCounter < 3) {
		loopCounter++;
		for(int i=0; i<numberOfArrayItems-2; i++) {
			if(fabs(orig_resistance-values[i]) < delta) {
				res_array[0] = values[i];
				return 1;
			}
			if(loopCounter == 1) continue;
			for(int j=i+1; j<numberOfArrayItems-1; j++) {
				sum_ij = values[i] + values[j];
				if(fabs(orig_resistance-sum_ij) < delta) {
					res_array[0] = values[i];
					res_array[1] = values[j];
					qsort(res_array, 2, sizeof(float), cmpfunc);
					return 2;
				}
				if(loopCounter == 2) continue;
				for(int k=j+1; k<numberOfArrayItems; k++) {
					sum_ijk = values[i] + values[j] + values[k];
					if(fabs(orig_resistance-sum_ijk) < delta) {
						res_array[0] = values[i];
						res_array[1] = values[j];
						res_array[2] = values[k];
						qsort(res_array, 3, sizeof(float), cmpfunc);
						return 3;
					}
				}
			}
		}
	}
	return 0;
}
