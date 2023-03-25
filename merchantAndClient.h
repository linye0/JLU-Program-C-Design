#ifndef MERCHANTANDCLIENT_H
#define MERCHANTANDCLIENT_H

void beverageRecordInit();

void beveragePrintTime(char* file);

//************************************************************
// 新加的
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

    int price;

    char info[1000];

    struct beverageLinkedList* next;

}*pBeverageList, BeverageList;

typedef BeverageList BeverageNode;
typedef pBeverageList pBeverageNode;

void beverageRecordInit();

void beveragePrintTime(char* file);

int isEmpty(pBeverageList list); // 判断链表是否为空，返回int类型真值

void add(pBeverageList list, pBeverageNode newNode); // 往list中加入newNode

pBeverageList init(); // 初始化，创建空链表

pBeverageNode find(pBeverageList head, int i); // 找到数据库中编号为i的酒水，find函数的编号是从0开始的，而不是从1开始

pBeverageNode insert(pBeverageList list, pBeverageNode node, int i); // 把node插入到list里编号为i的结点前

void insertLast(pBeverageList list, pBeverageNode node);

pBeverageNode newBeverageNode(char brand[], char name[], char time[], int storeNum, int price, char info[], pInteractInfo pInfo); // 根据参数创建一个新的酒水结点

pBeverageList createFromFile(char* file, pInteractInfo pInfo); // 从文件读入进货记录，存入链表中

void showStaff(pBeverageList list); // 打印链表，打印时酒水前面会显示从0开始的编号，供后续操作参考

pBeverageList sortBeverageTime(pBeverageList list, int key); // 对酒水以进货时间为关键词进行排序

pBeverageList sortBeverageBrand(pBeverageList list, int key); // 对酒水以品牌为关键词进行排序

pBeverageList sortBeverageStoreNum(pBeverageList list, int key); // 对酒水以库存量为关键词进行排序

pBeverageList sortBeveragePrice(pBeverageList list, int key); // 对酒水以价格为关键词进行排序

void deleteBeverage(pBeverageList list, int pos); // 根据编号删除指定结点

void changeBeverageInfo(pBeverageList list, int number, char* givenInfo); // 修改编号为number的酒水信息为info

void reduceBeverageStoreNum(pBeverageList list, int number, int reduceNum); // 减少酒水的库存

void searchBeverageBrand(pBeverageList list, char* givenBrand); // 根据givenBrand查询对酒水的品牌进行查询

void searchBeverageInfo(pBeverageList list, char* givenInfo); // 根据givenInfo对酒水的信息进行查询

void searchBeverageName(pBeverageList list, char* givenName); // 根据givenName对酒水的名称进行查询

void writeIntoFile(pBeverageList list);

pBeverageList addFromFile(char* file, pBeverageList list, pInteractInfo pInfo);

pBeverageNode findname(pBeverageList head, char* name);
//************************************下面都是我的捏******************************************************

typedef struct clientLinkedList {

    char account[20];

    char password[20];

    char username[20];

    float cost;

    float saving;

    int grade;//-1/123对应 administrator 和客户等级一二三

    struct clientLinkedList* next;

}*pClientLinkedList, ClientLinkedList;

typedef pClientLinkedList clientNode;


pClientLinkedList initClient(); // 初始化，创建空链表

void signUp(pClientLinkedList list, char* account, char* password, char* username,float saving,float cost,int grade); // 将注册信息写入链表//更改了一下多了一个saving//这里还有一个重名的问题 我先输出了  到时候跟下面的函数一样返回一个status来判断是否账户创建成功

clientNode signIn(pClientLinkedList list, char* account, char* password,int *status);// 登录，运用了Search查找找账户 返回值时数据库（链表）中对应的结点，在登陆操作之后，所有客户的操作都是对该结点进行操作//带回三种状态 登录成功1 密码错误0 以及找不到账号-1//管理员可以设置一个机器密码 有这个东西才能注册管理员

clientNode clientSearch(pClientLinkedList list,char *account);//查用户

