#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "merchantAndClient.h"
#include<time.h>

void beveragePrintTime(char* file){
    FILE *fp;
    fp = fopen(file,"at+");
    time_t tmpcal_ptr;
    struct tm *tmp_ptr = NULL;
    time(&tmpcal_ptr);
    tmp_ptr = localtime(&tmpcal_ptr);
    fprintf(fp,"%d.%d.%d", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday);//五个空格
    fclose(fp);
}

void beverageRecordInit()
{
    FILE *fp;
    char file0[]="D:\\JLU-Program-C-Design\\Data\\进货记录.txt";
    fp = fopen(file0,"w");
    fprintf(fp,"%s\n", "进货记录:");
    fclose(fp);
    char file1[]="D:\\JLU-Program-C-Design\\Data\\写入库存.txt";
    fp = fopen(file1, "w");
    fprintf(fp, "%s\n", "写入库存:");
    fclose(fp);
}//用来打表头捏

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

void insertLast(pBeverageList list, pBeverageNode node) {
    pBeverageNode p = list;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = node;
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

    char file0[]="D:\\JLU-Program-C-Design\\Data\\进货记录.txt";
    beveragePrintTime(file0);
    FILE* fpW = fopen(file0, "at+");
    fprintf(fpW, ":\n");
    fprintf(fpW, "%-16s\t%-16s\t%-16s\t%-16s\t%-16s\t%-16s\t%-16s\n", "序号", "品牌", "酒水名", "进货时间", "存量", "价格", "信息");

    if (fp == NULL) {
        printf("\n读取文件失败\n");
        exit(0);
    } else {
        printf("\n读取文件成功\n");
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

        fprintf(fpW, "%-16d\t%-16s\t%-16s\t%-16s\t%-16d\t%-16d\t%-16s\n", insertPos, brand, name, time, storeNum, price, info);

        head = insert(head, newNode, insertPos);

        insertPos++;
    }

    fprintf(fpW, "\n");

    fclose(fpW);

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
        printf("%-12s%-12s%-12s%-12s%-12s%-12s%-12s\n", "序号", "品牌", "酒水名", "进货时间", "存量", "价格", "信息");
        while (p)  //循环将各个节点值输出
        {
            p = p->next;//第一是垃圾值   跳过
            if(p) printf("%-12d%-12s%-12s%-12s%-12d%-12d%-12s\n", i, p->brand, p->name, p->time, p->storeNum, p->price, p->info);
            i++;
        }
    }
}

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

