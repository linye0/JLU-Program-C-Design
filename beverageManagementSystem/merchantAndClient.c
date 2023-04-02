#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "merchantAndClient.h"
#define fileClientBuyLog "D:\\C-Project\\JLU-Program-C-Design\\data\\buy.txt"
#define fileClientAccountLog "D:\\C-Project\\JLU-Program-C-Design\\data\\client.txt"
#define fileClientInfoLog "D:\\C-Project\\JLU-Program-C-Design\\data\\clientInfo.txt"
#define BEVEPATH1 "D:\\C-Project\\JLU-Program-C-Design\\data\\进货记录.txt"
#define BEVEPATH2 "D:\C-Project\JLU-Program-C-Design\data\\写入库存.txt"
#define autoSaveStore "D:\C-Project\JLU-Program-C-Design\data\\autoSave.txt"
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
    char file0[]=BEVEPATH1;
    fp = fopen(file0,"w");
    fclose(fp);
    char file1[]=BEVEPATH2;
    fp = fopen(file1, "w");
    fclose(fp);
    char file2[]=autoSaveStore;
    fp = fopen(file2, "at+");
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

void insertLast(pBeverageList list, pBeverageNode node) {
    pBeverageNode p = list;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = node;
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

pBeverageNode newBeverageNode(char brand[], char name[], char time[], int storeNum, float price, char info[], pInteractInfo pInfo) {
    pBeverageNode node = malloc(sizeof(BeverageNode));
    strcpy(node->brand, brand);
    strcpy(node->name, name);
    strcpy(node->time, time);
    node->storeNum = storeNum;
    node->price = price;
    strcpy(node->info, info);
    node->next = NULL;
    if (!reduceSaving(pInfo, storeNum * price)) return NULL;
    return node;
}

pBeverageList createFromFile(char* file, pInteractInfo pInfo) {
    FILE*fp;
    fp = fopen(file, "r");
    int line_len = 0;
    char ch[1000] = {0};

    pBeverageNode head = (pBeverageNode)malloc(sizeof(BeverageNode));
    head->next = NULL;

    char file0[]=BEVEPATH1;
    beveragePrintTime(file0);
    FILE* fpW = fopen(file0, "at+");
    fprintf(fpW, "\n");
    fprintf(fpW, "\n");
    fprintf(fpW, "%-16s\t%-16s\t%-16s\t%-16s\t%-16s\t%-16s\t%-16s\n", "序号", "品牌", "酒水名", "进货时间", "存量", "价格", "信息");

    if (fp == NULL) {
        printf("\n读取文件失败\n");
        return NULL;
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

        pBeverageNode newNode = newBeverageNode(brand, name, time, storeNum, price, info, pInfo);

        if (newNode == NULL) return head;

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
        printf("%-16s\t%-16s\t%-16s\t%-16s\t%-16s\t%-16s\t%-16s\n", "序号", "品牌", "酒水名", "进货时间", "存量", "价格", "信息");
        while (p)  //循环将各个节点值输出
        {
            p = p->next;//第一是垃圾值   跳过
            if(p) printf("%-16d\t%-16s\t%-16s\t%-16s\t%-16d\t%-16.2f\t%-16s\t\n", i, p->brand, p->name, p->time, p->storeNum, p->price, p->info);
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
        prevTarNode=tarNode;
        tarNode=tarNode->next;
        i++;
    }
    // 删除tarNode结点
    if(prevTarNode==NULL){
        return;
    }
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

void writeIntoFile(pBeverageList list) {
    char file0[]=BEVEPATH2;
    //beveragePrintTime(file0);
    FILE* fpW = fopen(file0, "w");
    if (!fpW) {
        printf("++++\n");
        return;
    }
    int writePos = 1;
    pBeverageNode curNode = list;
    if (curNode == NULL) return;
    while (curNode->next != NULL) {
        curNode = curNode->next;
        fprintf(fpW, "%-16d %-16s %-16s %-16s %-16d %-16.2f %-16s\n", writePos++, curNode->brand, curNode->name, curNode->time, curNode->storeNum, curNode->price, curNode->info);
    }
    fclose(fpW);
}

void writeIntoFileAuto(pBeverageList list) {
    char file0[]=autoSaveStore;
    //beveragePrintTime(file0);
    FILE* fpW = fopen(file0, "w");
    if (!fpW) {
        printf("++++\n");
        return;
    }
    int writePos = 1;
    pBeverageNode curNode = list;
    if (curNode == NULL) return;
    while (curNode->next != NULL) {
        curNode = curNode->next;
        fprintf(fpW, "%-16d %-16s %-16s %-16s %-16d %-16.2f %-16s\n", writePos++, curNode->brand, curNode->name, curNode->time, curNode->storeNum, curNode->price, curNode->info);
    }
    fclose(fpW);
}

pBeverageList addFromFile(char* file, pBeverageList list, pInteractInfo pInfo) {
    FILE*fp;
    char* pEnd;
    fp = fopen(file, "r");
    int line_len = 0;
    char ch[1000] = {0};

    char file0[]=BEVEPATH1;
    beveragePrintTime(file0);
    FILE* fpW = fopen(file0, "at+");
    fprintf(fpW, "\n");
    fprintf(fpW, "%-16s\t%-16s\t%-16s\t%-16s\t%-16s\t%-16s\t%-16s\n", "序号", "品牌", "酒水名", "进货时间", "存量", "价格", "信息");

    pBeverageNode head = list;

    if (fp == NULL) {
        printf("\n读取文件失败\n");
        return NULL;
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

        char brand[100] = {0}; char name[100] = {0}; char time[100] = {0};  int storeNum = 0; float price = 0; char info[100] = {0};

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
                    price = strtof(p, &pEnd);
                    break;
                case 5:
                    strcpy(info, p);
                    break;
            }

            i++;
        }

        fprintf(fpW, "%-16d\t%-16s\t%-16s\t%-16s\t%-16d\t%-16d\t%-16s\n", writePos, brand, name, time, storeNum, price, info);

        writePos++;

        pBeverageNode newNode = newBeverageNode(brand, name, time, storeNum, price, info, pInfo);

        if (newNode == NULL) return head;

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

    fclose(fpW);

    return head;
}
//***************************************linyebyd******************************************************
//*******************************************************************************************************
pClientLinkedList initClient(){
    pClientLinkedList head = (pClientLinkedList)malloc(sizeof(ClientLinkedList));
    head->next=NULL;
    FILE *fp=fopen(fileClientInfoLog,"at+");
    int line_len = 0;
    char ch[1000] = {0};
    pClientLinkedList NewClientAccount = (pClientLinkedList)malloc(sizeof(ClientLinkedList));
    head->next=NewClientAccount;

    NewClientAccount->next=NULL;
    strcpy(NewClientAccount->account,"administer0");
    strcpy(NewClientAccount->password,"administer0");
    strcpy(NewClientAccount->username,"administer0");
    NewClientAccount->saving=0;
    NewClientAccount->cost=0;
    NewClientAccount->grade=-1;

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

        char account[100] = {0}; char username[100] = {0};char password[100]={0};float cost=0;float saving=0;int grade=0;
        int i = 0;

        char *p = strtok(ch, " ");
        while(p){//使用第一个参数为NULL来提取子串
            switch(i) {
                case 0:
                    strcpy(account, p);
                    break;
                case 1:
                    strcpy(username, p);
                    break;
                case 2:
                    strcpy(password, p);
                    break;
                case 3:
                    cost=atof(p);
                    break;
                case 4:
                    saving=atof(p);
                    break;
                case 5:
                    grade=atoi(p);
                    break;
            }
            i++;
            p=strtok(NULL," ");
        }
        pClientLinkedList NewClientAccount = (pClientLinkedList)malloc(sizeof(ClientLinkedList));
        pClientLinkedList ptr=head;
        while(ptr->next!=NULL){
            ptr=ptr->next;
        }
        ptr->next=NewClientAccount;

        NewClientAccount->next=NULL;
        strcpy_s(NewClientAccount->account,strlen(account)+1,account);
        strcpy_s(NewClientAccount->password,strlen(password)+1,password);
        strcpy_s(NewClientAccount->username,strlen(username)+1,username);
        NewClientAccount->saving=saving;
        NewClientAccount->cost=cost;
        NewClientAccount->grade=grade;

    }

    return head;
}

int Check(char* ch){
    if(strspn(ch,"0123456789")==strlen(ch))
        return -1;
    int num=0;
    for(int i=0;i<strlen(ch);i++)
        if(ch[i]>='0'&&ch[i]<='9')
            num++;
    if (num==0) return -1;
    return 0;
}
int signUp(pClientLinkedList list, char *account, char* password, char* username,float saving,float cost,int grade){
    pClientLinkedList p0=clientSearch(list,account);
    if(p0!=NULL)
    {
        printf("用户名重名：（请重新输入\n");
        return -1;
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
    printCLientArchive(NewClientAccount);
    return 0;
}//重新复制一下 main.c中传参类型要变 我把花费和存款改成了float，头文件里面struct client那个把连个int也改成float。
clientNode clientSearch(pClientLinkedList list,char *account){
    pClientLinkedList p=list;
    while(p!=NULL&&strcmp(p->account,account)!=0){
        p=p->next;
    }
    return p;
}//

void printCLientArchive(clientNode p){
    FILE *fp;

    fp = fopen(fileClientInfoLog,"at+");
    fprintf(fp,"%15s%15s%15s%10.2f%10.2f%10d\n",p->account,p->username,p->password,p->cost,p->saving,p->grade);
    fclose(fp);
}

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
void reprintClient(pClientLinkedList list){
    FILE *fp;

    fp = fopen(fileClientInfoLog,"w");
    pClientLinkedList p=list;
    clientUpgradeCheck(list);
    while(p!=NULL)
    {
    fprintf(fp,"%15s%15s%15s%15.2f%15.2f%10d\n",p->account,p->username,p->password,p->cost,p->saving,p->grade);
    p=p->next;
    }

    fclose(fp);
}
void changeUsername(pClientLinkedList list,char* username,char*newUsername){
    pClientLinkedList p;
    p=clientSearch(list,username);
    strcpy_s(p->username,strlen(newUsername)+1,newUsername);
    printf("用户名已改为%s\n",p->username);
    reprintClient(list);
    //
}//

void NewPassword(pClientLinkedList list,char* account,char* newPassword){
    pClientLinkedList p;
    p=clientSearch(list,account);
    strcpy_s(p->password,strlen(newPassword)+1,newPassword);
    printf("已修改密码为：%s\n",p->password);
    reprintClient(list);
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

void deposit(clientNode client, float money){
    client->saving+=money;

}

void clientUpgradeCheck(pClientLinkedList list)
{
    pClientLinkedList p=list;
    while(p!=NULL)
    {
        p->costMonthly=0;
        if(p->grade!=-1)
        p->grade=1;
        p=p->next;
    }//清空

    //从文档中读入
    FILE *fp=fopen(fileClientBuyLog,"at+");
    char ch[200]={0};
    int line_len=0;
    time_t tmpcal_ptr;
    struct tm *tmp_ptr = NULL;
    time(&tmpcal_ptr);
    tmp_ptr = localtime(&tmpcal_ptr);
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

        char account[100] = {0}; int costMonthly=0;char time1[200]={0};
        pClientLinkedList ptr=NULL;
        int i = 0;

        char *str = strtok(ch, " ");
        while(str){//使用第一个参数为NULL来提取子串
            switch(i) {
                case 0:
                    strcpy(account, str);
                    ptr=clientSearch(list,account);
                    break;

                case 6:
                    costMonthly=atof(str);
                    break;
                case 7:
                    strcpy(time1,str);
                    break;
                default:
                    break;
            }
            i++;
            str=strtok(NULL," ");
        }
       int year=atoi(strtok(time1,"."));int month=atoi(strtok(NULL,"."));
       //gradeCheck;
       if((year==tmp_ptr->tm_year+1900)&&(month==tmp_ptr->tm_mon+1))
       {
           ptr->costMonthly-=costMonthly;
           if(costMonthly<0){
                while(ptr->costMonthly>pow(10,2*list->grade))
                {
                    list->grade++;
                }
           }else{
               while(ptr->costMonthly<pow(10,2*list->grade)&&(ptr->grade>1))
               {
                   list->grade--;
               }
           }
       }
    }

}

int buy(clientNode client, pBeverageList list, int number,pClientLinkedList list0){
    if(list->storeNum<number)
        return -1;
    clientUpgradeCheck(list0);
    list->storeNum-=number;
    list->sales+=number;
    clientUpgradeCheck(list0);
    client->cost+=number*list->price*(1-0.06*(client->grade-1));
    client->saving-=number*list->price*(1-0.06*(client->grade-1));
    recordClientBuy(client,list,number,-number*list->price*(1-0.06*(client->grade-1)),"卖出");
    clientUpgradeCheck(list0);
    return 0;
}
//传参不用变 直接把这段复制粘贴覆盖原来的函数

//这段也直接复制粘贴 覆盖掉

void recordClientBuy(clientNode client, pBeverageList list, int number,float cost,char* info){
    FILE *fp;
    fp = fopen(fileClientBuyLog,"at+");
    fprintf(fp,"%10s%10s%10s%10s%10.2f%10d%10.2f",client->account,client->username,list->brand,list->name,list->price,number,cost);
    fclose(fp);
    printTime(fileClientBuyLog);//输出一下时间
    fp = fopen(fileClientBuyLog,"at+");
    fprintf(fp,"%10s\n",info);
    fclose(fp);
}
//这段也复制粘贴覆盖掉（传参变多了 多了一个购买信息  但是是内部函数你不用改main.c）但是头文件声明那里得多加一个info参数

void recordClientAccount(clientNode client,const char behavior[]){
    FILE *fp;
    fp = fopen(fileClientAccountLog,"at+");
    fprintf(fp,"%10s%10s%10s",client->account,client->username,behavior);
    fclose(fp);
    printTime(fileClientAccountLog);//输出一下时间
    fp = fopen(fileClientAccountLog,"at+");
    fprintf(fp,"\n");
    fclose(fp);
}

void printTime(char* file){
    FILE *fp;
    fp = fopen(file,"at+");
    time_t tmpcal_ptr;
    struct tm *tmp_ptr = NULL;
    time(&tmpcal_ptr);
    tmp_ptr = localtime(&tmpcal_ptr);
    fprintf(fp,"     %d.%d.%d_%d:%d:%d", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday,tmp_ptr->tm_hour,tmp_ptr->tm_min,tmp_ptr->tm_sec);//五个空格
    fclose(fp);
}

int infoCheck(clientNode p,char *info){
    if(p->grade<0){
        return 0;
    }else{
        if(strstr(info,p->account)==NULL){
            return 1;
        }else
            return 0;
    }
}//这个是新功能， 辅助粘贴 头文件也加上 检验普通用户输入的账单搜索关键字 使其不能查看所有用户的帐单 除非是管理员 return 0关键词没问题 return 1 关键词不够准确；
int searchClientBuy(char *info)
{

    FILE *fp;
    int line_len=0;
    char buf[1024]={0};
    char Info[20];
    strcpy_s(Info,strlen(info)+1,info);
    fp=fopen(fileClientBuyLog,"r");
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
//改过了 复制粘贴 传参不变
void printClientInfo(clientNode p)
{
    char account[]="账号";
    char username[]="用户名";
    char cost[]="历史消费金额";
    char saving[]="账户储蓄金";
    char grade[]="用户等级";
    char costMonthly[]="本月已花销";
    char grade0[]="管理员";
    clientUpgradeCheck(p);//这里有点bug但是bug不多。
    printf("*****************************\n");
    printf("%15s%15s\n",account,p->account);
    printf("%15s%15s\n",username,p->username);
    printf("%15s%15.2f\n",cost,p->cost);
    printf("%15s%15.2f\n",saving,p->saving);
    if(p->grade>=0){
        printf("%15s%15d(%s:%.2f,离下一等级还需花费%.2f元)\n",grade,p->grade,costMonthly,p->costMonthly,pow(10,2*(p->grade))-p->costMonthly);
    }else{
        printf("%15s%15s\n",grade,grade0);
    }
    printf("*****************************\n");
}

pclientRequestList clientRequestListInit(){
    pclientRequestList head = (pclientRequestList)malloc(sizeof(clientRequestList));
    head->next=NULL;
    return head;
}

void searchClientBuy_FORREQUEST(char *info,char requestInfo[])
{

    FILE *fp;

    int line_len=0;
    char buf[1024]={0};
    char Info[20];
    strcpy_s(Info,strlen(info)+1,info);
    fp=fopen(fileClientBuyLog,"r");
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

void clientRequest_PUSH(pclientRequestList list,clientNode client,pBeverageList listb,char *info,char* excuse){
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
    strcpy_s(NewClientRequest->info,strlen(excuse)+1,excuse);
    NewClientRequest->pb=pb0;
    NewClientRequest->pc=client;
    NewClientRequest->number=number;
    NewClientRequest->cost=cost;
}


void clientRequest_POP(pclientRequestList list,int choice,int operate, pInteractInfo pInfo){
        int i=1;
        pclientRequestList p0=list;
        pclientRequestList p=list->next;
        while(p!=NULL&&i<choice){
            i++;
            p0=p0->next;
            p=p->next;
         }
        if(operate==1){
            while(p->pc->cost+p->cost<pow(10,2*p->pc->grade)&&p->pc->grade>1)
            {
                p->pc->grade--;
            }
            p->pc->saving-=p->cost;
            p->pc->cost+=p->cost;
            p->pb->storeNum+=p->number;
            p->pb->sales-=p->number;
            // pInfo->sellerSaving -= p->cost;
            printf("您已成功同意一条退货申请，还剩下这些请求待处理：\n");
            recordClientBuy(p->pc,p->pb,p->number,-p->cost,"退货成功");
        }else{
            printf("您已成功拒绝一条退货申请，还剩下这些请求待处理：\n");
            recordClientBuy(p->pc,p->pb,p->number,0,"拒绝退货");
        }
        p0->next=p->next;
        clientRequest_SHOW(list);
}

int clientRequest_SHOW(pclientRequestList list){
    pclientRequestList p=list->next;
    int i=0;
    char *request="退货";
    printf("***********************************************************************************\n");
    printf("%10s%10s%10s%10s%10s%15s\n","账号","品牌","名称","请求","数量","时间");
    printf("-----------------------------------------------------------------------------------\n");
    while(p!=NULL){
        printf("%10s%10s%10s%10s%10d%25s\n",p->pc->account,p->pb->brand,p->pb->name,request,p->number,p->time);
        p=p->next;
        i++;
    }
    printf("***********************************************************************************\n");
    return i;
}

void clientRequest_SHOWMORE(pclientRequestList list,int choice){
    int i=1;
    pclientRequestList p0=list;
    pclientRequestList p=list->next;
    while(p!=NULL&&i<choice){
        i++;
        p0=p0->next;
        p=p->next;
     }
    printf("*************************************************退货原因说明****************************************************\n");
    printf("%s\n",p->info);
    printf("*************************************************退货原因说明****************************************************\n");
}
//**************************************************************************************************************************
int  searchClientCost(pClientLinkedList list,float max,float min){
    int i=0;
    pClientLinkedList p=list->next;
    rankClientCost(list,1);
    while(p!=NULL)
    {
        if(p->cost>=min&&p->cost<=max&&p->grade>0){
            if(i==0){
                printf("%15s%15s%15s%20s%20s%10s%20s\n","账号","用户名","密码","历史总花费","存款","等级","本月花费");
            }
            printf("%15s%15s%15s%20.2f%20.2f%10d%20.2f\n",p->account,p->username,p->password,p->cost,p->saving,p->grade,p->costMonthly);
            i++;
        }

        p=p->next;
    }
    return i;
}
int  searchClientCostMOnthly(pClientLinkedList list,float max,float min){
    int i=0;
    pClientLinkedList p=list->next;
    rankClientCostMonthly(list,1);
    while(p!=NULL)
    {
        if(p->costMonthly>=min&&p->costMonthly<=max&&p->grade>0){
            if(i==0){
                printf("%15s%15s%15s%20s%20s%10s%20s\n","账号","用户名","密码","历史总花费","存款","等级","本月花费");
            }
            printf("%15s%15s%15s%20.2f%20.2f%10d%20.2f\n",p->account,p->username,p->password,p->cost,p->saving,p->grade,p->costMonthly);
            i++;
        }

        p=p->next;
    }
    return i;
}
int  searchClientGrade(pClientLinkedList list,int max,int min){
    int i=0;
    pClientLinkedList p=list->next;
    rankClientCostMonthly(list,1);
    while(p!=NULL)
    {
        if(p->grade>min&&p->grade<max&&p->grade>0){
            if(i==0){
                printf("%15s%15s%15s%20s%20s%10s%20s\n","账号","用户名","密码","历史总花费","存款","等级","本月花费");
            }
            printf("%15s%15s%15s%20.2f%20.2f%10d%20.2f\n",p->account,p->username,p->password,p->cost,p->saving,p->grade,p->costMonthly);
            i++;
        }

        p=p->next;
    }
    return i;
}
int  searchClientName(pClientLinkedList list,char* name){
    int i=0;
    pClientLinkedList p=list->next;
    rankClientCostMonthly(list,1);
    while(p!=NULL)
    {
        if(strstr(p->username,name)!=NULL&&p->grade>0){
            if(i==0){
                printf("%15s%15s%15s%20s%20s%10s%20s\n","账号","用户名","密码","历史总花费","存款","等级","本月花费");
            }
            printf("%15s%15s%15s%20.2f%20.2f%10d%20.2f\n",p->account,p->username,p->password,p->cost,p->saving,p->grade,p->costMonthly);
            i++;
        }

        p=p->next;
    }
    return i;
}
int  searchClientAccount(pClientLinkedList list,char* account){
    int i=0;
    pClientLinkedList p=list->next;
    rankClientCostMonthly(list,1);
    while(p!=NULL)
    {
        if(strstr(p->account,account)!=NULL&&p->grade>0){
            if(i==0){
                printf("%15s%15s%15s%20s%20s%10s%20s\n","账号","用户名","密码","历史总花费","存款","等级","本月花费");
            }
            printf("%15s%15s%15s%20.2f%20.2f%10d%20.2f\n",p->account,p->username,p->password,p->cost,p->saving,p->grade,p->costMonthly);
            i++;
        }

        p=p->next;
    }
    return i;
}
//*****************************************************排序****************************************************
int rankClientCost(pClientLinkedList list,int k){
   pClientLinkedList p0=list->next;
   if(p0->next==NULL) return -1;
   pClientLinkedList p=p0->next;
   if(p->next==NULL) return 1;
   //一些特判。
   clientUpgradeCheck(list);
   while(p->next!=NULL){
            pClientLinkedList ptr=p;
            while(ptr!=NULL){
                if(k*ptr->cost>k*p->cost){
                    char account[200]={0};char username[200]={0};char password[200]={0};
                    int grade=0;float cost=0;float costMonthly=0;float saving=0;
                    strcpy(account,ptr->account);
                    strcpy(username,ptr->username);
                    strcpy(password,ptr->password);
                    grade=ptr->grade;
                    cost=ptr->cost;
                    costMonthly=ptr->costMonthly;
                    saving=ptr->saving;
                    strcpy(ptr->account,p->account);
                    strcpy(ptr->username,p->username);
                    strcpy(ptr->password,p->password);
                    ptr->cost=p->cost;
                    ptr->costMonthly=p->costMonthly;
                    ptr->grade=p->grade;
                    ptr->saving=p->saving;
                    strcpy(p->account,account);
                    strcpy(p->username,username);
                    strcpy(p->password,password);
                    p->cost=cost;
                    p->grade=grade;
                    p->saving=saving;
                    p->costMonthly=costMonthly;
                }
                ptr=ptr->next;
            }
            p=p->next;
   }
   return 1;
}

int rankClientCostMonthly(pClientLinkedList list,int k){
   pClientLinkedList p0=list->next;
   if(p0->next==NULL) return -1;
   pClientLinkedList p=p0->next;
   if(p->next==NULL) return 1;
   //一些特判。
   clientUpgradeCheck(list);
   while(p->next!=NULL){
            pClientLinkedList ptr=p;
            while(ptr!=NULL){
                if(k*ptr->costMonthly>k*p->costMonthly){
                    char account[200]={0};char username[200]={0};char password[200]={0};
                    int grade=0;float cost=0;float costMonthly=0;float saving=0;
                    strcpy(account,ptr->account);
                    strcpy(username,ptr->username);
                    strcpy(password,ptr->password);
                    grade=ptr->grade;
                    cost=ptr->cost;
                    costMonthly=ptr->costMonthly;
                    saving=ptr->saving;
                    strcpy(ptr->account,p->account);
                    strcpy(ptr->username,p->username);
                    strcpy(ptr->password,p->password);
                    ptr->cost=p->cost;
                    ptr->costMonthly=p->costMonthly;
                    ptr->grade=p->grade;
                    ptr->saving=p->saving;
                    strcpy(p->account,account);
                    strcpy(p->username,username);
                    strcpy(p->password,password);
                    p->cost=cost;
                    p->grade=grade;
                    p->saving=saving;
                    p->costMonthly=costMonthly;
                }
                ptr=ptr->next;
            }
            p=p->next;
   }
   return 1;
}
int rankClientUsername(pClientLinkedList list,int k){
    pClientLinkedList p0=list->next;
    if(p0->next==NULL) return -1;
    pClientLinkedList p=p0->next;
    if(p->next==NULL) return 1;
    //一些特判。
    clientUpgradeCheck(list);
    while(p->next!=NULL){
             pClientLinkedList ptr=p;
             while(ptr!=NULL){
                 if(k*strcmp(p->username,ptr->username)>0){
                     char account[200]={0};char username[200]={0};char password[200]={0};
                     int grade=0;float cost=0;float costMonthly=0;float saving=0;
                     strcpy(account,ptr->account);
                     strcpy(username,ptr->username);
                     strcpy(password,ptr->password);
                     grade=ptr->grade;
                     cost=ptr->cost;
                     costMonthly=ptr->costMonthly;
                     saving=ptr->saving;
                     strcpy(ptr->account,p->account);
                     strcpy(ptr->username,p->username);
                     strcpy(ptr->password,p->password);
                     ptr->cost=p->cost;
                     ptr->costMonthly=p->costMonthly;
                     ptr->grade=p->grade;
                     ptr->saving=p->saving;
                     strcpy(p->account,account);
                     strcpy(p->username,username);
                     strcpy(p->password,password);
                     p->cost=cost;
                     p->grade=grade;
                     p->saving=saving;
                     p->costMonthly=costMonthly;
                 }
                 ptr=ptr->next;
             }
             p=p->next;
    }
    return 1;
}
int rankClientAccount(pClientLinkedList list,int k){
    pClientLinkedList p0=list->next;
    if(p0->next==NULL) return -1;
    pClientLinkedList p=p0->next;
    if(p->next==NULL) return 1;
    //一些特判。
    clientUpgradeCheck(list);
    while(p->next!=NULL){
             pClientLinkedList ptr=p;
             while(ptr!=NULL){
                 if(k*strcmp(p->account,ptr->account)>0){
                     char account[200]={0};char username[200]={0};char password[200]={0};
                     int grade=0;float cost=0;float costMonthly=0;float saving=0;
                     strcpy(account,ptr->account);
                     strcpy(username,ptr->username);
                     strcpy(password,ptr->password);
                     grade=ptr->grade;
                     cost=ptr->cost;
                     costMonthly=ptr->costMonthly;
                     saving=ptr->saving;
                     strcpy(ptr->account,p->account);
                     strcpy(ptr->username,p->username);
                     strcpy(ptr->password,p->password);
                     ptr->cost=p->cost;
                     ptr->costMonthly=p->costMonthly;
                     ptr->grade=p->grade;
                     ptr->saving=p->saving;
                     strcpy(p->account,account);
                     strcpy(p->username,username);
                     strcpy(p->password,password);
                     p->cost=cost;
                     p->grade=grade;
                     p->saving=saving;
                     p->costMonthly=costMonthly;
                 }
                 ptr=ptr->next;
             }
             p=p->next;
    }
    return 1;
}

void showClientAll(pClientLinkedList list){
    pClientLinkedList p=list->next;
    printf("%15s%15s%15s%20s%20s%10s%20s\n","账号","用户名","密码","历史总花费","存款","等级","本月花费");
    while(p!=NULL){
        if(p->grade!=-1){
            printf("%15s%15s%15s%20.2f%20.2f%10d%20.2f\n",p->account,p->username,p->password,p->cost,p->saving,p->grade,p->costMonthly);
        }
        p=p->next;
    }
}
void showClientTop(pClientLinkedList list){
    pClientLinkedList p=list->next;
    printf("%15s%15s%15s%20s%20s%10s%20s\n","账号","用户名","密码","历史总花费","存款","等级","本月花费");
    int i=0;
    while(p!=NULL&&i<=5){
        if(p->grade!=-1){
            printf("%15s%15s%15s%20.2f%20.2f%10d%20.2f\n",p->account,p->username,p->password,p->cost,p->saving,p->grade,p->costMonthly);
            i++;
        }
        p=p->next;
    }
    if(i<3){
        printf("人数不足，仅有%d条",i);
    }
}
//**************************************************************************************************************************
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

pClientshoppingcar initshoppingcar()
{   pClientshoppingcar head = (pClientshoppingcar)malloc(sizeof(Clientshoppingcar));
    head->next=NULL;
    return head;
}


shopNode shoppingcarSearch(pClientshoppingcar list,char *name){
    pClientshoppingcar p=list;
    while(p!=NULL&&strcmp(p->name,name)!=0){
        p=p->next;
    }
    return p;
}

void addshoppingcar(pClientshoppingcar Testlist,pClientLinkedList list,pBeverageList testList,int amount){
    pClientshoppingcar NewClientshoppingcar = (pClientshoppingcar)malloc(sizeof(Clientshoppingcar));
    pClientshoppingcar p=Testlist;
    while(p->next!=NULL){
        p=p->next;
    }
    p->next=NewClientshoppingcar;

    NewClientshoppingcar->next=NULL;
    strcpy_s(NewClientshoppingcar->account,strlen(list->account)+1,list->account);
    strcpy_s(NewClientshoppingcar->username,strlen(list->username)+1,list->username);
    strcpy_s(NewClientshoppingcar->name,strlen(testList->name)+1,testList->name);
    strcpy_s(NewClientshoppingcar->brand,strlen(testList->brand)+1,testList->brand);
    strcpy_s(NewClientshoppingcar->info,strlen(testList->info)+1,testList->info);
    NewClientshoppingcar->price=testList->price;
    NewClientshoppingcar->amount=amount;
    NewClientshoppingcar->cost=testList->price*amount;

}
void changeshoppingcar(pClientshoppingcar Testlist,char* name,int amount){
    pClientshoppingcar p;
    p=shoppingcarSearch(Testlist,name);
    p->amount=amount;
    p->cost=p->price*amount;
}

pClientshoppingcar deleteshoppingcar(pClientshoppingcar list,char* name,int *status){
    pClientshoppingcar p=list;
    pClientshoppingcar p0=p;
    p=p->next;
    while(p!=NULL&&strcmp(p->name,name)!=0){
        p0=p;
        p=p->next;
    }
    if(p!=NULL){
        if(p->next!=NULL){
            p0->next=p->next;
            *status=0;
        }else{
            p0->next=NULL;
            *status=0;
        }
    }else
    {
        printf("");
        *status=-1;
    }
    return list;
}

void showshoppingcar(pClientshoppingcar list,char* username){
    pClientshoppingcar p;
    p=list;
    int i=1;

        printf("\n当前购物车如下:\n");
        printf("%-12s%-12s%-12s%-12s%-12s%-12s%-12s%-12s%-12s\n", "序号", "账号", "用户名", "品牌", "名称", "单价", "数量","总价","信息");
        while (p != NULL) {
            if (strcmp(p->username,username)==0) {
                printf("%-12d%-12s%-12s%-12s%-12s%-12d%-12d%-12d%-12s\n", i, p->account, p->username, p->brand, p->name, p->price, p->amount,p->cost,p->info);
                i++;
            }

            p = p->next;
        }

}

pClientshoppingcar finding(pClientshoppingcar head, int i){
    int j = 1;
    pClientshoppingcar p=head;
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
void searchshoppingcar(pClientshoppingcar list, char* name){
     printf("\n开始检索名称\n");
     pClientshoppingcar p=list->next;
     int i=1;
     int sum=0;
     while (p != NULL) {
         if (strstr(p->name, name)) {
             printf("%-12d%-12s%-12s%-12s%-12s%-12s%-12d%-12d%-12d\n", i, p->account, p->username, p->brand, p->name, p->info, p->price,p->amount,p->cost);
             sum++;
         }
         i++;
         p = p->next;
     }
     printf("为您搜索'%s'关键字，共搜索到%d条记录\n", name, sum);
     return;
}
void searchshoppingcar2(pClientshoppingcar list, char* name){
     printf("\n开始检索名称\n");
     pClientshoppingcar p=list->next;
     int i=1;
     int sum=0;
     while (p != NULL) {
         if (strstr(p->brand, name)) {
             printf("%-12d%-12s%-12s%-12s%-12s%-12s%-12d%-12d%-12d\n", i, p->account, p->username, p->brand, p->name, p->info, p->price,p->amount,p->cost);
             sum++;
         }
         i++;
         p = p->next;
     }
     printf("为您搜索'%s'关键字，共搜索到%d条记录\n", name, sum);
     return;
}
pBeverageNode findname(pBeverageList list, char* name){

    pBeverageNode p = list;
   while(strcmp(p->name, name)!=0)
   {p=p->next;
   }
    return p;
}
int blank(char judge[]){
    char ch;
    char true_[20];
    int i,j;
    for(i=0,j=0;i<strlen(judge);i++){
        if(judge[i]==' ')
         continue;
        else{
        true_[j]=judge[i];
        j++;
       }
    }
    true_[j]='\0';
    return strlen(true_);
}

pInteractInfo initInteractInfo(float saving) {
    pInteractInfo ret = (pInteractInfo)malloc(sizeof(InteractInfo));
    ret->sellerSaving = saving;
    return ret;
}

int reduceSaving(pInteractInfo pInfo, float price) {
    if (pInfo->sellerSaving >= price) {
        pInfo->sellerSaving -= price;
        return 1;
    }
    else printf("商户存款不足！\n");
    return 0;
}

void showInfoSaving(pInteractInfo pInfo) {
    printf("当前资金是：%.2f\n", pInfo->sellerSaving);
}

int getNum(pClientshoppingcar head){
    int cnt = 0;
    pClientshoppingcar p = head;
    while(p != NULL){
    cnt++;
    p = p->next;
}
    return cnt;
}
int check_date(int year, int month, int day)
{
        int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if ( year < 0 )
        {
                printf("输入的年份[%d]错误\n", year);
                return -1;
        }

        if ( month < 1 || month > 12 )
        {
                printf("输入的月份[%d]错误\n", month);
                return -1;
        }

        if ( month == 2 )
        {
                // 判断如果是闰年,则修改二月的monthDays[1]值为29
                if ( (year % 400 == 0) || \
                     (year % 100 != 0 && year % 4 == 0)
                   )
                {
                        monthDays[1] = 29;
                }
        }

        if ( day < 1 || day > monthDays[month-1] )
        {
                printf("输入的日子[%d]错误\n", day);
                return -1;
        }

        return 0;
}

int is_valid_date(const char *startDate)
{
        int start_year = 0;
        int start_month = 0;
        int start_day = 0;

        if ( strlen(startDate) > 0 )
        {
                int count = 0;
                count = sscanf(startDate, "%4d-%2d-%2d", &start_year, &start_month, &start_day);
                if ( count != 3 )
                {
                        printf("输入格式错误\n");
                        return -1;
                }

                if ( 0 != check_date(start_year, start_month, start_day) )
                {
                        return -1;
                }

                printf("输入成功\n");
        }

        return 0;
}
