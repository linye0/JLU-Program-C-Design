#include <stdio.h>
#include <string.h>
#include "merchantAndClient.h"
#include<time.h>
int main()
{


    pBeverageList testList = createFromFile("D:\\C-Project\\JLU-Program-C-Design\\data\\test.txt");

        showStaff(testList);

        testList = sortBeverageBrand(testList, -1);

        showStaff(testList);

        searchBeverageInfo(testList, "崭新");

        searchBeverageBrand(testList, "茅台");

        searchBeverageName(testList, "快乐");

        deleteBeverage(testList, 1);

        showStaff(testList);

        changeBeverageInfo(testList, 4, "怡宝怡宝");

        reduceBeverageStoreNum(testList, 4, 12);

        testList = sortBeverageStoreNum(testList, -1);

        showStaff(testList);

        testList = sortBeveragePrice(testList, -1);

        showStaff(testList);

        testList = sortBeverageTime(testList, -1);

        showStaff(testList);

//***********************************************以上是林烨的byd debug*********************************************************
   //调试登录登出注销
    recordInit();
    pClientLinkedList list;
    list=initClient();
    signUp(list,"user1","password1","name1",5000,0,-1);
    signUp(list,"user2","password2","name2",5000,0,0);
    signUp(list,"user3","password3","name3",5000,0,1);

    int status;

    signIn(list,"user1","password1",&status);
    printf("%d",status);

    changeAccount(list,"user2","newuser2");

    NewPassword(list,"newuser2","newpassword2");


   //调试存款以及购买
    pClientLinkedList p=clientSearch(list,"user1");
    p=clientSearch(list,"user3");
    deposit(p,20000);

    pBeverageNode test=searchBeverage_FORREQUEST(testList,"农夫山泉","矿泉水");

    buy(p,test,20);
    p=clientSearch(list,"newuser2");
    buy(p,test,10);

    int i=searchClientBuy("user3 农夫山泉 ");
    printf("总共有%d条记录\n",i);
    printCLientInfo(p);
//*******************************************测试管理员退换货功能***********************************************************
    pclientRequestList list0=clientRequestListInit();
    p=clientSearch(list,"user3");
    printCLientInfo(p);
    clientRequest_PUSH(list0,p,testList,"user3 农夫山泉 ");
    p=clientSearch(list,"newuser2");
    clientRequest_PUSH(list0,p,testList,"name2 农夫山泉 ");
    clientRequest_SHOW(list0);
    clientRequest_POP(list0,2);
    p=clientSearch(list,"newuser2");
    printCLientInfo(p);
    return 0;
}


