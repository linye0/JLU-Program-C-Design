#ifndef MERCHANTANDCLIENT_H
#define MERCHANTANDCLIENT_H

typedef struct beverageLinkedList {

    char brand[10];

    char name[100];

    int time;

    int storeNum;

    char info[1000];

    struct beverageLinkedList* next;

}*pBeverageList, BeverageList;

typedef pBeverageList beverageNode;

typedef struct beverageData {

    char brand[10]; // 品牌

    char name[100]; // 酒水名

    int time; // 进货时间

    int storeNum; // 存量

    char info[1000]; // 酒水信息

}*pBeverageData, BeverageData;

int isEmpty(pBeverageList list); // 判断链表是否为空，返回int类型真值

void add(pBeverageList list, beverageNode newNode); // 往list中加入newNode

pBeverageList init(); // 初始化，创建空链表

pBeverageList createFromString(char* record); // 从字符串读入进货记录，存入链表中

// pBeverageList createFromFile(File* fp); // 从文件读入进货记录，存入链表中

pBeverageList sortBeverage(pBeverageList list, char* key); // 根据关键词对链表进行排序

void printStaff(pBeverageList list); // 打印链表，打印时酒水前面会显示从0开始的编号，供后续操作参考

void deleteBeverage(int number); // 根据编号删除指定结点

pBeverageList chageBeverage(int number, char* key, char* newValue); // 修改酒水属性

beverageNode searchBeverage(struct beverageData data); // 还没想清楚search的关键字要怎么搞
//************************************下面都是我的捏******************************************************

typedef struct clientLinkedList {

    char account[20];

    char password[20];

    char username[20];

    int saving;

    struct clientLinkedList* next;

}*pClientLinkedList, ClientLinkedList;

typedef pClientLinkedList clientNode;


pClientLinkedList initClient(); // 初始化，创建空链表

void signUp(pClientLinkedList list, char* account, char* password, char* username,int saving); // 将注册信息写入链表//更改了一下多了一个saving

clientNode signIn(pClientLinkedList list, char* account, char* password,int *status);
// 登录，运用了Search查找找账户 返回值时数据库（链表）中对应的结点，在登陆操作之后，所有客户的操作都是对该结点进行操作
//带回三种状态 登录成功1 密码错误0 以及找不到账号-1

clientNode clientSearch(pClientLinkedList list,char *account);//查用户

void chageAccount(pClientLinkedList list,char* account,char* newAccount);//改c账号//改完账号要把日志之类的给改了 有点麻烦先不写后续

void NewPassword(pClientLinkedList list,char* account,char* newPassword);//改密码
//改用户名

pClientLinkedList clientLogout(pClientLinkedList list,char* account,int *status);//删用户 返回头指针避免出现头指针被logout status状态反馈是否成功0/-1

void deposit(clientNode client, int money); // 存款

void showStaff(pBeverageList list); // 就是printStaff

void buy(clientNode client, pBeverageList list, int number); // 订购指定数量的酒水

#endif // MERCHANTANDCLIENT_H
