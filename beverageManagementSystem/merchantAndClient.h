#ifndef MERCHANTANDCLIENT_H
#define MERCHANTANDCLIENT_H

typedef struct beverageLinkedList {

    char brand[10];

    char name[100];

    char time[100];

    int storeNum;

    int price;

    char info[1000];

    struct beverageLinkedList* next;

}*pBeverageList, BeverageList;

typedef BeverageList BeverageNode;
typedef pBeverageList pBeverageNode;

typedef struct beverageData {

    char brand[10]; // Ʒ��

    char name[100]; // ��ˮ��

    int time; // ����ʱ��

    int storeNum; // ����

    int price; // �۸�

    char info[1000]; // ��ˮ��Ϣ

}*pBeverageData, BeverageData;

int isEmpty(pBeverageList list); // �ж������Ƿ�Ϊ�գ�����int������ֵ

void add(pBeverageList list, pBeverageNode newNode); // ��list�м���newNode

pBeverageList init(); // ��ʼ��������������

pBeverageNode find(pBeverageList head, int i); // �ҵ����ݿ��б��Ϊi�ľ�ˮ��find�����ı���Ǵ�0��ʼ�ģ������Ǵ�1��ʼ

pBeverageNode insert(pBeverageList list, pBeverageNode node, int i); // ��node���뵽list����Ϊi�Ľ��ǰ

pBeverageNode newBeverageNode(char brand[], char name[], char time[], int storeNum, int price, char info[]); // ���ݲ�������һ���µľ�ˮ���

pBeverageList createFromFile(char* file); // ���ļ����������¼������������

void showStaff(pBeverageList list); // ��ӡ������ӡʱ��ˮǰ�����ʾ��0��ʼ�ı�ţ������������ο�

pBeverageList sortBeverageTime(pBeverageList list, int key); // �Ծ�ˮ�Խ���ʱ��Ϊ�ؼ��ʽ�������

pBeverageList sortBeverageBrand(pBeverageList list, int key); // �Ծ�ˮ��Ʒ��Ϊ�ؼ��ʽ�������

pBeverageList sortBeverageStoreNum(pBeverageList list, int key); // �Ծ�ˮ�Կ����Ϊ�ؼ��ʽ�������

pBeverageList sortBeveragePrice(pBeverageList list, int key); // �Ծ�ˮ�Լ۸�Ϊ�ؼ��ʽ�������

void deleteBeverage(pBeverageList list, int pos); // ���ݱ��ɾ��ָ�����

void changeBeverageInfo(pBeverageList list, int number, char* givenInfo); // �޸ı��Ϊnumber�ľ�ˮ��ϢΪinfo

void reduceBeverageStoreNum(pBeverageList list, int number, int reduceNum); // ���پ�ˮ�Ŀ��

void searchBeverageBrand(pBeverageList list, char* givenBrand); // ����givenBrand��ѯ�Ծ�ˮ��Ʒ�ƽ��в�ѯ

void searchBeverageInfo(pBeverageList list, char* givenInfo); // ����givenInfo�Ծ�ˮ����Ϣ���в�ѯ

void searchBeverageName(pBeverageList list, char* givenName); // ����givenName�Ծ�ˮ�����ƽ��в�ѯ

typedef struct clientLinkedList {

    struct clientData* data;

    struct clientLinkedList* next;

}*pClientLinkedList, ClientLinkedList;

typedef pClientLinkedList clientNode;

typedef struct clientData {

    char account[20];

    char password[20];

    char username[20];

    int saving;

}*pClientData, ClientData;

pClientLinkedList initClient(); // ��ʼ��������������

void signUp(pClientLinkedList list, char* account, char* password, char* username); // ��ע����Ϣд������

clientNode signIn(pClientLinkedList list, char* account, char* password); // ��¼������ֵʱ���ݿ⣨�����ж�Ӧ�Ľ�㣬�ڵ�½����֮�����пͻ��Ĳ������ǶԸý����в���

void deposit(clientNode client, int money); // ���

void showStaff(pBeverageList list); // ����printStaff

void buy(clientNode client, pBeverageList list, int number); // ����ָ�������ľ�ˮ

#endif // MERCHANTANDCLIENT_H
