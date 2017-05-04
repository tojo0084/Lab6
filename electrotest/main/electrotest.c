#include "electrotest.h"

int main(void) {
  float res=0;
  char str[MAXWORDS];

  do {
    Electro *e = malloc(sizeof(Electro));
    float *res_array = malloc(3*sizeof(float));
    get_voltage(e);
    get_conn(e);
    get_comps(e);
    printf("Ersättningsresistans:\n");
    res = calc_resistance(e->count,e->conn,e->comps);
    printf("%f ohm\n",res);
    printf("Effekt:\n");
    printf("%f \n",calc_power_r(e->volt,res));
    printf("Ersättningsresistanser i E12-serien kopplade i serie:\n");
    int c = e_resistance(res,res_array);
    for(int i=0;i<c;i++){
      printf("%f\n",res_array[i]);
    }

    free(res_array);
    free(e->comps);
    free(e);
    printf("\n");
    printf("type quit to exit\n");
    fgets(str,MAXWORDS,stdin);
  } while(strcmp(str,"quit\n")!=0);

  return 0;
}

void get_voltage(Electro *e) {
  char str[MAXWORDS];
  char *check;
  float temp = 0;

  printf("Ange spänningskälla i V: ");
  fgets(str,MAXWORDS,stdin);
  temp = (float)strtol(str,&check,10);

  if(strlen(check)>1){
    fprintf(stderr,"Input must be a value\n");
    get_voltage(e);
  }else{
    e->volt = temp;
  }
}

void get_conn(Electro *e) {
  char str[MAXWORDS];
  char *check;
  long int temp = 0;

  printf("Ange koppling[S | P]: ");
  fgets(str,MAXWORDS,stdin);
  temp = strtol(str,&check,10);

  if(temp != 0 || strlen(check)>2) {
    fprintf(stderr,"Input must be either P or S\n");
    get_conn(e);
  }else{
    e->conn = str[0];
  }
}

void get_comps(Electro *e) {
  char str[MAXWORDS];
  char *check;
  int temp=0;

  printf("Antal komponenter: ");
  fgets(str,MAXWORDS,stdin);
  temp = (int)strtol(str,&check,10);

  if(strlen(check)>1) {
    fprintf(stderr,"Input must be an integer\n");
    get_comps(e);
  }
  e->count = temp;
  e->comps = malloc(e->count*sizeof(float));

  for(int i= 0;i <= e->count-1;i++) {
    printf("Komponent %d i Ohm: ",i+1);
    fgets(str,MAXWORDS,stdin);
    float res = (float)strtol(str,&check,10);
    if(strlen(check)>1){
      fprintf(stderr,"Input must be a value\n");
    }else{
      e->comps[i] = res;
    }
  }
}