void changeUsername(pClientLinkedList list,char* username,char* newUsername);//改c账号//改完账号要把日志之类的给改了 有点麻烦先不写后续

void NewPassword(pClientLinkedList list,char* account,char* newPassword);//改密码
//改用户名

pClientLinkedList clientLogout(pClientLinkedList list,char* account,int *status);//删用户 返回头指针避免出现头指针被logout status状态反馈是否成功0/-1
//*******************************以上是基本登录 增删改查****************************
//*******************************以下是客户进行购买活动*****************************
void deposit(clientNode client, float money); // 存款

int buy(clientNode client, pBeverageList list, int number); // 订购指定数量的酒水

void clientUpgradeCheck(pClientLinkedList list);//除了一个administator 之外其他都是普通商户即可

void recordInit();//初始化购买记录

void recordClientBuy(clientNode client, pBeverageList list, int number,float cost,char* info);//记录商户操作并记录导入文件

void recordClientAccount(clientNode client,const char behavior[]);

void showStaff(pBeverageList list); // 就是printStaff输出整个链表

void showClientRecord();

void printTime(char*  file);

int infoCheck(clientNode p,char *info);

int searchClientBuy(char *info);

int getLinkTotalNodeNum(pBeverageList head);

void printCLientInfo(clientNode p);//输出基本客户信息
//********************************以上是客户进行购买或者其他活动***********************
//********************************以下是管理员 客户退换货处理*************************
typedef struct clientRequest{
    clientNode pc;
    pBeverageNode pb;
    int number;
    float cost;
    char time[40];
    char info[200];
    struct clientRequest* next;
}*pclientRequestList,clientRequestList;//客户退换货链表结构

typedef pclientRequestList clientRequestNode;

pclientRequestList clientRequestListInit();//链表初始化 返回头指针

void clientRequest_PUSH(pclientRequestList list,clientNode client,pBeverageList listb,char *info,char* excuse);
/*
当searchLientBuy函数返回值为1时，将传入searchclienbuy函数的info关键字传入这个函数的char*info 其他参数分别是
退换货链表表头指针 当前进行操作的用户节点  饮料库存链表的头指针 info 以及退换货原因-excuse
只能对一条购货记录进行操作
*/

void clientRequest_POP(pclientRequestList list,int choice,int operate, pInteractInfo pInfo);
//退换货链表弹出操作。参数是 退换货链表头指针 对第几条进行操作（管理员会先看整个链表） 什么操作 1是同意退货 2是不同意
int clientRequest_SHOW(pclientRequestList list);
//展示整个退换货链表的基本信息 不展示退货原因
void clientRequest_SHOWMORE(pclientRequestList list,int choice);
//展示特定第几条的退货信息的退货原因
void searchClientBuy_FORREQUEST(char *info,char requestInfo[]);
//这个以及下面那个不出现在main.c里 内部调用。
pBeverageList searchBeverage_FORREQUEST(pBeverageList list , char* giveBrand,char* giveName);

int Check(char* ch);

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

pClientshoppingcar initshoppingcar();//初始化，创建链表

void addshoppingcar(pClientshoppingcar Testlist,pClientLinkedList list,pBeverageList testList,int amount);//增加购物车内容

pClientshoppingcar deleteshoppingcar(pClientshoppingcar Testlist,char* name,int *status);//删除购物车内容 返回头指针避免出现头指针被logout status状态反馈是否成功0/-1

void changeshoppingcar(pClientshoppingcar Testlist,char* name,int amount);//改变购物车信息


void showshoppingcar(pClientshoppingcar list,char* username);//打印链表

pClientshoppingcar finding(pClientshoppingcar head, int i);//查找链表结点

void searchshoppingcar(pClientshoppingcar list, char* name); // 根据名称对购物车进行查询

void searchCarinfo(pClientshoppingcar list, char* username);
int blank(char judge[]);
int getNum(pClientshoppingcar head);
#endif // MERCHANTANDCLIENT_H
