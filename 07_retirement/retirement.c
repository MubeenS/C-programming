#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;
double calBal (int age,retire_info rinfo,double bal) {
  while(rinfo.months>0) {
     printf("Age %3d month %2d you have $%.2f\n",age/12,age%12,bal);
         bal=bal+bal*rinfo.rate_of_return+rinfo.contribution;
	 rinfo.months--; age++;
  }
  return bal;
}
  void retirement (int startAge, double initial, retire_info working,retire_info retired) {
  int ageRetire=startAge+working.months;
  double bal;
  bal=calBal(startAge,working,initial);
  bal=calBal(ageRetire,retired,bal);
  }

int main () {
  retire_info working,retired;
  //initialisation
  working.months=489;
  working.contribution=1000;
  working.rate_of_return=0.045/12;

  retired.months=384;
  retired.contribution=-4000;
  retired.rate_of_return=0.01/12;
  int age=27*12+3;
  double initial=21345;
  retirement(age,initial,working,retired);
  return 0;
}
