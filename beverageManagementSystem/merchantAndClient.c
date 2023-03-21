#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "merchantAndClient.h"
int isEmpty(pBeverageList list) {
    if (list->next == NULL) return 1;
    else return 0;
}

void add(pBeverageList list, pBeverageNode newNode) {
    pBeverageNode p = list;
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

pBeverageNode find(pBeverageList head, int i) {
    int j = 1;
    pBeverageNode p = head;

    if (i < 1) {
        printf("\n链表长度要大于零\n");
        return NULL;
    }

    while (p && i != j) {
        p = p->next;
        j++;
    }

    return p;

}

pBeverageNode insert(pBeverageList list, pBeverageNode node, int i) {
    pBeverageNode p;
    p = find(list, i);

    if (!p && i != 0) {
        printf("找不到第%d个数据，无法插入数据\n", i);
    } else {
        if (i == 0) {
            node->next = list;
            list = node;
        } else {
            node->next = p->next;
            p->next = node;
        }
    }

    return list;
}

pBeverageNode newBeverageNode(char brand[], char name[], char time[], int storeNum, int price, char info[]) {
    pBeverageNode node = malloc(sizeof(BeverageNode));
    strcpy(node->brand, brand);
    strcpy(node->name, name);
    strcpy(node->time, time);
    node->storeNum = storeNum;
    node->price = price;
    strcpy(node->info, info);
    node->next = NULL;
    return node;
}

pBeverageList createFromFile(char* file) {
    FILE*fp;
    fp = fopen(file, "r");
    int line_len = 0;
    char ch[1000] = {0};

    pBeverageNode head = (pBeverageNode)malloc(sizeof(BeverageNode));
    head->next = NULL;

    if (fp == NULL) {
        printf("\nfail\n");
        exit(0);
    } else {
        printf("\nnice\n");
    }

    int insertPos = 1;

    while(fgets(ch, 1000, fp)) {
        line_len = strlen(ch);
        if ('\n' == ch[line_len - 1]) {
            ch[line_len - 1] = '\0';
            line_len--;
            if (0 == line_len) {
                continue;
            }
        }
        // 对ch进行分割

        char brand[100] = {0}; char name[100] = {0}; char time[100] = {0};  int storeNum = 0; int price = 0; char info[100] = {0};

        int i = 0;

        char *p = strtok(ch, " ");
        while(p=strtok(NULL, " ")){//使用第一个参数为NULL来提取子串
            switch(i) {
                case 0:
                    strcpy(brand, p);
                    break;
                case 1:
                    strcpy(name, p);
                    break;
                case 2:
                    strcpy(time, p);
                    break;
                case 3:
                    storeNum = atoi(p);
                    break;
                case 4:
                    price = atoi(p);
                    break;
                case 5:
                    strcpy(info, p);
                    break;
            }
            i++;
        }

        pBeverageNode newNode = newBeverageNode(brand, name, time, storeNum, price, info);

        head = insert(head, newNode, insertPos);

        insertPos++;
    }

    return head;
}

void showStaff(pBeverageList list) {
    pBeverageNode p;
    p = list;
    int i = 1;
    if (!p) //如果head指针为空说明链表为空
    {
        printf("\n库存为空\n");
    }
    else
    {
        printf("\n当前库存如下:\n");
        printf("        品牌        酒水名        进货时间        存量        价格         信息\n");
        while (p)  //循环将各个节点值输出
        {
            p = p->next;//第一是垃圾值   跳过
            if(p) printf("%d：%10s%13s%16s%12d%11d%17s\n", i, p->brand, p->name, p->time, p->storeNum, p->price, p->info);
            i++;
        }
    }
}
//*************************************以下是按各种属性排序************************************************************
pBeverageList sortBeverageTime(pBeverageList list, int key) {
    // 新建一个储存排序后结点的链表
    pBeverageList retList, insertPos, p, maxNode, prevP, prevMaxNode;
    retList = (pBeverageList)malloc(sizeof(BeverageList));
    retList->next = NULL;
    insertPos = retList;
    p = maxNode = list->next;
    prevP = prevMaxNode = NULL;
    while (p) {
        maxNode = p;
        prevP = prevMaxNode = NULL;
        if (p->next == NULL) {
            // 如果此时待排序链表里面只有p一个结点，就直接把p插入
            insertPos->next = p;
            p->next = NULL;
            p = p->next;
        } else {
            pBeverageNode cur = p;
            while (cur->next) {
                if (strcmp(cur->next->time, maxNode->time) * key > 0) {
                    maxNode = cur->next;
                    prevMaxNode = cur;
                }
                cur = cur->next;
                // 找到最大结点，令maxNode指向它，prevMaxNode指向它的前一个结点
            }
            // 插入步骤
            // 如果prevMaxNode == NULL，说明最大结点就是p结点，此时直接将p插入链表，并且让p指向下一个结点
            if (prevMaxNode == NULL) {
                pBeverageNode nextP = p->next;
                p->next = NULL;
                insertPos->next = p;
                p = nextP;
            } else {
                // 如果prevMaxNode != NULL，将maxNode插入链表，不用将p后移
                prevMaxNode->next = maxNode->next;
                maxNode->next = NULL;
                insertPos->next = maxNode;
            }
            // 将p和insertPos后移一位
            insertPos = insertPos->next;
        }
    }
    char* outStr = {0};
    if (key > 0) {
        outStr = "降序";
    } else {
        outStr = "升序";
    }
    printf("\n根据进货时间关键词对酒水进行了%s排序\n", outStr);
    return retList;
}

pBeverageList sortBeverageBrand(pBeverageList list, int key) {
    // 新建一个储存排序后结点的链表
    pBeverageList retList, insertPos, p, maxNode, prevP, prevMaxNode;
    retList = (pBeverageList)malloc(sizeof(BeverageList));
    retList->next = NULL;
    insertPos = retList;
    p = maxNode = list->next;
    prevP = prevMaxNode = NULL;
    while (p) {
        maxNode = p;
        prevP = prevMaxNode = NULL;
        if (p->next == NULL) {
            // 如果此时待排序链表里面只有p一个结点，就直接把p插入
            insertPos->next = p;
            p->next = NULL;
            p = p->next;
        } else {
            pBeverageNode cur = p;
            while (cur->next) {
                if (strcmp(cur->next->brand, maxNode->brand) * key > 0) {
                    maxNode = cur->next;
                    prevMaxNode = cur;
                }
                cur = cur->next;
                // 找到最大结点，令maxNode指向它，prevMaxNode指向它的前一个结点
            }
            // 插入步骤
            // 如果prevMaxNode == NULL，说明最大结点就是p结点，此时直接将p插入链表，并且让p指向下一个结点
            if (prevMaxNode == NULL) {
                pBeverageNode nextP = p->next;
                p->next = NULL;
                insertPos->next = p;
                p = nextP;
            } else {
                // 如果prevMaxNode != NULL，将maxNode插入链表，不用将p后移
                prevMaxNode->next = maxNode->next;
                maxNode->next = NULL;
                insertPos->next = maxNode;
            }
            // 将p和insertPos后移一位
            insertPos = insertPos->next;
        }
    }
    char* outStr = {0};
    if (key > 0) {
        outStr = "降序";
    } else {
        outStr = "升序";
    }
    printf("\n根据品牌关键词对酒水进行了%s排序\n", outStr);
    return retList;
}

pBeverageList sortBeverageStoreNum(pBeverageList list, int key) {
    // 新建一个储存排序后结点的链表
    pBeverageList retList, insertPos, p, maxNode, prevP, prevMaxNode;
    retList = (pBeverageList)malloc(sizeof(BeverageList));
    retList->next = NULL;
    insertPos = retList;
    p = maxNode = list->next;
    prevP = prevMaxNode = NULL;
    while (p) {
        maxNode = p;
        prevP = prevMaxNode = NULL;
        if (p->next == NULL) {
            // 如果此时待排序链表里面只有p一个结点，就直接把p插入
            insertPos->next = p;
            p->next = NULL;
            p = p->next;
        } else {
            pBeverageNode cur = p;
            while (cur->next) {
                if ((cur->next->storeNum - maxNode->storeNum) * key > 0) {
                    maxNode = cur->next;
                    prevMaxNode = cur;
                }
                cur = cur->next;
                // 找到最大结点，令maxNode指向它，prevMaxNode指向它的前一个结点
            }
            // 插入步骤
            // 如果prevMaxNode == NULL，说明最大结点就是p结点，此时直接将p插入链表，并且让p指向下一个结点
            if (prevMaxNode == NULL) {
                pBeverageNode nextP = p->next;
                p->next = NULL;
                insertPos->next = p;
                p = nextP;
            } else {
                // 如果prevMaxNode != NULL，将maxNode插入链表，不用将p后移
                prevMaxNode->next = maxNode->next;
                maxNode->next = NULL;
                insertPos->next = maxNode;
            }
            // 将p和insertPos后移一位
            insertPos = insertPos->next;
        }
    }
    char* outStr = {0};
    if (key > 0) {
        outStr = "降序";
    } else {
        outStr = "升序";
    }
    printf("\n根据存量关键词对酒水进行了%s排序\n", outStr);
    return retList;
}

pBeverageList sortBeveragePrice(pBeverageList list, int key) {
    // 新建一个储存排序后结点的链表
    pBeverageList retList, insertPos, p, maxNode, prevP, prevMaxNode;
    retList = (pBeverageList)malloc(sizeof(BeverageList));
    retList->next = NULL;
    insertPos = retList;
    p = maxNode = list->next;
    prevP = prevMaxNode = NULL;
    while (p) {
        maxNode = p;
        prevP = prevMaxNode = NULL;
        if (p->next == NULL) {
            // 如果此时待排序链表里面只有p一个结点，就直接把p插入
            insertPos->next = p;
            p->next = NULL;
            p = p->next;
        } else {
            pBeverageNode cur = p;
            while (cur->next) {
                if ((cur->next->price - maxNode->price) * key > 0) {
                    maxNode = cur->next;
                    prevMaxNode = cur;
                }
                cur = cur->next;
                // 找到最大结点，令maxNode指向它，prevMaxNode指向它的前一个结点
            }
            // 插入步骤
            // 如果prevMaxNode == NULL，说明最大结点就是p结点，此时直接将p插入链表，并且让p指向下一个结点
            if (prevMaxNode == NULL) {
                pBeverageNode nextP = p->next;
                p->next = NULL;
                insertPos->next = p;
                p = nextP;
            } else {
                // 如果prevMaxNode != NULL，将maxNode插入链表，不用将p后移
                prevMaxNode->next = maxNode->next;
                maxNode->next = NULL;
                insertPos->next = maxNode;
            }
            // 将p和insertPos后移一位
            insertPos = insertPos->next;
        }
    }
    char* outStr = {0};
    if (key > 0) {
        outStr = "降序";
    } else {
        outStr = "升序";
    }
    printf("\n根据价格关键词对酒水进行了%s排序\n", outStr);
    return retList;
}

void deleteBeverage(pBeverageList list, int pos) {
    int i = 0;
    pBeverageNode tarNode = list;
    pBeverageNode prevTarNode = NULL;
    while (i < pos && tarNode->next) {
        if (prevTarNode == NULL) prevTarNode = tarNode;
        tarNode = tarNode->next;
        i++;
    }
    // 删除tarNode结点
    prevTarNode->next = tarNode->next;
    free(tarNode);
    printf("\n删除了编号为%d的酒水\n", i);
}
//*************************************以下是按各种属性搜索************************************************************
void searchBeverageInfo(pBeverageList list, char* givenInfo) {
    printf("\n开始检索酒水信息\n");
    pBeverageNode p = list->next;
    int i = 1;
    int sum = 0;
    while (p != NULL) {
        if (strstr(p->info, givenInfo)) {
            printf("%d: %s %s %s %d %d %s\n", i, p->brand, p->name, p->time, p->storeNum, p->price, p->info);
            sum++;
        }
        i++;
        p = p->next;
    }
    printf("为您搜索'%s'关键字，共搜索到%d条记录\n", givenInfo, sum);
    return;
}

void searchBeverageBrand(pBeverageList list, char* givenBrand) {
    printf("\n开始检索品牌\n");
    pBeverageNode p = list->next;
    int i = 1;
    int sum = 0;
    while (p != NULL) {
        if (strstr(p->brand, givenBrand)) {
            printf("%d: %s %s %s %d %d %s\n", i, p->brand, p->name, p->time, p->storeNum, p->price, p->info);
            sum++;
        }
        i++;
        p = p->next;
    }
    printf("为您搜索'%s'关键字，共搜索到%d条记录\n", givenBrand, sum);
    return;
}

void searchBeverageName(pBeverageList list, char* givenName) {
    printf("\n开始检索名称\n");
    pBeverageNode p = list->next;
    int i = 1;
    int sum = 0;
    while (p != NULL) {
        if (strstr(p->name, givenName)) {
            printf("%d: %s %s %s %d %d %s\n", i, p->brand, p->name, p->time, p->storeNum, p->price, p->info);
            sum++;
        }
        i++;
        p = p->next;
    }
    printf("为您搜索'%s'关键字，共搜索到%d条记录\n", givenName, sum);
    return;
}

void changeBeverageInfo(pBeverageList list, int number, char* givenInfo) {
    pBeverageNode node = find(list, number + 1);
    strcpy(node->info, givenInfo);
    printf("\n修改了编号为%d的酒水的信息\n", number);
}

void reduceBeverageStoreNum(pBeverageList list, int number, int reduceNum) {
    pBeverageNode node = find(list, number + 1);
    if (node->storeNum < reduceNum) {
        printf("\n酒水库存不足！\n");
        return;
    } else {
        node->storeNum -= reduceNum;
    }
}

//***************************************以上是linye的byd函数实现******************************************************
pClientLinkedList initClient(){
    pClientLinkedList head = (pClientLinkedList)malloc(sizeof(ClientLinkedList));
    head->next=NULL;
    return head;
}

void signUp(pClientLinkedList list, char *account, char* password, char* username,float saving,float cost,int grade){
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

    recordClientAccount(NewClientAccount,"注册");
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
            if(p->grade>=0)
            {
                recordClientAccount(p,"普通登录");
                *status=1;
            }else
            {
                recordClientAccount(p,"管理登录");
                *status=4;
            }
        }else{

            recordClientAccount(p,"登录失败");
            printf("密码错误 请输入正确的密码\n");
            *status=0;
        }
    }else{
        printf("抱歉 未能找到输入的用户名T^T\n");
        printf("您是否需要 注册\n");
        *status=-1;
    }
    return p;
}//已测试

