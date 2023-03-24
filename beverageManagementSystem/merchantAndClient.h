#ifndef MERCHANTANDCLIENT_H
#define MERCHANTANDCLIENT_H

void beverageRecordInit();

void beveragePrintTime(char* file);

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

void writeIntoFile(pBeverageList list);

pBeverageList addFromFile(char* file, pBeverageList list);

//*************************************************************************************

typedef struct clientLinkedList {

    char account[20];

    char password[20];

    char username[20];

    int cost;

    int saving;

    int grade;//-1/123��Ӧ administrator �Ϳͻ��ȼ�һ����

    struct clientLinkedList* next;

}*pClientLinkedList, ClientLinkedList;

typedef pClientLinkedList clientNode;


pClientLinkedList initClient(); // ��ʼ��������������

void signUp(pClientLinkedList list, char* account, char* password, char* username,int saving,int cost,int grade); // ��ע����Ϣд������//������һ�¶���һ��saving//���ﻹ��һ������������ ���������  ��ʱ�������ĺ���һ������һ��status���ж��Ƿ��˻������ɹ�

clientNode signIn(pClientLinkedList list, char* account, char* password,int *status);// ��¼��������Search�������˻� ����ֵʱ���ݿ⣨�����ж�Ӧ�Ľ�㣬�ڵ�½����֮�����пͻ��Ĳ������ǶԸý����в���//��������״̬ ��¼�ɹ�1 �������0 �Լ��Ҳ����˺�-1//����Ա��������һ���������� �������������ע�����Ա

clientNode clientSearch(pClientLinkedList list,char *account);//���û�

void changeAccount(pClientLinkedList list,char* account,char* newAccount);//��c�˺�//�����˺�Ҫ����־֮��ĸ����� �е��鷳�Ȳ�д����

void NewPassword(pClientLinkedList list,char* account,char* newPassword);//������
//���û���

pClientLinkedList clientLogout(pClientLinkedList list,char* account,int *status);//ɾ�û� ����ͷָ��������ͷָ�뱻logout status״̬�����Ƿ�ɹ�0/-1
//*******************************�����ǻ�����¼ ��ɾ�Ĳ�****************************
//*******************************�����ǿͻ����й���*****************************
void deposit(clientNode client, int money); // ���

void buy(clientNode client, pBeverageList list, int number); // ����ָ�������ľ�ˮ

void clientUpgradeCheck(pClientLinkedList list);//����һ��administator ֮������������ͨ�̻�����

void recordInit();//��ʼ�������¼

void recordClientBuy(clientNode client, pBeverageList list, int number);//��¼�̻���������¼�����ļ�

void recordClientAccount(clientNode client,const char behavior[]);

void showStaff(pBeverageList list); // ����printStaff�����������

void showClientRecord();

void printTime(char*  file);

int searchClientBuy(char *info);

int getLinkTotalNodeNum(pBeverageList head);

//***************************************ʱ��*********************************************

#endif // MERCHANTANDCLIENT_H
