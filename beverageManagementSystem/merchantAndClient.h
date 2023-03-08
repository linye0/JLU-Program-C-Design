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

pBeverageNode find(pBeverageList head, int i);

pBeverageNode insert(pBeverageList list, pBeverageNode node, int i);

pBeverageNode newBeverageNode(char brand[], char name[], char time[], int storeNum, int price, char info[]);

pBeverageList createFromFile(char* file); // ���ļ����������¼������������

void showStaff(pBeverageList list); // ��ӡ������ӡʱ��ˮǰ�����ʾ��0��ʼ�ı�ţ������������ο�

pBeverageList sortBeverageBrand(pBeverageList list, int key); // �Ծ�ˮ��Ʒ��Ϊ�ؼ��ʽ�������

void deleteBeverage(pBeverageList list, int pos); // ���ݱ��ɾ��ָ�����

pBeverageList chageBeverage(int number, char* key, char* newValue); // �޸ľ�ˮ����

pBeverageNode searchBeverage(struct beverageData data); // ��û�����search�Ĺؼ���Ҫ��ô��

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
