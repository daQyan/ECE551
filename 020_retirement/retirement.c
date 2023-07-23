#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;


double calculator(int startAge, double initial, retire_info info) {
  int age = startAge/12;
  int month = startAge%12;
  double balance = initial;
  for (int i = info.months; i >0; i--) {
    
    printf("Age %3d month %2d you have $%.2lf\n", age, month, balance);
    double increase = balance * info.rate_of_return + info.contribution;
    balance += increase;
    month = (month + 1)%12;
    if (month == 0) {
      age++;
    }
  }
  return balance;
}


void retirement (int startAge, double initial, retire_info working, retire_info retired) {
  double work = calculator(startAge, initial, working);
  calculator(startAge + working.months, work, retired);
}

int main(void) {

  retire_info working_info;
  
  working_info.months = 489;
  working_info.contribution = 1000;
  working_info.rate_of_return = 0.045/12;
  
  
  retire_info retired_info;
  retired_info.months = 384;
  retired_info.contribution = -4000;
  retired_info.rate_of_return = 0.01/12;
  
  retirement(327, 21345, working_info, retired_info);
  return 0;
}