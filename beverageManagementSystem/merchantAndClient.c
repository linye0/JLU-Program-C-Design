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