void changeAccount(pClientLinkedList list,char* account,char*newAccount){
    pClientLinkedList p;
    p=clientSearch(list,account);
    strcpy_s(p->account,strlen(newAccount)+1,newAccount);
    printf("成功更改账号为：%s\n",p->account);
    //这里有一个把日志也改了的过程 暂时先搁一下
}//已测试

void NewPassword(pClientLinkedList list,char* account,char* newPassword){
    pClientLinkedList p;
    p=clientSearch(list,account);
    strcpy_s(p->password,strlen(newPassword)+1,newPassword);
    printf("成功更改密码为：%s\n",p->password);
}//已测试

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
        printf("注销成功\n");
        recordClientAccount(p,"注销");
    }else
    {
        printf("查无此人");
        *status=-1;
    }
    return list;
}//已测试

void deposit(clientNode client, int money){
    client->saving+=money;

}

void clientUpgradeCheck(pClientLinkedList list)
{
    if(list->cost>pow(10,2*list->grade))
    {
        list->grade++;
    }
}

void buy(clientNode client, pBeverageList list, int number){
    list->storeNum-=number;
    client->cost+=number*list->price*(1-0.06*client->grade);
    client->saving-=number*list->price*(1-0.06*client->grade);
    recordClientBuy(client,list,number,-number*list->price*(1-0.06*client->grade));
    clientUpgradeCheck(client);
}

