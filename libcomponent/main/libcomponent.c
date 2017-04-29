// Tomas Johansson, Bibliotek 3, libcomponent.so
#include <stdio.h>
#include <stdlib.h> // qsort
#include <math.h> // fabs , pow . Observera vid kompilering av math.h: använd -lm (math library heter libm.so)
#include <stdbool.h> // bool

#include "libcomponent.h"

// 12 grundvärden är definierade i arrayen nedan, men värdena kan också vara tiopotenser av dessa
// t.ex. 82000 eller 0.0082.
const long double E12_VALUES[] = { 1.00,  1.20,  1.50,  1.80 , 2.20,  2.70,  3.30 , 3.90 , 4.70, 5.60, 6.80, 8.20  };

// Konstanterna nedan definierar hur små och stora tiopotenser acv E12-värden ovan som programmet försöker klara av.
const int maxMinusPower = 4; // 1^-4 dvs ett upphöjt till -4
const int maxPlusPower = 7; // 1^7

// Storleken 500 nedan räcker för en stor array med E12-värden mellan 10^-20 och 10^20
static long double values[500]; // det funakr INTE att skriva "maxMinusPower+maxPlusPower+1" innanför hakparentserna
static int numberOfArrayItems = 0; // faktiska antalet element i arrayen som används


// antalet decimaler nedan är inte vetenskapligt utvalt, och om man vill kunna använda minimalt små E12-värden får man nog försöka justera värdet.
const long double DELTA_VALUE_FOR_EQUALITY = 0.000001;
// Dessa två värden nedan medförde t.ex. skillnaden för att kolla om 4.7 är lika med 4.7 ...
// (men t.ex. jämföresle med 3.9 funkade även med den senare)
// 0.000001
// 0.0000001

int sortingDescending(const void * a, const void * b) {
	float val1 = *(float*)a;
	float val2 = *(float*)b;
	float diff = val1 - val2;
	if(fabs(diff) < DELTA_VALUE_FOR_EQUALITY) return 0;
	if(diff < 0) return 1; // returnerar positivt tal för att sortera i minskande ordning
	return -1;
}

// Initierings-funktionen behöver bara anropas en gång, och då sätter den numberOfArrayItems till en siffra större än 0,
// vilket därför kan utnyttjas för att innan anrop kontrollera om anrop behövs.
// Funktionen kommer att populera en stor array med E12-värden tillhörande olika tiopotenser.
// t.ex. dessa: 1.00,  1.20,  1.50 ...
// ock också t.ex. dessa: 0.00001,  0.000012,  0.000015
// ock också t.ex. dessa: 1000000, 1200000 1500000 ...
void initializeArrayWithE12valuesOfDifferentPowers() {
	int numberOfValuesPerE12sequence = sizeof(E12_VALUES) / sizeof(long double); // istället för att hårdkdoa 12

	int arrayIndex = 0;
	long double powerFactor;

	for(int i=-maxMinusPower; i<=maxPlusPower; i++) {
		powerFactor = pow(10, i);
		for(int j=0; j < numberOfValuesPerE12sequence; j++) {
			long double value = powerFactor * E12_VALUES[j];
			values[arrayIndex++] = value;
		}
	}
	numberOfArrayItems = arrayIndex; // = numberOfValuesPerE12sequence * (maxMinusPower + maxPlusPower + 1);
}

int iterateArrayWithE12valuesAndTryToSumCombinationOfValues(float orig_resistance, float *res_array) {
	// Det finns naturligtvis ENORM potential att skriva om den här funktkionen på ett bättre sätt..
	// Exempel: Om man skickar in parametern orig_resistance=100000
	// så kommer loopen ändå börja med att prova summering av värden 0.001 + 0.0012 o.s.v.
	// men eftersom det här inte är en algoritm-kurs så ska det inte spela någon roll.
	// Citat av läraren: "Det är ju inte en programmeringskurs utan det viktiga med kursen är att ni ska samarbeta kring ett litet programmeringsprojekt."
	// http://www.moodle2.tfe.umu.se/mod/forum/discuss.php?d=3585

	long double sum_of_three_values;
	long double sum_of_two_values;
	int loopCounter = 0;
	// Syftet med yttersta while-loopen nedan är att företrädesvis välja endast ett värde, och i andra hand två värden, och som sista utväg tre värden
	// därför loopas först alla värden för att se om de ensamma kan summer till önskat värde,
	// sedan summeras alla kombinationer av två värden, och sist alla kombinationer av tre värden.
	// Ett exempel är att 61 kan erhållas genom av summering med E12-värden 33+27+1
	// men ett "bättre" (färre komponenter) är att summera två E12-värden 39+22.
	while(loopCounter < 3) {
		loopCounter++;
		for(int i=0; i<numberOfArrayItems-2; i++) {
			if( fabs(orig_resistance - values[i]) < DELTA_VALUE_FOR_EQUALITY) {
				res_array[0] = values[i];
				return 1;
			}
			if(loopCounter == 1) continue; // Eftersom man föredrar matchning med ett värde kör vi bara igenom alla värden en gång först
			for(int j=i+1; j<numberOfArrayItems-1; j++) {
				sum_of_two_values = values[i] + values[j];
				if( fabs(orig_resistance - sum_of_two_values) < DELTA_VALUE_FOR_EQUALITY) {
					res_array[0] = values[i];
					res_array[1] = values[j];
					qsort(res_array, 2, sizeof(float), sortingDescending);
					return 2;
				}
				if(loopCounter == 2) continue; // Andra varvet i while-loopen försöker vi hitta alla kombinationer med två värden
				for(int k=j+1; k<numberOfArrayItems; k++) {
					sum_of_three_values = values[i] + values[j] + values[k];
					if( fabs(orig_resistance - sum_of_three_values) < DELTA_VALUE_FOR_EQUALITY) {
						res_array[0] = values[i];
						res_array[1] = values[j];
						res_array[2] = values[k];
						qsort(res_array, 3, sizeof(float), sortingDescending);
						return 3;
					}
				}
			}
		}
	}
	return 0;
}

int e_resistance(float orig_resistance, float *res_array) {
	bool areValuesInitialized = numberOfArrayItems > 0;
	if(!areValuesInitialized) initializeArrayWithE12valuesOfDifferentPowers();
	return iterateArrayWithE12valuesAndTryToSumCombinationOfValues( orig_resistance, res_array);
}
