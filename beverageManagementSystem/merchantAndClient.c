#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "merchantAndClient.h"
#define fileClientBuyLog "D:\\C-Project\\JLU-Program-C-Design\\data\\buy.txt"
#define fileClientAccountLog "D:\\C-Project\\JLU-Program-C-Design\\data\\client.txt"
#define fileClientInfoLog "D:\\C-Project\\JLU-Program-C-Design\\data\\clientInfo.txt"
#define BEVEPATH1 "D:\\C-Project\\JLU-Program-C-Design\\data\\������¼.txt"
#define BEVEPATH2 "D:\C-Project\JLU-Program-C-Design\data\\д����.txt"
#define autoSaveStore "D:\C-Project\JLU-Program-C-Design\data\\autoSave.txt"
void beveragePrintTime(char* file){
    FILE *fp;
    fp = fopen(file,"at+");
    time_t tmpcal_ptr;
    struct tm *tmp_ptr = NULL;
    time(&tmpcal_ptr);
    tmp_ptr = localtime(&tmpcal_ptr);
    fprintf(fp,"%d.%d.%d", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday);//����ո�
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
}//�������ͷ��

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
    fprintf(fpW, "%-16s\t%-16s\t%-16s\t%-16s\t%-16s\t%-16s\t%-16s\n", "���", "Ʒ��", "��ˮ��", "����ʱ��", "����", "�۸�", "��Ϣ");

    if (fp == NULL) {
        printf("\n��ȡ�ļ�ʧ��\n");
        return NULL;
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
    if (!p) //���headָ��Ϊ��˵������Ϊ��
    {
        printf("\n���Ϊ��\n");
    }
    else
    {
        printf("\n��ǰ�������:\n");
        printf("%-16s\t%-16s\t%-16s\t%-16s\t%-16s\t%-16s\t%-16s\n", "���", "Ʒ��", "��ˮ��", "����ʱ��", "����", "�۸�", "��Ϣ");
        while (p)  //ѭ���������ڵ�ֵ���
        {
            p = p->next;//��һ������ֵ   ����
            if(p) printf("%-16d\t%-16s\t%-16s\t%-16s\t%-16d\t%-16.2f\t%-16s\t\n", i, p->brand, p->name, p->time, p->storeNum, p->price, p->info);
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
        prevTarNode=tarNode;
        tarNode=tarNode->next;
        i++;
    }
    // ɾ��tarNode���
    if(prevTarNode==NULL){
        return;
    }
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
    fprintf(fpW, "%-16s\t%-16s\t%-16s\t%-16s\t%-16s\t%-16s\t%-16s\n", "���", "Ʒ��", "��ˮ��", "����ʱ��", "����", "�۸�", "��Ϣ");

    pBeverageNode head = list;

    if (fp == NULL) {
        printf("\n��ȡ�ļ�ʧ��\n");
        return NULL;
    } else {
        printf("\n��ȡ�ļ��ɹ�\n");
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
        // ��ch���зָ�

        char brand[100] = {0}; char name[100] = {0}; char time[100] = {0};  int storeNum = 0; float price = 0; char info[100] = {0};

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

        // �жϲ�Ʒ�Ƿ����ڿ���д���

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
        // ��ch���зָ�

        char account[100] = {0}; char username[100] = {0};char password[100]={0};float cost=0;float saving=0;int grade=0;
        int i = 0;

        char *p = strtok(ch, " ");
        while(p){//ʹ�õ�һ������ΪNULL����ȡ�Ӵ�
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
        printf("�û���������������������\n");
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

    recordClientAccount(NewClientAccount,"ע��");
    printCLientArchive(NewClientAccount);
    return 0;
}//���¸���һ�� main.c�д�������Ҫ�� �Ұѻ��Ѻʹ��ĳ���float��ͷ�ļ�����struct client�Ǹ�������intҲ�ĳ�float��
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
                recordClientAccount(p,"��ͨ��¼");
                *status=1;
            }else
            {
                recordClientAccount(p,"�����¼");
                *status=4;
            }
        }else{

            recordClientAccount(p,"��¼ʧ��");
            printf("������� ��������ȷ������\n");
            *status=0;
        }
    }else{
        printf("��Ǹ δ���ҵ�������˺�\n");
        printf("���Ƿ���Ҫ ע��\n");
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
    printf("�û����Ѹ�Ϊ%s\n",p->username);
    reprintClient(list);
    //
}//

