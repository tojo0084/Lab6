	#ifndef _ELECTROTEST_H
#define _ELECTROTEST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "power.h"
#include "libresistance.h"
#include "libcomponent.h"

#define MAXWORDS 1024

typedef struct Electro{
  float *comps;
  float *res_array;
  float volt;
  char conn;
  int count;
}Electro;

void get_voltage(Electro *e);
void get_conn(Electro *e);
void get_comps(Electro *e);

#endif


