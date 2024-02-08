/*
 * Copyright ©2023 Leonardo Ochoa
 */
// Leonardo Ochoa
// lochoa2@uw.edu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void pie(double *val) {
  double temp = 3;
  if (*val > 0) {
    temp += 4.0 / (2 * 3 * 4);
  }
  if (*val > 1) {
    temp -= 4.0 / (4 * 5 * 6);
  }
  for (int i = 3; i <= (int)(*val); i++) {
    double mul = i * 2;
    if (i % 2 == 1) {
      temp +=  4.0 / (mul * (mul + 1) * (mul + 2));
    } else {
      temp -=  4.0 / (mul * (mul + 1) * (mul + 2));
    }
  }
  *val = temp;
}



void demo(char* c){
  char* h = "123456";

  //char *c = (char *) malloc(2);
  strncpy(c, h, 2);
  // printf("%s", b);
  // c = b;
}

int main(int argc, char* argv[]) {

  // printf("double:  %f \n", atof(argv[1]));
  // if (argc != 2) {
  //   printf("your command should have 2 arguments \n");
  // } else {
  //   char* num = argv[1];
  //   if (!isdigit(*num) || atoi(num) != atof(num)) {
  //     printf("not an integer \n");
  //   } else {
  //     double val = atof(num);
  //     pie(&val);
  //     printf("%.20f \n", val);
  //   }
  // }
  // return EXIT_SUCCESS;

  char* c = (char *) malloc(2);
  demo(c);
  printf("%s", c);

}