void searchBeverageInfo(pBeverageList list, char* givenInfo) {
    printf("\n开始检索酒水信息\n");
    pBeverageNode p = list->next;
    int i = 1;
    int sum = 0;
    while (p != NULL) {
        if (strstr(p->info, givenInfo)) {
            printf("%-12d%-12s%-12s%-12s%-12d%-12d%-12s\n", i, p->brand, p->name, p->time, p->storeNum, p->price, p->info);
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
            printf("%-12d%-12s%-12s%-12s%-12d%-12d%-12s\n", i, p->brand, p->name, p->time, p->storeNum, p->price, p->info);
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
            printf("%-12d%-12s%-12s%-12s%-12d%-12d%-12s\n", i, p->brand, p->name, p->time, p->storeNum, p->price, p->info);
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

void writeIntoFile(pBeverageList list) {
    char file0[]="D:\\JLU-Program-C-Design\\Data\\写入库存.txt";
    beveragePrintTime(file0);
    FILE* fpW = fopen(file0, "at+");
    fprintf(fpW, ":\n");
    fprintf(fpW, "%-16s\t%-16s\t%-16s\t%-16s\t%-16s\t%-16s\t%-16s\n", "序号", "品牌", "酒水名", "进货时间", "存量", "价格", "信息");
    int writePos = 1;
    pBeverageNode curNode = list;
    while (curNode->next != NULL) {
        curNode = curNode->next;
        fprintf(fpW, "%-16d\t%-16s\t%-16s\t%-16s\t%-16d\t%-16d\t%-16s\n", writePos++, curNode->brand, curNode->name, curNode->time, curNode->storeNum, curNode->price, curNode->info);
    }
}

pBeverageList addFromFile(char* file, pBeverageList list) {
    FILE*fp;
    fp = fopen(file, "r");
    int line_len = 0;
    char ch[1000] = {0};

    char file0[]="D:\\JLU-Program-C-Design\\Data\\进货记录.txt";
    beveragePrintTime(file0);
    FILE* fpW = fopen(file0, "at+");
    fprintf(fpW, ":\n");
    fprintf(fpW, "%-16s\t%-16s\t%-16s\t%-16s\t%-16s\t%-16s\t%-16s\n", "序号", "品牌", "酒水名", "进货时间", "存量", "价格", "信息");

    pBeverageNode head = list;

    if (fp == NULL) {
        printf("\n读取文件失败\n");
        exit(0);
    } else {
        printf("\n读取文件成功\n");
    }

    int writePos = 1;

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

        fprintf(fpW, "%-16d\t%-16s\t%-16s\t%-16s\t%-16d\t%-16d\t%-16s\n", writePos, brand, name, time, storeNum, price, info);

        writePos++;

        pBeverageNode newNode = newBeverageNode(brand, name, time, storeNum, price, info);

        // 判断产品是否已在库存中存在

        pBeverageNode curNode = head->next;

        while(curNode != NULL) {
            if (strcmp(curNode->brand, brand) == 0 && strcmp(curNode->name, name) == 0 && curNode->price == price) {
                curNode->storeNum += storeNum;

                strcat(curNode->info, info);
                break;
            }
            curNode = curNode->next;
        }

        if (curNode == NULL) {

            head = insert(head, newNode, insertPos);

            insertPos++;

        }
    }

    return head;
}

//***************************************linyebyd******************************************************

pClientLinkedList initClient(){
    pClientLinkedList head = (pClientLinkedList)malloc(sizeof(ClientLinkedList));
    head->next=NULL;
    return head;
}

void signUp(pClientLinkedList list, char *account, char* password, char* username,int saving,int cost,int grade){
    pClientLinkedList p0=clientSearch(list,account);
    if(p0!=NULL)
    {
        printf("用户名已存在，请重新输入\n");
        return ;//
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

    recordClientAccount(NewClientAccount,"");
}//

clientNode clientSearch(pClientLinkedList list,char *account){
    pClientLinkedList p=list;
    while(p!=NULL&&strcmp(p->account,account)!=0){
        p=p->next;
    }
    return p;
}//

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
        printf("抱歉 未能找到输入的账号\n");
        printf("您是否需要 注册\n");
        *status=-1;
    }
    return p;
}

void changeAccount(pClientLinkedList list,char* account,char*newAccount){
    pClientLinkedList p;
    p=clientSearch(list,account);
    strcpy_s(p->account,strlen(newAccount)+1,newAccount);
    printf("%s\n",p->account);
    //
}//

void NewPassword(pClientLinkedList list,char* account,char* newPassword){
    pClientLinkedList p;
    p=clientSearch(list,account);
    strcpy_s(p->password,strlen(newPassword)+1,newPassword);
    printf("已修改密码为：%s\n",p->password);
}//

pClientLinkedList clientLogout(pClientLinkedList list,char* account,int *status){
    pClientLinkedList p=list;
    /*if(strcmp(p->account,account)==0)
    {
        pClientLinkedList t=p->next;
        //free(p);
        return t;
    } head*/
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
        printf("\n");
        recordClientAccount(p,"");
    }else
    {
        printf("");
        *status=-1;
    }
    return list;
}//

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
    client->saving-=number*list->price;
    clientUpgradeCheck(client);
    recordClientBuy(client,list,number);
}

void recordInit()
{
    FILE *fp;
    char file0[]="D:\\JLU-Program-C-Design\\Data\\buy.txt";
    fp = fopen(file0,"w");
   fprintf(fp,"%10s%11s%10s%11s%10s%10s%9s\n","账号","用户名","货物品牌","货物名称","货物价格","购买数量","时间");
    fclose(fp);
    char file1[]="D:\\JLU-Program-C-Design\\Data\\client.txt";
    fp = fopen(file1,"w");
    fprintf(fp,"%10s%10s%10s%10s\n","账号","用户名","行为","时间");
    fclose(fp);
}//

void recordClientBuy(clientNode client, pBeverageList list, int number){
    FILE *fp;
    char file[]="D:\\qt\\qt project\\1\\client.txt";
    fp = fopen(file,"at+");
    fprintf(fp,"%10s%10s%10s%10s%10d%10d",client->account,client->username,list->brand,list->name,list->price,number);
    fclose(fp);
    printTime(file);//
}

void recordClientAccount(clientNode client,const char behavior[]){
    FILE *fp;
    char file[]="D:\\JLU-Program-C-Design\\Data\\client.txt";
    fp = fopen(file,"at+");
    fprintf(fp,"%10s%10s%10s",client->account,client->username,behavior);
    fclose(fp);
    printTime(file);//
}

void printTime(char* file){
    FILE *fp;
    fp = fopen(file,"at+");
    time_t tmpcal_ptr;
    struct tm *tmp_ptr = NULL;
    time(&tmpcal_ptr);
    tmp_ptr = localtime(&tmpcal_ptr);
    fprintf(fp,"     %d.%d.%d\n", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday);//
    fclose(fp);
}

int searchClientBuy(char *info)
{

    FILE *fp;
    char file[]="D:\\qt\\qt project\\1\\buy.txt";

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
                //
                continue;
            }
        }
        if('\r'==buf[line_len-1]){
            buf[line_len-1]='\0';
            line_len--;
            if(0==line_len){
                //
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
    if(0== feof ){
        printf("fgets error\n");
        return -1;
    }

    fclose(fp);

    return sum;
}

//ɡ-->

//


int getLinkTotalNodeNum(pBeverageList head)
{
        int cnt = 0;
        pBeverageList p = head;
        while(p != NULL){
        cnt++;
        p = p->next;
}
        return cnt;
}