void recordInit()
{
    FILE *fp;
    char file0[]="D:\\C-Project\\JLU-Program-C-Design\\data\\clientBuyLog.txt";
    fp = fopen(file0,"w");
    fprintf(fp,"%10s%11s%10s%11s%10s%10s%10s%9s\n","账号","用户名","货物品牌","货物名称","货物价格","购买数量","花费","时间");
    fclose(fp);
    char file1[]="D:\\C-Project\\JLU-Program-C-Design\\data\\clientAccountLog.txt";
    fp = fopen(file1,"w");
    fprintf(fp,"%10s%10s%10s%10s\n","账号","用户名","行为","时间");
    fclose(fp);
}//用来打表头捏

void recordClientBuy(clientNode client, pBeverageList list, int number,float cost){
    FILE *fp;
    char file[]="D:\\C-Project\\JLU-Program-C-Design\\data\\clientBuyLog.txt";
    fp = fopen(file,"at+");
    fprintf(fp,"%10s%10s%10s%10s%10d%10d%10.2f",client->account,client->username,list->brand,list->name,list->price,number,cost);
    fclose(fp);
    printTime(file);//输出一下时间
}

void recordClientAccount(clientNode client,const char behavior[]){
    FILE *fp;
    char file[]="D:\\C-Project\\JLU-Program-C-Design\\data\\clientAccountLog.txt";
    fp = fopen(file,"at+");
    fprintf(fp,"%10s%10s%10s",client->account,client->username,behavior);
    fclose(fp);
    printTime(file);//输出一下时间
}

