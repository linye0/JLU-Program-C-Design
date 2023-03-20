#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "merchantAndClient.h"
#include<time.h>

int main(void){

    beverageRecordInit();

    pBeverageList testList = createFromFile("D:\\JLU-Program-C-Design\\Data\\������Ŀ.txt");

    showStaff(testList);

    testList = sortBeverageBrand(testList, -1);

    showStaff(testList);

    searchBeverageInfo(testList, "ո��");

    searchBeverageBrand(testList, "ę́");

    searchBeverageName(testList, "����");

    deleteBeverage(testList, 1);

    showStaff(testList);

    changeBeverageInfo(testList, 4, "��������");

    reduceBeverageStoreNum(testList, 4, 12);

    testList = sortBeverageStoreNum(testList, -1);

    showStaff(testList);

    testList = sortBeveragePrice(testList, -1);

    showStaff(testList);

    testList = sortBeverageTime(testList, -1);

    showStaff(testList);

    testList = addFromFile("D:\\JLU-Program-C-Design\\Data\\test.txt", testList);

    showStaff(testList);
}
