#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>
#include <conio.h>
#include "merchantAndClient.h"

int main(void){

<<<<<<< HEAD
    beverageRecordInit();

    pBeverageList testList = createFromFile("D:\\JLU-Program-C-Design\\Data\\进货条目.txt");
=======
    pInteractInfo pInfo = initInteractInfo(10000000000);

    printf("剩余存款：%f\n", pInfo->sellerSaving);

    beverageRecordInit();

    pBeverageList testList = createFromFile("D:\\CSdiy\\JLU-Program-C-Design-linye\\Data\\进货条目.txt", pInfo);
>>>>>>> 324d5d8 (InteractInfo)

    showStaff(testList);

    testList = sortBeverageBrand(testList, -1);

    showStaff(testList);

    searchBeverageInfo(testList, "崭新");

    searchBeverageBrand(testList, "茅台");

    searchBeverageName(testList, "快乐");

    deleteBeverage(testList, 1);

    showStaff(testList);

    changeBeverageInfo(testList, 4, "怡宝怡宝");

    reduceBeverageStoreNum(testList, 4, 12);

    testList = sortBeverageStoreNum(testList, -1);

    showStaff(testList);

    testList = sortBeveragePrice(testList, -1);

    showStaff(testList);

    testList = sortBeverageTime(testList, -1);

    showStaff(testList);

<<<<<<< HEAD
    testList = addFromFile("D:\\JLU-Program-C-Design\\Data\\进货条目.txt", testList);
=======
    testList = addFromFile("D:\\CSdiy\\JLU-Program-C-Design-linye\\Data\\进货条目.txt", testList, pInfo);
>>>>>>> 324d5d8 (InteractInfo)

    showStaff(testList);

    writeIntoFile(testList);
<<<<<<< HEAD
=======

    printf("剩余存款：%f\n", pInfo->sellerSaving);
>>>>>>> 324d5d8 (InteractInfo)
}

