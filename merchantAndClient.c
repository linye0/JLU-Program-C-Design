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
        printf("\n��������Ҫ������\n");
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
        printf("%-12s%-12s%-12s%-12s%-12s%-12s%-12s\n", "���", "Ʒ��", "��ˮ��", "����ʱ��", "����", "�۸�", "��Ϣ");
        while (p)  //ѭ���������ڵ�ֵ���
        {
            p = p->next;//��һ������ֵ   ����
            if(p) printf("%-12d%-12s%-12s%-12s%-12d%-12d%-12s\n", i, p->brand, p->name, p->time, p->storeNum, p->price, p->info);
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
            // ���prevMaxNode == NULL��˵����������p��㣬��ʱֱ�ӽ�p����������������pָ����һ�����
            if (prevMaxNode == NULL) {
                pBeverageNode nextP = p->next;
                p->next = NULL;
                insertPos->next = p;
                p = nextP;
            } else {
                // ���prevMaxNode != NULL����maxNode�������������ý�p����
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
            // ���prevMaxNode == NULL��˵����������p��㣬��ʱֱ�ӽ�p����������������pָ����һ�����
            if (prevMaxNode == NULL) {
                pBeverageNode nextP = p->next;
                p->next = NULL;
                insertPos->next = p;
                p = nextP;
            } else {
                // ���prevMaxNode != NULL����maxNode�������������ý�p����
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
            // ���prevMaxNode == NULL��˵����������p��㣬��ʱֱ�ӽ�p����������������pָ����һ�����
            if (prevMaxNode == NULL) {
                pBeverageNode nextP = p->next;
                p->next = NULL;
                insertPos->next = p;
                p = nextP;
            } else {
                // ���prevMaxNode != NULL����maxNode�������������ý�p����
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
            // ���prevMaxNode == NULL��˵����������p��㣬��ʱֱ�ӽ�p����������������pָ����һ�����
            if (prevMaxNode == NULL) {
                pBeverageNode nextP = p->next;
                p->next = NULL;
                insertPos->next = p;
                p = nextP;
            } else {
                // ���prevMaxNode != NULL����maxNode�������������ý�p����
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

pBeverageList addFromFile(char* file, pBeverageList list) {
    FILE*fp;
    fp = fopen(file, "r");
    int line_len = 0;
    char ch[1000] = {0};

    pBeverageNode head = list;

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
        printf("�û����Ѵ��ڣ�����������\n");
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
                recordClientAccount(p,"��ͨ��¼");
                *status=1;
            }else
            {
                recordClientAccount(p,"������¼");
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
    printf("���޸�����Ϊ��%s\n",p->password);
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
    char file0[]="D:\\qt\\qt project\\1\\buy.txt";
    fp = fopen(file0,"w");
   fprintf(fp,"%10s%11s%10s%11s%10s%10s%9s\n","�˺�","�û���","����Ʒ��","��������","����۸�","��������","ʱ��");
    fclose(fp);
    char file1[]="D:\\qt\\qt project\\1\\client.txt";
    fp = fopen(file1,"w");
    fprintf(fp,"%10s%10s%10s%10s\n","�˺�","�û���","��Ϊ","ʱ��");
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
    char file[]="D:\\qt\\qt project\\1\\client.txt";
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

//��-->

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
        printf("%-12s%-12s%-12s%-12s%-12s%-12s%-12s%-12s%-12s\n", "���", "�˺�", "�û���", "Ʒ��", "����", "��Ϣ", "����","����","�ܼ�");
        while (p != NULL) {
            if (strcmp(p->username,username)==0) {
                printf("%-12d%-12s%-12s%-12s%-12s%-12s%-12d%-12d%-12d\n", i, p->account, p->username, p->brand, p->name, p->info, p->price,p->amount,p->cost);
                i++;
            }

            p = p->next;
        }

}

pClientshoppingcar finding(pClientshoppingcar head, int i){
    int j = 1;
    pClientshoppingcar p=head;
    if (i < 1) {
        printf("\n��������Ҫ������\n");
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