void printTime(char* file){
    FILE *fp;
    fp = fopen(file,"at+");
    time_t tmpcal_ptr;
    struct tm *tmp_ptr = NULL;
    time(&tmpcal_ptr);
    tmp_ptr = localtime(&tmpcal_ptr);
    fprintf(fp,"     %d.%d.%d %d:%d:%d\n", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday,tmp_ptr->tm_hour,tmp_ptr->tm_min,tmp_ptr->tm_sec);//五个空格
    fclose(fp);
}

int searchClientBuy(char *info)
{

    FILE *fp;
    char file[]="D:\\C-Project\\JLU-Program-C-Design\\data\\clientBuyLog.txt";

    int line_len=0;
    char buf[1024]={0};
    char Info[20];
    strcpy_s(Info,strlen(info)+1,info);
    fp=fopen(file,"r");
    int sum=0;
    int sum0=0;
    char *token=strtok(Info," ");
    char s[10][20];
    while( token != NULL ) {
        sum0++;
        strcpy_s(s[sum0],strlen(token)+1,token);
        token = strtok(NULL," ");
    }
    while(fgets(buf,1024,fp)){

        line_len=strlen(buf);
        //
        if('\n'==buf[line_len-1]){
            buf[line_len-1]='\0';
            line_len--;
            if(0==line_len){
                //空行
                continue;
            }
        }
        if('\r'==buf[line_len-1]){
            buf[line_len-1]='\0';
            line_len--;
            if(0==line_len){
                //空行
                continue;
            }
        }
        //]
        int p=1;
        int flag=1;
        while(p<=sum0)
        {
            char *ptr=strstr(buf,s[p]);
            if(ptr==NULL)
                flag=0;
            p++;
        }
        if(flag)
        {
            printf("%s\n", buf);
            sum++;
        }
    }
    if(0== &feof ){
        printf("fgets error\n");
        return -1;
    }

    fclose(fp);

    return sum;
}

