#include "electrotest.h"
#include <stdbool.h> // bool
#include <ctype.h>   // toupper

const float minResistance = 0.01;
const float maxResistance = 1000000;

static bool is_P_or_S_ignoringCaseAndTerminatingCharacter(char *str) {
  int numberOfInitialCharacters_P_or_S = strspn(str, "SPsp");
  int lengthOfInputLineIncludingTerminatingCharacter = strlen(str);
  return numberOfInitialCharacters_P_or_S == 1 &&
         lengthOfInputLineIncludingTerminatingCharacter <= 2;
}

int main(void) {
  float res = 0;
  char str[MAXWORDS];

  do {
    Electro *e = malloc(sizeof(Electro));
    float *res_array = malloc(3 * sizeof(float));
    get_voltage(e);
    get_conn(e);
    get_comps(e);
    printf("Ersättningsresistans:\n");

    // Anrop av funktionen "calc_resistance" i biblioteket "libresistance.so":
    res = calc_resistance(e->count, e->conn, e->comps);

    printf("%.1f ohm\n", res);
    printf("Effekt:\n");

    // Anrop av funktionen "calc_power_r" i biblioteket "libpower.so":
    printf("%.2f W\n", calc_power_r(e->volt, res));

    printf("Ersättningsresistanser i E12-serien kopplade i serie:\n");

    // Anrop av funktionen "e_resistance" i biblioteket "libcomponent.so":
    int c = e_resistance(res, res_array);

    for (int i = 0; i < c; i++) {
      printf("%f\n", res_array[i]);
    }

    free(res_array);
    free(e->comps);
    free(e);
    printf("\n");
    printf("type quit to exit\n");
    fgets(str, MAXWORDS, stdin);
  } while (strcmp(str, "quit\n") != 0);

  return 0;
}

void get_voltage(Electro *e) {
  char str[MAXWORDS];
  float temp = 0;
  printf("Ange spänningskälla i V: ");
  fgets(str, MAXWORDS, stdin);
  int numberOfSuccessfullyFilledVariables = sscanf(str, "%f", &temp);
  if (numberOfSuccessfullyFilledVariables != 1) {
    fprintf(stderr, "Input must be a value\n");
    get_voltage(e);
  } else {
    e->volt = temp;
  }
}

void get_conn(Electro *e) {
  char str[MAXWORDS];

  printf("Ange koppling[S | P]: ");
  fgets(str, MAXWORDS, stdin);

  if (!is_P_or_S_ignoringCaseAndTerminatingCharacter(str)) {
    fprintf(stderr, "Input must be either P or S\n");
    get_conn(e);
  } else {
    e->conn = toupper(str[0]); // calc_resistance kräver f.n. versal
  }
}

void get_comps(Electro *e) {
  char str[MAXWORDS];
  char *check;
  int temp = 0;

  bool isInputOk = false;
  while (!isInputOk) {
    printf("Antal komponenter: ");
    fgets(str, MAXWORDS, stdin);
    temp = (int)strtol(str, &check, 10);

    if (strlen(check) > 1) {
      fprintf(stderr, "Input must be an integer\n");
    } else {
      isInputOk = true;
    }
  }

  e->count = temp;
  e->comps = malloc(e->count * sizeof(float));

  for (int i = 0; i <= e->count - 1; i++) {
    while (true) {
      printf("Komponent %d i Ohm: ", i + 1);
      fgets(str, MAXWORDS, stdin);
      float res;
      int numberOfSuccessfullyFilledVariables = sscanf(str, "%f", &res);
      if (numberOfSuccessfullyFilledVariables != 1 || res < minResistance ||
          res > maxResistance) {
        fprintf(stderr, "Input must be a value between %f and %f\n",
                minResistance, maxResistance);
      } else {
        e->comps[i] = res;
        break;
      }
    }
  }
}
