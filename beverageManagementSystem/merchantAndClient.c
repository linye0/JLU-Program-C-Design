#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        printf("\t品牌\t酒水名\t进货时间\t存量\t价格\t信息\n");
        while (p)  //循环将各个节点值输出
        {
            p = p->next;//第一是垃圾值   跳过
            if(p) printf("%d:\t%s\t%s\t%s\t%d\t%d\t%s\n", i, p->brand, p->name, p->time, p->storeNum, p->price, p->info);
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
