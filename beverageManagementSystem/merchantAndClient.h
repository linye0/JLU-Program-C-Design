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

    char brand[10]; // 品牌

    char name[100]; // 酒水名

    int time; // 进货时间

    int storeNum; // 存量

    int price; // 价格

    char info[1000]; // 酒水信息

}*pBeverageData, BeverageData;

int isEmpty(pBeverageList list); // 判断链表是否为空，返回int类型真值

void add(pBeverageList list, pBeverageNode newNode); // 往list中加入newNode

pBeverageList init(); // 初始化，创建空链表

pBeverageNode find(pBeverageList head, int i);

pBeverageNode insert(pBeverageList list, pBeverageNode node, int i);

pBeverageNode newBeverageNode(char brand[], char name[], char time[], int storeNum, int price, char info[]);

pBeverageList createFromFile(char* file); // 从文件读入进货记录，存入链表中

void showStaff(pBeverageList list); // 打印链表，打印时酒水前面会显示从0开始的编号，供后续操作参考

pBeverageList sortBeverageBrand(pBeverageList list, int key); // 对酒水以品牌为关键词进行排序

void deleteBeverage(pBeverageList list, int pos); // 根据编号删除指定结点

pBeverageList chageBeverage(int number, char* key, char* newValue); // 修改酒水属性

pBeverageNode searchBeverage(struct beverageData data); // 还没想清楚search的关键字要怎么搞

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

pClientLinkedList initClient(); // 初始化，创建空链表

void signUp(pClientLinkedList list, char* account, char* password, char* username); // 将注册信息写入链表

clientNode signIn(pClientLinkedList list, char* account, char* password); // 登录，返回值时数据库（链表）中对应的结点，在登陆操作之后，所有客户的操作都是对该结点进行操作

void deposit(clientNode client, int money); // 存款

void showStaff(pBeverageList list); // 就是printStaff

void buy(clientNode client, pBeverageList list, int number); // 订购指定数量的酒水

#endif // MERCHANTANDCLIENT_H