void printCLientInfo(clientNode p)
{
    char account[]="账号";
    char username[]="用户名";
    char cost[]="已消费金额";
    char saving[]="账户储蓄金";
    char grade[]="用户等级";
    char grade0[]="管理员";
    printf("*********************\n");
    printf("%10s%10s\n",account,p->account);
    printf("%10s%10s\n",username,p->username);
    printf("%10s%10.2f\n",cost,p->cost);
    printf("%10s%10.2f\n",saving,p->saving);
    if(p->grade>0){
        printf("%10s%10d\n",grade,p->grade);
    }else{
        printf("%10s%10s\n",grade,grade0);
    }
    printf("*********************\n");
}
//做一个查找购买记录的功能即可“我的-->”
//库存不够了怎么办
//写一个退换货的事情 建一个新的链表然后让管理员同意？？这里得考虑一下那个量的事情，。
pclientRequestList clientRequestListInit(){
    pclientRequestList head = (pclientRequestList)malloc(sizeof(clientRequestList));
    head->next=NULL;
    return head;
}

void searchClientBuy_FORREQUEST(char *info,char requestInfo[])
{

    FILE *fp;
    char file[]="D:\\C-Project\\JLU-Program-C-Design\\data\\clientBuyLog.txt";

    int line_len=0;
    char buf[1024]={0};
    char Info[20];
    strcpy_s(Info,strlen(info)+1,info);
    fp=fopen(file,"r");
    int sum0=0;
    char *token=strtok(Info," ");
    char s[10][20];
    while( token != NULL ) {
        sum0++;
        strcpy_s(s[sum0],strlen(token)+1,token);
        token = strtok(NULL," ");
    }
    while(fgets(buf,1024,fp)){

        line_len=strlen(buf);
        //
        if('\n'==buf[line_len-1]){
            buf[line_len-1]='\0';
            line_len--;
            if(0==line_len){
                //空行
                continue;
            }
        }
        if('\r'==buf[line_len-1]){
            buf[line_len-1]='\0';
            line_len--;
            if(0==line_len){
                //空行
                continue;
            }
        }
        //]
        int p=1;
        int flag=1;
        while(p<=sum0)
        {
            char *ptr=strstr(buf,s[p]);
            if(ptr==NULL)
                flag=0;
            p++;
        }
        if(flag)
        {
            strcpy_s(requestInfo,strlen(buf)+1,buf);

        }
    }
    if(0== &feof ){
        printf("fgets error\n");
    }

    fclose(fp);


}

