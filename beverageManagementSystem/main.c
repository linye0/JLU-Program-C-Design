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

//***********************************************���������ǵ�byd debug*********************************************************
   //���Ե�¼�ǳ�ע��
    recordInit();
    pClientLinkedList list;
    list=initClient();
    signUp(list,"user1","password1","name1",5000,0,-1);
    signUp(list,"user2","password2","name2",5000,0,1);
    signUp(list,"user3","password3","name3",5000,0,1);

    int status;

    signIn(list,"user1","password1",&status);
printf("%d",status);

    changeAccount(list,"user2","newuser2");

    NewPassword(list,"newuser2","newpassword2");

    clientLogout(list,"user3",&status);
   //���Դ���Լ�����
    pClientLinkedList p=clientSearch(list,"user1");

    deposit(p,20000);

    pBeverageNode test=newBeverageNode("ũ��ɽȪ","��Ȫˮ","2023",20000,20,"default");

    buy(p,test,20);
    p=clientSearch(list,"newuser2");
    buy(p,test,10);

    int i=searchClientBuy("user1 ũ��ɽȪ ");
    printf("�ܹ���%d����¼\n",i);
    printCLientInfo(p);
    return 0;
}


