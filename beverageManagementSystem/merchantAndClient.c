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
        printf("\n������Ҫ������\n");
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
        printf("�Ҳ�����%d�����ݣ��޷���������\n", i);
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
        printf("\n��ȡ�ļ�ʧ��\n");
        exit(0);
    } else {
        printf("\n��ȡ�ļ��ɹ�\n");
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
        // ��ch���зָ�

        char brand[100] = {0}; char name[100] = {0}; char time[100] = {0};  int storeNum = 0; int price = 0; char info[100] = {0};

        int i = 0;

        char *p = strtok(ch, " ");
        while(p=strtok(NULL, " ")){//ʹ�õ�һ������ΪNULL����ȡ�Ӵ�
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
    if (!p) //���headָ��Ϊ��˵������Ϊ��
    {
        printf("\n���Ϊ��\n");
    }
    else
    {
        printf("\n��ǰ�������:\n");
        printf("\tƷ��\t��ˮ��\t����ʱ��\t����\t�۸�\t��Ϣ\n");
        while (p)  //ѭ���������ڵ�ֵ���
        {
            p = p->next;//��һ������ֵ   ����
            if(p) printf("%d:\t%s\t%s\t%s\t%d\t%d\t%s\n", i, p->brand, p->name, p->time, p->storeNum, p->price, p->info);
            i++;
        }
    }
}

pBeverageList sortBeverageTime(pBeverageList list, int key) {
    // �½�һ������������������
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
            // �����ʱ��������������ֻ��pһ����㣬��ֱ�Ӱ�p����
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
                // �ҵ�����㣬��maxNodeָ������prevMaxNodeָ������ǰһ�����
            }
            // ���벽��
            // ���prevMaxNode == NULL��˵����������p��㣬��ʱֱ�ӽ�p��������������pָ����һ�����
            if (prevMaxNode == NULL) {
                pBeverageNode nextP = p->next;
                p->next = NULL;
                insertPos->next = p;
                p = nextP;
            } else {
                // ���prevMaxNode != NULL����maxNode�����������ý�p����
                prevMaxNode->next = maxNode->next;
                maxNode->next = NULL;
                insertPos->next = maxNode;
            }
            // ��p��insertPos����һλ
            insertPos = insertPos->next;
        }
    }
    char* outStr = {0};
    if (key > 0) {
        outStr = "����";
    } else {
        outStr = "����";
    }
    printf("\n���ݽ���ʱ��ؼ��ʶԾ�ˮ������%s����\n", outStr);
    return retList;
}

pBeverageList sortBeverageBrand(pBeverageList list, int key) {
    // �½�һ������������������
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
            // �����ʱ��������������ֻ��pһ����㣬��ֱ�Ӱ�p����
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
                // �ҵ�����㣬��maxNodeָ������prevMaxNodeָ������ǰһ�����
            }
            // ���벽��
            // ���prevMaxNode == NULL��˵����������p��㣬��ʱֱ�ӽ�p��������������pָ����һ�����
            if (prevMaxNode == NULL) {
                pBeverageNode nextP = p->next;
                p->next = NULL;
                insertPos->next = p;
                p = nextP;
            } else {
                // ���prevMaxNode != NULL����maxNode�����������ý�p����
                prevMaxNode->next = maxNode->next;
                maxNode->next = NULL;
                insertPos->next = maxNode;
            }
            // ��p��insertPos����һλ
            insertPos = insertPos->next;
        }
    }
    char* outStr = {0};
    if (key > 0) {
        outStr = "����";
    } else {
        outStr = "����";
    }
    printf("\n����Ʒ�ƹؼ��ʶԾ�ˮ������%s����\n", outStr);
    return retList;
}

pBeverageList sortBeverageStoreNum(pBeverageList list, int key) {
    // �½�һ������������������
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
            // �����ʱ��������������ֻ��pһ����㣬��ֱ�Ӱ�p����
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
                // �ҵ�����㣬��maxNodeָ������prevMaxNodeָ������ǰһ�����
            }
            // ���벽��
            // ���prevMaxNode == NULL��˵����������p��㣬��ʱֱ�ӽ�p��������������pָ����һ�����
            if (prevMaxNode == NULL) {
                pBeverageNode nextP = p->next;
                p->next = NULL;
                insertPos->next = p;
                p = nextP;
            } else {
                // ���prevMaxNode != NULL����maxNode�����������ý�p����
                prevMaxNode->next = maxNode->next;
                maxNode->next = NULL;
                insertPos->next = maxNode;
            }
            // ��p��insertPos����һλ
            insertPos = insertPos->next;
        }
    }
    char* outStr = {0};
    if (key > 0) {
        outStr = "����";
    } else {
        outStr = "����";
    }
    printf("\n���ݴ����ؼ��ʶԾ�ˮ������%s����\n", outStr);
    return retList;
}

pBeverageList sortBeveragePrice(pBeverageList list, int key) {
    // �½�һ������������������
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
            // �����ʱ��������������ֻ��pһ����㣬��ֱ�Ӱ�p����
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
                // �ҵ�����㣬��maxNodeָ������prevMaxNodeָ������ǰһ�����
            }
            // ���벽��
            // ���prevMaxNode == NULL��˵����������p��㣬��ʱֱ�ӽ�p��������������pָ����һ�����
            if (prevMaxNode == NULL) {
                pBeverageNode nextP = p->next;
                p->next = NULL;
                insertPos->next = p;
                p = nextP;
            } else {
                // ���prevMaxNode != NULL����maxNode�����������ý�p����
                prevMaxNode->next = maxNode->next;
                maxNode->next = NULL;
                insertPos->next = maxNode;
            }
            // ��p��insertPos����һλ
            insertPos = insertPos->next;
        }
    }
    char* outStr = {0};
    if (key > 0) {
        outStr = "����";
    } else {
        outStr = "����";
    }
    printf("\n���ݼ۸�ؼ��ʶԾ�ˮ������%s����\n", outStr);
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
    // ɾ��tarNode���
    prevTarNode->next = tarNode->next;
    free(tarNode);
    printf("\nɾ���˱��Ϊ%d�ľ�ˮ\n", i);
}

void searchBeverageInfo(pBeverageList list, char* givenInfo) {
    printf("\n��ʼ������ˮ��Ϣ\n");
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
    printf("Ϊ������'%s'�ؼ��֣���������%d����¼\n", givenInfo, sum);
    return;
}

void searchBeverageBrand(pBeverageList list, char* givenBrand) {
    printf("\n��ʼ����Ʒ��\n");
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
    printf("Ϊ������'%s'�ؼ��֣���������%d����¼\n", givenBrand, sum);
    return;
}

void searchBeverageName(pBeverageList list, char* givenName) {
    printf("\n��ʼ��������\n");
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
    printf("Ϊ������'%s'�ؼ��֣���������%d����¼\n", givenName, sum);
    return;
}

void changeBeverageInfo(pBeverageList list, int number, char* givenInfo) {
    pBeverageNode node = find(list, number + 1);
    strcpy(node->info, givenInfo);
    printf("\n�޸��˱��Ϊ%d�ľ�ˮ����Ϣ\n", number);
}

void reduceBeverageStoreNum(pBeverageList list, int number, int reduceNum) {
    pBeverageNode node = find(list, number + 1);
    if (node->storeNum < reduceNum) {
        printf("\n��ˮ��治�㣡\n");
        return;
    } else {
        node->storeNum -= reduceNum;
    }
}
