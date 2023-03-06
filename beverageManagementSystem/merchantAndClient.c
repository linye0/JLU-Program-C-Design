#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "merchantAndClient.h"
int isEmpty(pBeverageList list) {
    if (list->next == NULL) return 1;
    else return 0;
}

void add(pBeverageList list, beverageNode newNode) {
    beverageNode p = list;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = newNode;
    newNode->next = NULL;
}

pBeverageList init() {
    pBeverageList head = (pBeverageList)malloc(sizeof(BeverageList));
    head->next = NULL;
    return head;
}

pBeverageList createFromString(char* record) {
    pBeverageList head = (pBeverageList)malloc(sizeof(BeverageList));
    head->next = NULL;
    char tmp[100];
    printf("欢迎使用酒水进货系统!\n");
    printf("请依次输入：酒水品牌 酒水名称 进货时间 进货量 酒水信息\n");
    printf("每一条输入记录以换行符为结束标志，如果你在输入了结束换行符后继续输入了'-1'，则视为输入结束.\n");
    scanf_s("%s", tmp);
    if (strcmp(tmp, "\n") == 0) return head;

    return head;
}

pBeverageList sortBeverage(pBeverageList list, char* key) {

    return NULL;
}

pClientLinkedList initClient(){
    pClientLinkedList head = (pClientLinkedList)malloc(sizeof(ClientLinkedList));
    head->next=NULL;
    return head;
}

void signUp(pClientLinkedList list, char *account, char* password, char* username,int saving,int cost,int grade){
    pClientLinkedList p0=clientSearch(list,account);
    if(p0!=NULL)
    {
        printf("gimmeanothernamebitch");
        return ;//这个地方再调一下
    }
    pClientLinkedList NewClientAccount = (pClientLinkedList)malloc(sizeof(ClientLinkedList));
    pClientLinkedList p=list;
    while(p->next!=NULL){
        p=p->next;
    }
    p->next=NewClientAccount;

    NewClientAccount->next=NULL;

    strcpy_s(NewClientAccount->account,strlen(account)+1,account);
    strcpy_s(NewClientAccount->password,strlen(password)+1,password);
    strcpy_s(NewClientAccount->username,strlen(username)+1,username);
    NewClientAccount->saving=saving;
    NewClientAccount->cost=cost;
    NewClientAccount->grade=grade;
}//已测试

clientNode clientSearch(pClientLinkedList list,char *account){
    pClientLinkedList p=list;
    while(p!=NULL&&strcmp(p->account,account)!=0){
        p=p->next;
    }
    return p;
}//已测试

clientNode signIn(pClientLinkedList list, char* account, char* password,int *status){
    pClientLinkedList p;
    p=clientSearch(list,account);
    if(p!=NULL){
        if(strcmp(p->password,password)==0){
            printf("登陆成功 你好，%s！",p->account);
            *status=1;
        }else{
            printf("密码错误 请输入正确的密码\n");
            *status=0;
        }
    }else{
        printf("抱歉 未能找到输入的用户名T^T\n");
        printf("您是否需要 注册？");
        *status=-1;
    }
    return p;
}//已测试

void changeAccount(pClientLinkedList list,char* account,char*newAccount){
    pClientLinkedList p;
    p=clientSearch(list,account);
    strcpy_s(p->account,strlen(newAccount)+1,newAccount);
    //这里有一个把日志也改了的过程 暂时先搁一下
}

void NewPassword(pClientLinkedList list,char* account,char* newPassword){
    pClientLinkedList p;
    p=clientSearch(list,account);
    strcpy_s(p->account,strlen(newPassword)+1,newPassword);
}

pClientLinkedList clientLogout(pClientLinkedList list,char* account,int *status){
    pClientLinkedList p=list;
    /*if(strcmp(p->account,account)==0)
    {
        pClientLinkedList t=p->next;
        //free(p);
        return t;
    }似乎不用 head节点没东西的*/
    pClientLinkedList p0=p;
    p=p->next;
    while(p!=NULL&&strcmp(p->account,account)!=0){
        p0=p;
        p=p->next;
    }
    if(p!=NULL){
        if(p->next!=NULL){
            p0->next=p->next;
           // free(p);
            *status=0;
        }else{
            p0->next=NULL;
           // free(p);
            *status=0;
        }
    }else
    {
        *status=-1;
    }
    return list;
}

void deposit(clientNode client, int money){
    client->saving+=money;
}

void clientUpgradeCheck(pClientLinkedList list)
{
    if(list->cost>pow(10,2*p->grade))
    {
        list->grade++;
    }
}

void buy(clientNode client, pBeverageList list, int number){
    list->storeNum-=number;
    client->cost+=number*list->price;
    client->saving-=number*list->price;
    clientUpgradeCheck(client);
    recordClient(client,list,number);
}

void recordInit()
{

}

void recordClient(clientNode client, pBeverageList list, int number)
{

}

void showClientRecord()
{

}