pBeverageList searchBeverage_FORREQUEST(pBeverageList list , char* giveBrand,char* giveName) {
    pBeverageNode p = list->next;
    while (p != NULL) {
        if (strstr(p->name, giveName)&&strstr(p->brand, giveBrand)) {
            return p;
        }
        p = p->next;
    }
    return p;
}

void clientRequest_PUSH(pclientRequestList list,clientNode client,pBeverageList listb,char *info){
    char Info[100];
    strcpy_s(Info,strlen(info)+1,info);
    searchClientBuy_FORREQUEST(info,Info);
    strtok(Info," ");
    strtok(NULL," ");
    char *tokenBrand=strtok(NULL," ");
    char *tokenName=strtok(NULL," ");
    strtok(NULL," ");
    int number=atoi(strtok(NULL," "));
    float cost=atof(strtok(NULL," "));

    char *time=strtok(NULL," ");

    pBeverageNode pb0=searchBeverage_FORREQUEST(listb,tokenBrand,tokenName);
    pclientRequestList NewClientRequest = (pclientRequestList)malloc(sizeof(clientRequestList));
    pclientRequestList p=list;
    while(p->next!=NULL){
        p=p->next;
    }
    p->next=NewClientRequest;
    NewClientRequest->next=NULL;
    strcpy_s(NewClientRequest->time,strlen(time)+1,time);
    NewClientRequest->pb=pb0;
    NewClientRequest->pc=client;
    NewClientRequest->number=number;
    NewClientRequest->cost=cost;
}


void clientRequest_POP(pclientRequestList list,int choice){
    if(choice!=0){
        int i=1;
        pclientRequestList p0=list;
        pclientRequestList p=list->next;
        //先改数据

        while(p!=NULL&&i<choice){
            i++;
            p0=p0->next;
            p=p->next;
         }
        while(p->pc->cost-p->cost<pow(10,2*p->pc->grade))
        {
            p->pc->grade--;
        }
        p->pc->saving-=p->cost;
        p->pc->cost+=p->cost;
        p->pb->storeNum+=p->number;
        recordClientBuy(p->pc,p->pb,p->number,-p->cost);
        p0->next=p->next;

    }
    printf("你已经同意了一条退货需求！剩下的退货请求还有这些\n");
    clientRequest_SHOW(list);
}

void clientRequest_SHOW(pclientRequestList list){
    pclientRequestList p=list->next;
    char *request="退货";
    printf("***********************************************************************************\n");
    printf("%10s%10s%10s%10s%10s%15s\n","账号","品牌","名称","请求","数量","时间");
    printf("-----------------------------------------------------------------------------------\n");
    while(p!=NULL){
        printf("%10s%10s%10s%10s%10d%15s\n",p->pc->account,p->pb->brand,p->pb->name,request,p->number,p->time);
        p=p->next;
    }
    printf("***********************************************************************************\n");
}
