#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void Signup(pClientLinkedList list, char *account, char* password, char* username,int saving){
    pClientLinkedList NewClientAccount = (pClientLinkedList)malloc(sizeof(ClientLinkedList));
    pClientLinkedList p=list;
    while(p->next!=NULL){
        p=p->next;
    }
    p->next=NewClientAccount;

    NewClientAccount->next=NULL;
    strcpy(NewClientAccount->data->account,account);
    strcpy(NewClientAccount->data->password,password);
    strcpy(NewClientAccount->data->username,username);
    NewClientAccount->data->saving=saving;
}

clientNode clientSearch(pClientLinkedList list,char *account){
    pClientLinkedList p=list;
    while(p!=NULL&&!strcmp(p->data->account,account)){
        p=p->next;
    }
    return p;
}

clientNode signIn(pClientLinkedList list, char* account, char* password,int *status){
    pClientLinkedList p;
    p=clientSearch(list,account);
    if(p!=NULL){
        if(!strcmp(p->data->password,password)){
            printf("登陆成功 你好，%s！",p->data->account);
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
}

void chageAccount(pClientLinkedList list,char* account,char*newAccount){
    pClientLinkedList p;
    p=clientSearch(list,account);
    strcpy(p->data->account,newAccount);
    //这里有一个把日志也改了的过程 暂时先搁一下
}

void NewPassword(pClientLinkedList list,char* account,char* newPassword){
    pClientLinkedList p;
    p=clientSearch(list,account);
    strcpy(p->data->account,newPassword);
}

pClientLinkedList clientLogout(pClientLinkedList list,char* account,int *status){
    pClientLinkedList p=list;
    if(strcmp(p->data->account,account)==0)
    {
        pClientLinkedList t=p->next;
        free(p);
        return t;
    }
    pClientLinkedList p0=p;
    p=p->next;
    while(p!=NULL&&!strcmp(p->data->account,account)){
        p0=p;
        p=p->next;
    }
    if(p!=NULL){
        if(p->next!=NULL){
            p0->next=p->next;
            free(p);
            *status=0;
        }else{
            p0->next=NULL;
            free(p);
            *status=0;
        }
        return list;
    }else
    {
        *status=-1;
        return list;
    }
}

void deposit(clientNode client, int money){
    client->data->saving+=money;
}

void buy(clientNode client, pBeverageList list, int number){
    list->storeNum-=number;
   // client->data->saving-=number*list->哥们你价格呢
}