/*
int kehu(pClientLinkedList a,pBeverageList testList,pClientLinkedList list){
    pBeverageList p;
    system("cls");
    printf("  登录成功\n");
    printf("请选择功能列表\n");
    printf("1.查询存款\n");
    printf("2.查询商品\n");
    printf("3.订购\n");
    printf("4.充值\n");
    printf("5.更改用户名或密码\n");
    printf("6.查询购买记录\n");
    printf("7.注销账户\n");
    printf("8.退出\n");
    char f=_getch();
    switch(f)
    {
    case'1':
    system("cls");
   printf("您的存款为:\n");
   printf("%d\n",a->saving);
    system("pause");
    system("cls");
    kehu(a,testList,list);
    break;
    case'2':
    system("cls");
    printf("请选择\n");
    printf("1、查看所有商品\n");
    printf("2、根据品牌查找商品\n");
    printf("3、根据名称商品\n");
    printf("4、根据酒水信息查找商品\n");
    char m=_getch();
    switch(m){
    case'1':
        system("cls");
        showStaff(testList);
        system("pause");
      kehu(a,testList,list);
        break;
    case'2':
        system("cls");
        showStaff(testList);
        printf("请输入品牌：\n");
        char o[20];
        fgets(o, 19, stdin);
        searchBeverageBrand(testList,o);
        system("pause");
     kehu(a,testList,list);
        break;
    case'3':
        system("cls");
        showStaff(testList);
        printf("请输入名称：\n");
        char p[20];
        fgets(p, 19, stdin);
        searchBeverageName(testList,p);
        system("pause");
     kehu(a,testList,list);
        break;
    case'4':
        system("cls");
        showStaff(testList);
        printf("请输入信息：\n");
        char j[20];
        fgets(j,19, stdin);
        searchBeverageInfo(testList,j);
        system("pause");
       kehu(a,testList,list);
        break;
    default:
        printf("输入有误，请重新输入\n");
        system("pause");
       kehu(a,testList,list);
        break;
    }
    break;
    case'3':
    system("cls");
    showStaff(testList);
    printf("请选择酒水编号\n");
    int h;
    scanf_s("%d",&h);
    int b=getLinkTotalNodeNum(testList);
    b=b-1;
    char j[20];
    fgets(j,19, stdin);
    if(h>=1&&h<=b)
    {h=h+1;
    p=find(testList, h);
    printf("请选择订购数量\n");
    int nm;
    scanf_s("%d",&nm);
    char o[20]=" ";
    fgets(o,19, stdin);
    if(nm>0&&strlen(o) == 0){
    if(a->saving>=(p->price*nm))
    {
    buy(a, p, nm);
    printf("订购成功\n");
    system("pause");
   kehu(a,testList,list);
    break;}
    else
    {printf("余额不足\n");
     system("pause");
    kehu(a,testList,list);
    break;}}
    else
        printf("请输入正确的数量\n");
       system("pause");
  kehu(a,testList,list);
    break;}
    else {
        printf("请输入正确的编号\n");
        system("pause");
        kehu(a,testList,list);
        break;
    }
    case '4':
        system("cls");
        printf("请输入充值金额：\n");
        int g;
        char c[20];
        if(scanf_s("%d",&g)>0)
            {deposit(a, g);
            printf("充值成功\n");
            system("pause");
            kehu(a,testList,list);}
        else{fgets(c,19, stdin);
            printf("请输入正确的金额\n");
             system("pause");
            kehu(a,testList,list);}
        break;
    case'5':
        system("cls");
        printf("请输入新密码：\n");
        char y[20];
        fgets(y,19, stdin);
        NewPassword(a,a->account,y);
        system("pause");
       kehu(a,testList,list);
        break;
    case'6':
        system("cls");
        printf("%10s%11s%10s%11s%10s%10s%9s\n","账号","用户名","货物品牌","货物名称","货物价格","购买数量","时间");
        int i=searchClientBuy(a->account);
           printf("总共有%d条记录\n",i);
        system("pause");
        kehu(a,testList,list);
        break;
    case'7':
        system("cls");
        int status;
        clientLogout(list,a->account,&status);
        if(status==0)
            printf("删除成功\n");
        else
            printf("删除失败，请重试\n");
        system("pause");
        break;

    case'8':
         system("cls");
        break;
    default:
    printf("输入有误，请重新输入\n");
    system("pause");
    system("cls");
  kehu(a,testList,list);
    break;
    }return 0;
}

int shanghu(pBeverageList testList){
    system("cls");
printf("请选择功能列表\n");
  printf("1.进货\n");
  printf("2.查询库存\n");
  printf("3.商品排序\n");
  printf("4.删除库存\n");
  printf("5.修改商品信息\n");
  printf("6.返回\n");
  char d =_getch();
  switch(d)

  {case'1':
  {system("cls");
      printf("请选择进货方式\n");
      printf("1.手动输入进货信息\n");
      printf("2.从文件读入进货信息\n");
      char j=_getch();
      switch (j) {
      case'1':
      system("cls");
      printf("请输入品牌\n");
      char fe[20];
      fgets(fe,19, stdin);
      printf("请输入商品名\n");
      char fd[20];
      fgets(fd,19, stdin);
      printf("请输入进货时间\n");
      char fg[20];
      fgets(fg,19, stdin);
      printf("请输入商品数量\n");
      int k;
      scanf_s("%d",&k);
      printf("请输入商品价格\n");
      int l;
      scanf_s("%d",&l);
      char ch=getchar();
      printf("请输入商品信息\n");
      char fs[20];
      fgets(fs,19, stdin);
      pBeverageList newNode=newBeverageNode(fe, fd, fg, k, l, fs);
      insertLast(testList, newNode);
       printf("进货成功");
          break;
      case'2':
          system("cls");
          printf("请输入文件地址\n");
          char u[50];
          fgets(u,49, stdin);
          addFromFile(u, testList);
          printf("进货成功");
          break;
      default:printf("输入错误，请重新输入\n");
          break;}
      showStaff(testList);
      system("pause");
      system("cls");
      shanghu(testList);
      break;}
  case'2':
  {system("cls");
      showStaff(testList);
      system("pause");
      system("cls");
      shanghu(testList);
      break;}
  case'3':
  {system("cls");
      system("cls");
      printf("请选择\n");
      printf("1、对酒水以进货时间为关键词进行排序\n");
      printf("2、对酒水以品牌为关键词进行排序\n");
      printf("3、对酒水以库存量为关键词进行排序\n");
      printf("4、对酒水以价格为关键词进行排序\n");
      char m=_getch();
      switch(m){
      case'1':
          system("cls");
          printf("请选择排序方式：\n");
          printf("1、正序\n");
          printf("2、倒序\n");
          char l=_getch();
          switch (l) {
          case'1':
              testList = sortBeverageTime(testList, 1);
              showStaff(testList);
              system("pause");
              system("cls");
              shanghu(testList);
              break;
          case'2':
              testList = sortBeverageTime(testList, -1);
              showStaff(testList);
              system("pause");
              system("cls");
              shanghu(testList);
              break;
          default:
              printf("输入有误");
              system("pause");
              system("cls");
              shanghu(testList);
              break;
          }
          system("pause");
          shanghu(testList);
          break;
      case'2':
          system("cls");
          printf("请选择排序方式：\n");
          printf("1、正序\n");
          printf("2、倒序\n");
          char r=_getch();
          switch (r) {
          case'1':
              testList = sortBeverageBrand(testList, 1);
              showStaff(testList);
              system("pause");
              system("cls");
              shanghu(testList);
              break;
          case'2':
              testList = sortBeverageBrand(testList, -1);
              showStaff(testList);
              system("pause");
              system("cls");
              shanghu(testList);
              break;
          default:
              printf("输入有误");
              system("pause");
              system("cls");
              shanghu(testList);
              break;
          }
          system("pause");
          shanghu(testList);
          break;
      case'3':
          system("cls");
          printf("请选择排序方式：\n");
          printf("1、正序\n");
          printf("2、倒序\n");
          char t=_getch();
          switch (t) {
          case'1':
              testList = sortBeverageStoreNum(testList, 1);
              showStaff(testList);
              system("pause");
              system("cls");
              shanghu(testList);
              break;
          case'2':
              testList = sortBeverageStoreNum(testList, -1);
              showStaff(testList);
              system("pause");
              system("cls");
              shanghu(testList);
              break;
          default:
              printf("输入有误");
              system("pause");
              system("cls");
              shanghu(testList);
              break;
          }
          system("pause");
          shanghu(testList);
          break;
      case'4':
          system("cls");
          printf("请选择排序方式：\n");
          printf("1、正序\n");
          printf("2、倒序\n");
          char y=_getch();
          switch (y) {
          case'1':
              testList = sortBeveragePrice(testList, 1);
              showStaff(testList);
              system("pause");
              system("cls");
              shanghu(testList);
              break;
          case'2':
              testList = sortBeveragePrice(testList, -1);
              showStaff(testList);
              system("pause");
              system("cls");
              shanghu(testList);
              break;
          default:
              printf("输入有误");
              system("pause");
              system("cls");
              shanghu(testList);
              break;
          }
          system("pause");
          shanghu(testList);
          break;
      }
      system("pause");

      shanghu(testList);
      break;
  }
  case'4':
  {system("cls");
      showStaff(testList);
      printf("请输入删除的产品编号\n");
      int bh ;
      scanf_s("%d",&bh);
      printf("%d", bh);
      deleteBeverage(testList, bh);
      printf("成功删除\n");
      system("cls");
      showStaff(testList);
      system("pause");
      shanghu(testList);
      break;}
  case'5':
  {system("cls");
      showStaff(testList);
      printf("请输入产品编号\n");
      int bi=_getch()-'0';
      printf("请输入产品信息\n");
      char ke[20];
      fgets(ke,19, stdin);
      changeBeverageInfo(testList, bi, ke);
      printf("修改成功\n");
      system("pause");
      shanghu(testList);
      break;}
  case'6':
  {system("cls");
      break;}
  default:
      printf("输入有误，请重新输入\n");
      system("pause");
      system("cls");
      shanghu(testList);
      break;}return 0;
      }

int denglu(pClientLinkedList list ,pBeverageList testList){
    pClientLinkedList p;
    int status;
    system("cls");
  printf("     请选择\n");
  printf("1.登录     2.注册\n");
  char c=_getch();
  switch(c)
  {
  case'1':
  {system("cls");
  printf("请输入账号\n");
  char zh[20];
  fgets(zh,19, stdin);
  printf("请输入密码\n");
  char mi[20];
  fgets(mi,19, stdin);
 p=signIn(list, zh, mi, &status);
 switch (status) {
 case 1:
    kehu(p,testList,list);
    break;
 case 0:
     system("pause");
     break;
 case 4:
  shanghu(testList);
  break;
 case -1:
    system("pause");
     break;
 }
     break;}
  case'2':
  {system("cls");

  printf("请输入用户名\n");
  char yh[20];
  fgets(yh,19, stdin);
  if(strlen(yh)==0)
     { printf("用户名不能为空\n");
      system("pause");
      break;}
  printf("请输入账号\n");
  char hz[20];
  fgets(hz,19, stdin);
  if(strlen(hz)==0)
     { printf("账号不能为空\n");
      system("pause");
      break;}
  printf("请输入密码\n");
  char im[20];
  fgets(im,19, stdin);
  if(strlen(im)==0)
     { printf("密码不能为空\n");
      system("pause");
      break;}
  signUp(list, hz, im, yh,0,0,1);
  printf("注册成功");
  system("pause");
  system("cls");
      break;}
  default:
      printf("输入有误，请重新输入\n");
      system("pause");
      system("cls");
      denglu(list,testList);
      break;
  }return 0;
}

int main()
{

  pBeverageList testList = createFromFile("D:\\JLU-Program-C-Design\\Data\\进货条目.txt");
   recordInit();
  pClientLinkedList list=initClient();
  signUp(list, "111", "111", "shanghu",0,0,-1);
 while(1)
{system("cls");
 printf("欢迎进入酒水管理系统\n");
 system("pause");
 system("cls");
 denglu(list,testList);

}
    return 0;
}
*/
