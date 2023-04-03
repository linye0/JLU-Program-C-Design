#ifndef MERCHANTANDCLIENT_H
#define MERCHANTANDCLIENT_H

void beverageRecordInit();

void beveragePrintTime(char* file);

//************************************************************
// �¼ӵ�
typedef struct interactInfo {
    float sellerSaving;
}InteractInfo, *pInteractInfo;

pInteractInfo initInteractInfo(float saving);

int reduceSaving(pInteractInfo pInfo, float price);

void showInfoSaving(pInteractInfo pInfo);

//**************************************************************
typedef struct beverageLinkedList {

    char brand[10];

    char name[100];

    char time[100];

    int storeNum;

    float price;

    char info[1000];

    int sales;

    int level[100];

    struct beverageLinkedList* next;

}*pBeverageList, BeverageList;

typedef BeverageList BeverageNode;
typedef pBeverageList pBeverageNode;

void beverageRecordInit();

void beveragePrintTime(char* file);

int isEmpty(pBeverageList list); // �ж������Ƿ�Ϊ�գ�����int������ֵ

void add(pBeverageList list, pBeverageNode newNode); // ��list�м���newNode

pBeverageList init(); // ��ʼ��������������

pBeverageNode find(pBeverageList head, int i); // �ҵ����ݿ��б��Ϊi�ľ�ˮ��find�����ı���Ǵ�0��ʼ�ģ������Ǵ�1��ʼ

pBeverageNode insert(pBeverageList list, pBeverageNode node, int i); // ��node���뵽list����Ϊi�Ľ��ǰ

void insertLast(pBeverageList list, pBeverageNode node);

pBeverageNode newBeverageNode(char brand[], char name[], char time[], int storeNum, float price, char info[], pInteractInfo pInfo, int sales); // ���ݲ�������һ���µľ�ˮ���

pBeverageList createFromFile(char* file, pInteractInfo pInfo); // ���ļ����������¼������������

void showStaff(pBeverageList list); // ��ӡ������ӡʱ��ˮǰ�����ʾ��0��ʼ�ı�ţ������������ο�

pBeverageList sortBeverageTime(pBeverageList list, int key); // �Ծ�ˮ�Խ���ʱ��Ϊ�ؼ��ʽ�������

pBeverageList sortBeverageBrand(pBeverageList list, int key); // �Ծ�ˮ��Ʒ��Ϊ�ؼ��ʽ�������

pBeverageList sortBeverageStoreNum(pBeverageList list, int key); // �Ծ�ˮ�Կ����Ϊ�ؼ��ʽ�������

pBeverageList sortBeveragePrice(pBeverageList list, int key); // �Ծ�ˮ�Լ۸�Ϊ�ؼ��ʽ�������

pBeverageList sortBeverageSales(pBeverageList List, int key); // �Ծ�ˮ������Ϊ�ؼ��ʽ�������

pBeverageList sortBeverageSaleMoney(pBeverageList List, int key); // �Ծ�ˮ�����۶�Ϊ�ؼ��ʽ�������

void deleteBeverage(pBeverageList list, int pos); // ���ݱ��ɾ��ָ�����

void changeBeverageInfo(pBeverageList list, int number, char* givenInfo); // �޸ı��Ϊnumber�ľ�ˮ��ϢΪinfo

void reduceBeverageStoreNum(pBeverageList list, int number, int reduceNum); // ���پ�ˮ�Ŀ��

void searchBeverageBrand(pBeverageList list, char* givenBrand); // ����givenBrand��ѯ�Ծ�ˮ��Ʒ�ƽ��в�ѯ

void searchBeverageInfo(pBeverageList list, char* givenInfo); // ����givenInfo�Ծ�ˮ����Ϣ���в�ѯ

void searchBeverageName(pBeverageList list, char* givenName); // ����givenName�Ծ�ˮ�����ƽ��в�ѯ

void writeIntoFile(pBeverageList list);

pBeverageList addFromFile(char* file, pBeverageList list, pInteractInfo pInfo);

pBeverageNode findname(pBeverageList head, char* name);

void showData(pBeverageList list);

void writeIntoFileAuto(pBeverageList list);

pInteractInfo initInteractInfoFromFile();

pBeverageList initBeverageFromFileAuto();

pBeverageNode newBeverageNodeNoReduce(char brand[], char name[], char time[], int storeNum, float price, char info[], int sales);

pBeverageList sortBeverageSalesNoDisplay(pBeverageList list, int key);

pBeverageList sweepDate(pBeverageList head, char* date);
//************************************���涼���ҵ���******************************************************

typedef struct clientLinkedList {

    char account[20];

    char password[20];

    char username[20];

    float cost;

    float saving;

    int grade;//-1/123��Ӧ administrator �Ϳͻ��ȼ�һ����

    int gradebonus;

    float costMonthly;

    struct clientLinkedList* next;

}*pClientLinkedList, ClientLinkedList;

typedef pClientLinkedList clientNode;


pClientLinkedList initClient(); // ��ʼ��������������

int signUp(pClientLinkedList list, char* account, char* password, char* username,float saving,float cost,int grade); // ��ע����Ϣд������//������һ�¶���һ��saving//���ﻹ��һ������������ ���������  ��ʱ�������ĺ���һ������һ��status���ж��Ƿ��˻������ɹ�

clientNode signIn(pClientLinkedList list, char* account, char* password,int *status);// ��¼��������Search�������˻� ����ֵʱ���ݿ⣨�����ж�Ӧ�Ľ�㣬�ڵ�½����֮�����пͻ��Ĳ������ǶԸý����в���//��������״̬ ��¼�ɹ�1 �������0 �Լ��Ҳ����˺�-1//����Ա��������һ���������� �������������ע�����Ա

