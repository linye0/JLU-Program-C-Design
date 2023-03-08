#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "merchantAndClient.h"
#include "test.h"

int main(void){

    pBeverageList testList = createFromFile("D:\\JLU-Program-C-Design\\Data\\test.txt");

    testList = sortBeverageBrand(testList, -1);

    showStaff(testList);

    deleteBeverage(testList, 1);

    showStaff(testList);

    return 0;

}
