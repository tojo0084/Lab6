// Tomas Johansson, Bibliotek 3, libcomponent.so
#include <stdio.h>
#include <stdlib.h>  // qsort
#include <math.h>    // fabs , pow . Observera vid kompilering av math.h: använd -lm (math library heter libm.so)
#include <stdbool.h> // bool

#include "libcomponent.h"

/**
E12 grundvärden är definierade i arrayen nedan, men E12-värde kan dessutom vara tiopotenser av dessa.
Exempel: 82000 (8.2*10^3) och 0.0082 (8.2*10^-3) är också giltiga E12-värden.
Källa:
https://technick.net/guides/electronics/standard_resistors_table/
*/
const long double E12_BASE_VALUES[] = {1.00, 1.20, 1.50, 1.80, 2.20, 2.70,
                                  3.30, 3.90, 4.70, 5.60, 6.80, 8.20};

/**
Konstanterna nedan definierar hur små och stora tiopotenser acv E12-värden
ovan som programmet försöker klara av.
*/
const int maxMinusPower = 4; // 1^-4 dvs ett upphöjt till -4
const int maxPlusPower = 7;  // 1^7 dvs ett upphöjt till +7

/**
Array-storleken 500 nedan skulle räcka till för en array med E12-värden 
mellan 10^-20 och 10^20.
Den hårdkodas här till en större siffra än vad som behövs för att slippa ändra på flera 
ställen om man vill justera intervallet, eftersom det INTE fungerar att här allokera med 
konstanter på följande sätt: 
static long double values[maxMinusPower+maxPlusPower+1]
*/
static long double E12_values[500];

/**
Det faktiska antalet element i E12-arrayen som används.
Siffran kommer att initieras i en funktion som fyller arrayen med sina E12-värden.
*/
static int numberOfArrayItems;

/**
Siffran anger gränsen för hur olika två flyttal får vara för att de ska betraktas som lika.
Antalet decimaler är inte vetenskapligt utvalt, och om man vill kunna
använda minimalt små E12-värden får man nog försöka justera värdet.
*/
const long double DELTA_VALUE_FOR_EQUALITY = 0.000001;


/**
Hjälpfunktion som används som parameter (funktionspekare) till qsort för att sortera en float array i sjunkande ordning.
För att arrayen ska bli sorterad i sjunkande ordning ska funktionen returnera ett posiitivt tal om a är större än b.
Ett negativt tal ska returneras om b är större än a, och noll ska returneras om talen ska betraktas som lika.
*/
int sortingDescending(const void *a, const void *b) {
  float val1 = *(float *)a;
  float val2 = *(float *)b;
  float diff = val1 - val2;
  if (fabs(diff) < DELTA_VALUE_FOR_EQUALITY)
    return 0;
  if (diff < 0)
    return 1; // returnerar positivt tal för att sortera i minskande ordning
  return -1;
}

/**
Initierar en stor array med alla tänkbara E12-värden med hjälp av en mindre array 
med 12 st grundvärden mellan 1 och 10.
Övriga E12-värden erhålles genom att multiplicera grundvärdena med tiopotenser.
Initierings-funktionen behöver bara anropas en gång, och då sätter den
numberOfArrayItems till en siffra större än 0, vilket därför kan utnyttjas för 
att innan anrop kontrollera om ett anrop behövs.
Funktionen kommer alltså att populera en stor array med E12-värden tillhörande 
olika tiopotenser.
Exempel på E12-grundvärden: 1.00,  1.20,  1.50 ...
Exempel på fler värden men från en annan tiopotens: 1000000, 1200000 1500000 ...
Fler exempel från en annan tiopotens: 0.00001,  0.000012,  0.000015
*/
void initializeArrayWithE12valuesOfDifferentPowers() {
  int numberOfValuesPerE12sequence =
      sizeof(E12_BASE_VALUES) / sizeof(long double); // istället för att hårdkdoda 12

  int arrayIndex = 0;
  long double powerFactor;

  for (int i = -maxMinusPower; i <= maxPlusPower; i++) {
    powerFactor = pow(10, i);
    for (int j = 0; j < numberOfValuesPerE12sequence; j++) {
      long double value = powerFactor * E12_BASE_VALUES[j];
      E12_values[arrayIndex++] = value;
    }
  }
  numberOfArrayItems = arrayIndex; // = numberOfValuesPerE12sequence *
                                   // (maxMinusPower + maxPlusPower + 1);
}