clientNode clientSearch(pClientLinkedList list,char *account);//���û�

void changeUsername(pClientLinkedList list,char* username,char* newUsername);//��c�˺�//�����˺�Ҫ����־֮��ĸ����� �е��鷳�Ȳ�д����

void NewPassword(pClientLinkedList list,char* account,char* newPassword);//������
//���û���

pClientLinkedList clientLogout(pClientLinkedList list,char* account,int *status);//ɾ�û� ����ͷָ��������ͷָ�뱻logout status״̬�����Ƿ�ɹ�0/-1
//*******************************�����ǻ�����¼ ��ɾ�Ĳ�****************************
//*******************************�����ǿͻ����й���*****************************
void deposit(clientNode client, float money); // ���

int buy(clientNode client, pBeverageList list, int number,pClientLinkedList list0); // ����ָ�������ľ�ˮ

void clientUpgradeCheck(pClientLinkedList list);//����һ��administator ֮������������ͨ�̻�����


void recordClientBuy(clientNode client, pBeverageList list, int number,float cost,char* info);//��¼�̻���������¼�����ļ�

void recordClientAccount(clientNode client,const char behavior[]);

void showStaff(pBeverageList list); // ����printStaff�����������

void showClientRecord();

void printTime(char*  file);

int infoCheck(clientNode p,char *info);

int searchClientBuy(char *info);

int getLinkTotalNodeNum(pBeverageList head);

void printClientInfo(clientNode p,pClientLinkedList list);

void printCLientArchive(clientNode P);

//��������ͻ���Ϣ
//********************************�����ǿͻ����й�����������***********************
//********************************�����ǹ���Ա �ͻ��˻�������*************************
typedef struct clientRequest{
    clientNode pc;
    pBeverageNode pb;
    int number;
    float cost;
    char time[40];
    char info[200];
    struct clientRequest* next;
}*pclientRequestList,clientRequestList;//�ͻ��˻�������ṹ

typedef pclientRequestList clientRequestNode;

pclientRequestList clientRequestListInit();//�����ʼ�� ����ͷָ��

void clientRequest_PUSH(pclientRequestList list,clientNode client,pBeverageList listb,char *info,char* excuse);
/*
��searchLientBuy��������ֵΪ1ʱ��������searchclienbuy������info�ؼ��ִ������������char*info ���������ֱ���
�˻��������ͷָ�� ��ǰ���в������û��ڵ�  ���Ͽ�������ͷָ�� info �Լ��˻���ԭ��-excuse
ֻ�ܶ�һ��������¼���в���
*/

void clientRequest_POP(pclientRequestList list,int choice,int operate, pInteractInfo pInfo);
//�˻��������������������� �˻�������ͷָ�� �Եڼ������в���������Ա���ȿ��������� ʲô���� 1��ͬ���˻� 2�ǲ�ͬ��
int clientRequest_SHOW(pclientRequestList list);
//չʾ�����˻�������Ļ�����Ϣ ��չʾ�˻�ԭ��
void clientRequest_SHOWMORE(pclientRequestList list,int choice);
//չʾ�ض��ڼ������˻���Ϣ���˻�ԭ��
void searchClientBuy_FORREQUEST(char *info,char requestInfo[]);
//����Լ������Ǹ���������main.c�� �ڲ����á�
pBeverageList searchBeverage_FORREQUEST(pBeverageList list , char* giveBrand,char* giveName);

int Check(char* ch);

void reprintClient(pClientLinkedList list);

void showClientAll(pClientLinkedList list);

int showClientTop(pClientLinkedList list);

int rankClientCost(pClientLinkedList list,int k);

int rankClientCostMonthly(pClientLinkedList list,int k);

int rankClientUsername(pClientLinkedList list,int k);

int rankClientAccount(pClientLinkedList list,int k);


int  searchClientCost(pClientLinkedList list,float max,float min);

int  searchClientCostMOnthly(pClientLinkedList list,float max,float min);

int  searchClientGrade(pClientLinkedList list,int max,int min);

int  searchClientName(pClientLinkedList list,char* name);

int  searchClientAccount(pClientLinkedList list,char* account);

void clientBonusGrade(pClientLinkedList list,int number ,int grade);

void clientBonusSaving(pClientLinkedList list,int number,float saving);
//*****************************************************************************
typedef struct clientshoppingcar {

    char account[20];

    char username[20];

    char brand[10];

    char name[100];

    char info[1000];

    int price;

    int amount;

    int cost;

    struct clientshoppingcar* next;

}*pClientshoppingcar, Clientshoppingcar;

typedef pClientshoppingcar shopNode;

int is_valid_date(const char *startDate);

pClientshoppingcar initshoppingcar();//��ʼ������������

void addshoppingcar(pClientshoppingcar Testlist,pClientLinkedList list,pBeverageList testList,int amount);//���ӹ��ﳵ����

pClientshoppingcar deleteshoppingcar(pClientshoppingcar Testlist,char* name,int *status);//ɾ�����ﳵ���� ����ͷָ��������ͷָ�뱻logout status״̬�����Ƿ�ɹ�0/-1

void changeshoppingcar(pClientshoppingcar Testlist,char* name,int amount);//�ı乺�ﳵ��Ϣ


void showshoppingcar(pClientshoppingcar list,char* username);//��ӡ����

pClientshoppingcar finding(pClientshoppingcar head, int i);//����������

void searchshoppingcar(pClientshoppingcar list, char* name); // �������ƶԹ��ﳵ���в�ѯ

void searchshoppingcar2(pClientshoppingcar list, char* name);
void searchCarinfo(pClientshoppingcar list, char* username);

int blank(char judge[]);

int getNum(pClientshoppingcar head);

int check_date(int year, int month, int day);

#endif // MERCHANTANDCLIENT_H