void NewPassword(pClientLinkedList list,char* account,char* newPassword){
    pClientLinkedList p;
    p=clientSearch(list,account);
    strcpy_s(p->password,strlen(newPassword)+1,newPassword);
    printf("���޸�����Ϊ��%s\n",p->password);
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
    }//���

    //���ĵ��ж���
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
        // ��ch���зָ�

        char account[100] = {0}; int costMonthly=0;char time1[200]={0};
        pClientLinkedList ptr=NULL;
        int i = 0;

        char *str = strtok(ch, " ");
        while(str){//ʹ�õ�һ������ΪNULL����ȡ�Ӵ�
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
    recordClientBuy(client,list,number,-number*list->price*(1-0.06*(client->grade-1)),"����");
    clientUpgradeCheck(list0);
    return 0;
}
//���β��ñ� ֱ�Ӱ���θ���ճ������ԭ���ĺ���

//���Ҳֱ�Ӹ���ճ�� ���ǵ�

void recordClientBuy(clientNode client, pBeverageList list, int number,float cost,char* info){
    FILE *fp;
    fp = fopen(fileClientBuyLog,"at+");
    fprintf(fp,"%10s%10s%10s%10s%10.2f%10d%10.2f",client->account,client->username,list->brand,list->name,list->price,number,cost);
    fclose(fp);
    printTime(fileClientBuyLog);//���һ��ʱ��
    fp = fopen(fileClientBuyLog,"at+");
    fprintf(fp,"%10s\n",info);
    fclose(fp);
}
//���Ҳ����ճ�����ǵ������α���� ����һ��������Ϣ  �������ڲ������㲻�ø�main.c������ͷ�ļ���������ö��һ��info����

void recordClientAccount(clientNode client,const char behavior[]){
    FILE *fp;
    fp = fopen(fileClientAccountLog,"at+");
    fprintf(fp,"%10s%10s%10s",client->account,client->username,behavior);
    fclose(fp);
    printTime(fileClientAccountLog);//���һ��ʱ��
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
    fprintf(fp,"     %d.%d.%d_%d:%d:%d", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday,tmp_ptr->tm_hour,tmp_ptr->tm_min,tmp_ptr->tm_sec);//����ո�
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
}//������¹��ܣ� ����ճ�� ͷ�ļ�Ҳ���� ������ͨ�û�������˵������ؼ��� ʹ�䲻�ܲ鿴�����û����ʵ� �����ǹ���Ա return 0�ؼ���û���� return 1 �ؼ��ʲ���׼ȷ��
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
//�Ĺ��� ����ճ�� ���β���
void printClientInfo(clientNode p)
{
    char account[]="�˺�";
    char username[]="�û���";
    char cost[]="��ʷ���ѽ��";
    char saving[]="�˻������";
    char grade[]="�û��ȼ�";
    char costMonthly[]="�����ѻ���";
    char grade0[]="����Ա";
    clientUpgradeCheck(p);//�����е�bug����bug���ࡣ
    printf("*****************************\n");
    printf("%15s%15s\n",account,p->account);
    printf("%15s%15s\n",username,p->username);
    printf("%15s%15.2f\n",cost,p->cost);
    printf("%15s%15.2f\n",saving,p->saving);
    if(p->grade>=0){
        printf("%15s%15d(%s:%.2f,����һ�ȼ����軨��%.2fԪ)\n",grade,p->grade,costMonthly,p->costMonthly,pow(10,2*(p->grade))-p->costMonthly);
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
                //����
                continue;
            }
        }
        if('\r'==buf[line_len-1]){
            buf[line_len-1]='\0';
            line_len--;
            if(0==line_len){
                //����
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
            printf("���ѳɹ�ͬ��һ���˻����룬��ʣ����Щ���������\n");
            recordClientBuy(p->pc,p->pb,p->number,-p->cost,"�˻��ɹ�");
        }else{
            printf("���ѳɹ��ܾ�һ���˻����룬��ʣ����Щ���������\n");
            recordClientBuy(p->pc,p->pb,p->number,0,"�ܾ��˻�");
        }
        p0->next=p->next;
        clientRequest_SHOW(list);
}

