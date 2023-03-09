#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "merchantAndClient.h"

int main(void){
    pBeverageList testList = createFromFile("D:\\CSdiy\\JLU Program C Design\\Data\\test.txt");

    showStaff(testList);

    testList = sortBeverageBrand(testList, -1);

    showStaff(testList);

    searchBeverageInfo(testList, "Õ¸ÐÂ");

    searchBeverageBrand(testList, "Ã©Ì¨");

    searchBeverageName(testList, "¿ìÀÖ");

    deleteBeverage(testList, 1);

    showStaff(testList);

    changeBeverageInfo(testList, 4, "âù±¦âù±¦");

    reduceBeverageStoreNum(testList, 4, 12);

    testList = sortBeverageStoreNum(testList, -1);

    showStaff(testList);

    testList = sortBeveragePrice(testList, -1);

    showStaff(testList);

    testList = sortBeverageTime(testList, -1);

    showStaff(testList);
}