/**
Loopar igenom kombinationer av E12-värden för att testa om en summering av 1-3 sådana 
termer resulterar i en summa lika med inparametern orig_resistance.
Om termer hittas fylls de i parameter-arrayen som således fungerar som en output-parameter.

@param desiredSum den summa som funktionen försöker skapa genom att summera 1-3 termer som itereras
@param resultTerms ska vara en pekare till en array med plats för upp till 3 termer som summerar till desiredSum
@param potentialTermsForSumming  array med alla de termer som kan kombineras för att försöka summera till önskvärda summan.
@return antalet termer (1-3) eller 0 om inga kombinationer av termer resulterade i önskvärd summa.
*/
int
iterateArrayAndTryToSumCombinationOfValues(float desiredSum, float* resultTerms, long double * potentialTermsForSumming) {
  // Det finns naturligtvis ENORM potential att skriva om den här funktktionen på
  // ett bättre sätt..
  // Exempel: Om man skickar in parametern desiredSum=100000
  // så kommer loopen ändå börja med att prova summering av värden 0.001 +
  // 0.0012 o.s.v.
  // men eftersom det här inte är en algoritm-kurs så ska det inte spela någon roll.
  // Citat av läraren: "Det är ju inte en programmeringskurs utan det viktiga
  // med kursen är att ni ska samarbeta kring ett litet programmeringsprojekt."
  // http://www.moodle2.tfe.umu.se/mod/forum/discuss.php?d=3585

  long double sum_of_three_values;
  long double sum_of_two_values;
  int loopCounter = 0;
  // Syftet med yttersta while-loopen nedan är att företrädesvis välja endast
  // ett värde, och i andra hand två värden, och som sista utväg tre värden
  // därför loopas först alla värden för att se om de ensamma kan summer till
  // önskat värde,
  // Sedan summeras alla kombinationer av två värden, och sist alla
  // kombinationer av tre värden.
  // Ett exempel är att 61 kan erhållas genom av summering med E12-värden
  // 33+27+1
  // men ett "bättre" (färre komponenter) är att summera två E12-värden 39+22.
  // Se även kommentaren i test-funktionen "test_e_resistance_61" som även
  // förklarar varför man inte kan utgå från det högsta
  // matchande värdet och sedan fortsätta med diffarna.
  while (loopCounter < 3) {
    loopCounter++;
    for (int i = 0; i < numberOfArrayItems - 2; i++) {
      if (fabs(desiredSum - potentialTermsForSumming[i]) < DELTA_VALUE_FOR_EQUALITY) {
        resultTerms[0] = potentialTermsForSumming[i];
        return 1;
      }
      if (loopCounter == 1)
        continue; // Eftersom man föredrar matchning med ett värde kör vi bara
                  // igenom alla värden en gång först
      for (int j = i + 1; j < numberOfArrayItems - 1; j++) {
        sum_of_two_values = potentialTermsForSumming[i] + potentialTermsForSumming[j];
        if (fabs(desiredSum - sum_of_two_values) <
            DELTA_VALUE_FOR_EQUALITY) {
          resultTerms[0] = potentialTermsForSumming[i];
          resultTerms[1] = potentialTermsForSumming[j];
          qsort(resultTerms, 2, sizeof(float), sortingDescending);
          return 2;
        }
        if (loopCounter == 2)
          continue; // Andra varvet i while-loopen försöker vi hitta alla
                    // kombinationer med två värden
        for (int k = j + 1; k < numberOfArrayItems; k++) {
          sum_of_three_values = potentialTermsForSumming[i] + potentialTermsForSumming[j] + potentialTermsForSumming[k];
          if (fabs(desiredSum - sum_of_three_values) <
              DELTA_VALUE_FOR_EQUALITY) {
            resultTerms[0] = potentialTermsForSumming[i];
            resultTerms[1] = potentialTermsForSumming[j];
            resultTerms[2] = potentialTermsForSumming[k];
            qsort(resultTerms, 3, sizeof(float), sortingDescending);
            return 3;
          }
        }
      }
    }
  }
  return 0;
}


/** Dokumentation av parametrarna: se h-filen */
int e_resistance(float orig_resistance, float *res_array) {
  bool areValuesInitialized = numberOfArrayItems > 0;
  if (!areValuesInitialized)
    initializeArrayWithE12valuesOfDifferentPowers();
  return iterateArrayAndTryToSumCombinationOfValues(
      orig_resistance, res_array, E12_values);
}