int clientRequest_SHOW(pclientRequestList list){
    pclientRequestList p=list->next;
    int i=0;
    char *request="�˻�";
    printf("***********************************************************************************\n");
    printf("%10s%10s%10s%10s%10s%15s\n","�˺�","Ʒ��","����","����","����","ʱ��");
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
    printf("*************************************************�˻�ԭ��˵��****************************************************\n");
    printf("%s\n",p->info);
    printf("*************************************************�˻�ԭ��˵��****************************************************\n");
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
                printf("%15s%15s%15s%20s%20s%10s%20s\n","�˺�","�û���","����","��ʷ�ܻ���","���","�ȼ�","���»���");
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
                printf("%15s%15s%15s%20s%20s%10s%20s\n","�˺�","�û���","����","��ʷ�ܻ���","���","�ȼ�","���»���");
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
                printf("%15s%15s%15s%20s%20s%10s%20s\n","�˺�","�û���","����","��ʷ�ܻ���","���","�ȼ�","���»���");
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
                printf("%15s%15s%15s%20s%20s%10s%20s\n","�˺�","�û���","����","��ʷ�ܻ���","���","�ȼ�","���»���");
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
                printf("%15s%15s%15s%20s%20s%10s%20s\n","�˺�","�û���","����","��ʷ�ܻ���","���","�ȼ�","���»���");
            }
            printf("%15s%15s%15s%20.2f%20.2f%10d%20.2f\n",p->account,p->username,p->password,p->cost,p->saving,p->grade,p->costMonthly);
            i++;
        }

        p=p->next;
    }
    return i;
}
//*****************************************************����****************************************************
int rankClientCost(pClientLinkedList list,int k){
   pClientLinkedList p0=list->next;
   if(p0->next==NULL) return -1;
   pClientLinkedList p=p0->next;
   if(p->next==NULL) return 1;
   //һЩ���С�
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
   //һЩ���С�
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
    //һЩ���С�
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
    //һЩ���С�
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
    printf("%15s%15s%15s%20s%20s%10s%20s\n","�˺�","�û���","����","��ʷ�ܻ���","���","�ȼ�","���»���");
    while(p!=NULL){
        if(p->grade!=-1){
            printf("%15s%15s%15s%20.2f%20.2f%10d%20.2f\n",p->account,p->username,p->password,p->cost,p->saving,p->grade,p->costMonthly);
        }
        p=p->next;
    }
}
void showClientTop(pClientLinkedList list){
    pClientLinkedList p=list->next;
    printf("%15s%15s%15s%20s%20s%10s%20s\n","�˺�","�û���","����","��ʷ�ܻ���","���","�ȼ�","���»���");
    int i=0;
    while(p!=NULL&&i<=5){
        if(p->grade!=-1){
            printf("%15s%15s%15s%20.2f%20.2f%10d%20.2f\n",p->account,p->username,p->password,p->cost,p->saving,p->grade,p->costMonthly);
            i++;
        }
        p=p->next;
    }
    if(i<3){
        printf("�������㣬����%d��",i);
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

        printf("\n��ǰ���ﳵ����:\n");
        printf("%-12s%-12s%-12s%-12s%-12s%-12s%-12s%-12s%-12s\n", "���", "�˺�", "�û���", "Ʒ��", "����", "����", "����","�ܼ�","��Ϣ");
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
        printf("\n������Ҫ������\n");
        return NULL;
    }

    while (p && i != j) {
        p = p->next;
        j++;
    }

    return p;
}
void searchshoppingcar(pClientshoppingcar list, char* name){
     printf("\n��ʼ��������\n");
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
     printf("Ϊ������'%s'�ؼ��֣���������%d����¼\n", name, sum);
     return;
}
void searchshoppingcar2(pClientshoppingcar list, char* name){
     printf("\n��ʼ��������\n");
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
     printf("Ϊ������'%s'�ؼ��֣���������%d����¼\n", name, sum);
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
    else printf("�̻����㣡\n");
    return 0;
}

void showInfoSaving(pInteractInfo pInfo) {
    printf("��ǰ�ʽ��ǣ�%.2f\n", pInfo->sellerSaving);
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
                printf("��������[%d]����\n", year);
                return -1;
        }

        if ( month < 1 || month > 12 )
        {
                printf("������·�[%d]����\n", month);
                return -1;
        }

        if ( month == 2 )
        {
                // �ж����������,���޸Ķ��µ�monthDays[1]ֵΪ29
                if ( (year % 400 == 0) || \
                     (year % 100 != 0 && year % 4 == 0)
                   )
                {
                        monthDays[1] = 29;
                }
        }

        if ( day < 1 || day > monthDays[month-1] )
        {
                printf("���������[%d]����\n", day);
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
                        printf("�����ʽ����\n");
                        return -1;
                }

                if ( 0 != check_date(start_year, start_month, start_day) )
                {
                        return -1;
                }

                printf("����ɹ�\n");
        }

        return 0;
}
