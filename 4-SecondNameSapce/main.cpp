#include <iostream>
#include <stdio.h>
#include "cir.h"


using namespace cir;

int main()
{
    double myRadius = 5;
    std::cout << "namespace" << std::endl;
  //  printf("lenth: %lf, are:%lf\n",cir::getLenthOfCircle(myRadius),
  //         cir::getAifCircle(myRadius));

    printf("lenth: %lf, are:%lf\n",getLenthOfCircle(myRadius),
                      getAifCircle(myRadius));
    return 0;
}
