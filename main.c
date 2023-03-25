#include <string.h>
#include "merchantAndClient.h"
#include<time.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
pBeverageList testList = NULL;
pInteractInfo pInfo = NULL;
int kehu(pClientLinkedList a,pClientLinkedList list,pClientshoppingcar car, pclientRequestList change){
    pBeverageList p;
    system("cls");
    printf("  登录成功\n");
    printf("请选择功能列表\n");
    printf("1.查询存款\n");
    printf("2.查询商品\n");
    printf("3.订购\n");
    printf("4.充值\n");
    printf("5.更改密码\n");
    printf("6.查询购买记录与退换货\n");
    printf("7.注销账户\n");
    printf("8.购物车\n");
    printf("9.退出\n");
    char f=_getch();
    switch(f)
    {
    case'1':
    system("cls");
   printf("您的存款为:\n");
   printf("%f\n",a->saving);
    system("pause");
    system("cls");
   kehu(a,list,car, change);
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
   kehu(a,list,car, change);
        break;
    case'2':
        system("cls");
        showStaff(testList);
        printf("请输入品牌：\n");
        char o[20];
        gets(o);
        searchBeverageBrand(testList,o);
        system("pause");
    kehu(a,list,car, change);
        break;
    case'3':
        system("cls");
        showStaff(testList);
        printf("请输入名称：\n");
        char p[20];
        gets(p);
        searchBeverageName(testList,p);
        system("pause");
  kehu(a,list,car, change);
        break;
    case'4':
        system("cls");
        showStaff(testList);
        printf("请输入信息：\n");
        char j[20];
        gets(j);
        searchBeverageInfo(testList,j);
        system("pause");
     kehu(a,list,car, change);
        break;
    default:
        printf("输入有误，请重新输入\n");
        system("pause");
      kehu(a,list,car, change);
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
    gets(j);
    if(h>=1&&h<=b)
    {h=h+1;
    p=find(testList, h);
    printf("请选择订购数量\n");
    int nm;
    scanf_s("%d",&nm);
    char o[20]=" ";
    gets(o);
    if(nm>0&&strlen(o) == 0){
    if(a->saving>=(p->price*nm))
    {
    buy(a, p, nm);
    reduceSaving(pInfo, -p->price*nm);
    printf("订购成功\n");
    system("pause");
 kehu(a,list,car, change);
    break;}
    else
    {printf("余额不足\n");
     system("pause");
   kehu(a,list,car, change);
    break;}}
    else
        printf("请输入正确的数量\n");
       system("pause");
kehu(a,list,car, change);
    break;}
    else {
        printf("请输入正确的编号\n");
        system("pause");
     kehu(a,list,car, change);
        break;
    }
    case '4':
        system("cls");
        printf("请输入充值金额：\n");
        float g;
        char c[20];
        if(scanf_s("%f",&g)>0)
            {deposit(a, g);
            printf("充值成功\n");
            getchar();
            system("pause");
             kehu(a,list,car, change);}
        else{gets(c);
            printf("请输入正确的金额\n");
             system("pause");
            kehu(a,list,car, change);}
        break;
    case'5':
        system("cls");
        printf("请输入新密码：\n");
        char y[20];
        gets(y);
        NewPassword(a,a->account,y);
        system("pause");
       kehu(a,list,car, change);
        break;
    case'6':
        system("cls");
        searchClientBuy(a->account);
        printf("请输入查找关键词,多个关键词中间用空格分开\n");
        char s[100];
        gets(s);
        if(blank(s)== 0)
           { printf("关键词不能为空\n");
            system("pause");
            kehu(a,list,car, change);
            break;
        }
        int x=infoCheck(a,s);
        if(x==0)
        {printf("%10s%11s%10s%11s%10s%10s%10s%9s%20s\n","账号","用户名","货物品牌","货物名称","货物价格","购买数量","花费","时间","状态");
        int i=searchClientBuy(s);
           printf("总共有%d条记录\n",i);
           if(i==1)
           {
               printf("请选择是否要退货\n");
               printf("1.退货  2.不退货\n");
               char g=_getch();
               switch (g) {
               case'1':
                   printf("请输入退货原因\n");
                   char u[100];
                   gets(u);
                   clientRequest_PUSH(change,a,testList,s,u );
                   printf("退货申请已提交\n");
                   system("pause");
                  kehu(a,list,car, change);
                   break;
               case '2':
                   system("pause");
                   kehu(a,list,car, change);
                   break;
               default:
                   system("pause");
                  kehu(a,list,car, change);
                   break;
               }
           }
        system("pause");
        kehu(a,list,car, change);
        break;}
        else
        {
            system("pause");
            kehu(a,list,car, change);
            break;
        }
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
     showshoppingcar(car,a->username);
     printf("\n请选择\n");
     printf("1.添加购物车\n");
     printf("2.修改购物车\n");
     printf("3.删除购物车\n");
     printf("4.查找购物车\n");
     printf("5.购买购物车中物品\n");
     printf("6.返回\n");
     char u=_getch();
     switch (u) {
     case'1':
         system("cls");
         showStaff(testList);
         printf("请选择添加酒水序号\n");
         int k;
         scanf_s("%d",&k);
         char b=getchar();
         k++;
         pBeverageNode p0=find(testList, k);
         printf("请选择添加数量\n");
         int r;
         scanf_s("%d",&r);
         b=getchar();
         addshoppingcar(car,a,p0,r);
         printf("添加成功\n");
         showshoppingcar(car,a->username);
         system("pause");
          kehu(a,list,car, change);
         break;
   case '2':
         system("cls");
         showshoppingcar(car,a->username);
         printf("请选择要修改的序号\n");
         int j;
         scanf_s("%d",&j);
         char c=getchar();
         j++;
         if(j>getNum(car))
         {
             printf("请输入正确的编号\n");
             system("pause");
            kehu(a,list,car, change);
            break;
         }
         else{
         pClientshoppingcar p1= finding(car, j);
         printf("请输入要修改的数量\n");
         int y;
         scanf_s("%d",&y);
         c=getchar();
         changeshoppingcar(car,p1->name,y );
         printf("修改成功\n");
         showshoppingcar(car,a->username);
         system("pause");
        kehu(a,list,car, change);
        break;}
    case '3':
         system("cls");
         int status;
         showshoppingcar(car,a->username);
         printf("请选择要删除的序号\n");
         int h;
         scanf_s("%d",&h);
         char d=getchar();
         h++;
         if(h>getNum(car))
         {
             printf("请输入正确的编号\n");
             system("pause");
            kehu(a,list,car, change);
            break;
         }
         else{
         pClientshoppingcar p2=finding(car,h);
         car=deleteshoppingcar(car,p2->name,&status);
         printf("删除成功\n");
         showshoppingcar(car,a->username);
         system("pause");
         kehu(a,list,car, change);
         break;}
   case '4':
         system("cls");
         showshoppingcar(car,a->username);
         printf("请输入要查找的名称\n");
         char ch=getchar();
         char w[20];
         gets(w);
         searchshoppingcar(car, w);
         system("pause");
         kehu(a,list,car, change);
         break;
   case'5':
         system("cls");
         showshoppingcar(car,a->username);
         printf("请输入要购买的编号\n");
         int p;
         scanf_s("%d",&p);
         char de=getchar();
         p++;
         if(p>getNum(car))
         {
             printf("请输入正确的编号\n");
             system("pause");
            kehu(a,list,car, change);
            break;
         }
         else{
         pClientshoppingcar p3=finding(car, p);
         pBeverageNode p4=findname(testList, p3->name);
         if(a->saving>=(p3->cost))
         {buy(a,p4,p3->amount);
          reduceSaving(pInfo, p3->cost);
             deleteshoppingcar(car,p3->name,&status);
             printf("购买成功\n");
         system("pause");
      kehu(a,list,car, change);
         break;}
         else
         {printf("余额不足\n");
          system("pause");
        kehu(a,list,car, change);
         break;}}

   case'6':
         system("cls");
         kehu(a,list,car, change);
         break;
     default:
         printf("输入有误，请重新输入\n");
         system("pause");
         system("cls");
      kehu(a,list,car, change);
         break;

     }

        break;
    case'9':
         system("cls");
        break;
    default:
    printf("输入有误，请重新输入\n");
    system("pause");
    system("cls");
 kehu(a,list,car, change);
    break;
    }return 0;
}

int shanghu(pclientRequestList change){
    system("cls");
printf("请选择功能列表\n");
  printf("1.进货\n");
  printf("2.查询库存\n");
  printf("3.商品排序\n");
  printf("4.删除库存\n");
  printf("5.修改商品信息\n");
  printf("6.审核退货申请\n");
  printf("7.初始化库存\n");
  printf("8.设定资金\n");
  printf("9.查询资金\n");
  printf("0.返回\n");
  char d =_getch();
  switch(d)

  {case'1':
  {system("cls");
      if (pInfo == NULL) {
          printf("请先设定资金！\n");
          system("pause");
          shanghu(change);
          break;
      }
      printf("请选择进货方式\n");
      printf("1.手动输入进货信息\n");
      printf("2.从文件读入进货信息\n");
      char j=_getch();
      switch (j) {
      case'1':
      system("cls");
      printf("请输入品牌\n");
      char fe[20];
      gets(fe);
      printf("请输入商品名\n");
      char fd[20];
      gets(fd);
      printf("请输入进货时间\n");
      char fg[20];
      gets(fg);
      printf("请输入商品数量\n");
      int k;
      scanf_s("%d",&k);
      printf("请输入商品价格\n");
      int l;
      scanf_s("%d",&l);
      char ch=getchar();
      printf("请输入商品信息\n");
      char fs[20];
      gets(fs);
      pBeverageList newNode=newBeverageNode(fe, fd, fg, k, l, fs, pInfo);
      insertLast(testList, newNode);
       printf("进货成功");

          break;
      case'2':
          system("cls");
          printf("请输入文件地址\n");
          char u[100];
          gets(u);
          if (testList) addFromFile(u, testList, pInfo);
          else testList = createFromFile(u, pInfo);
          printf("进货成功");
          break;
      default:printf("输入错误，请重新输入\n");
          system("pause");
          shanghu(change);
          break;}
      showStaff(testList);
      system("pause");
      system("cls");
     shanghu(change);
      break;}
  case'2':
  {system("cls");
      showStaff(testList);
      system("pause");
      system("cls");
     shanghu(change);
      break;}
  case'3':
  {system("cls");
      if (testList == NULL) {
          printf("请先初始化库存！\n");
          system("pause");
          shanghu(change);
          break;
      }
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
             shanghu(change);
              break;
          case'2':
              testList = sortBeverageTime(testList, -1);
              showStaff(testList);
              system("pause");
              system("cls");
             shanghu(change);
              break;
          default:
              printf("输入有误");
              system("pause");
              system("cls");
            shanghu(change);
              break;
          }
          system("pause");
           shanghu(change);
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
             shanghu(change);
              break;
          case'2':
              testList = sortBeverageBrand(testList, -1);
              showStaff(testList);
              system("pause");
              system("cls");
           shanghu(change);
              break;
          default:
              printf("输入有误");
              system("pause");
              system("cls");
           shanghu(change);
              break;
          }
          system("pause");
         shanghu(change);
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
              shanghu(change);
              break;
          case'2':
              testList = sortBeverageStoreNum(testList, -1);
              showStaff(testList);
              system("pause");
              system("cls");
               shanghu(change);
              break;
          default:
              printf("输入有误");
              system("pause");
              system("cls");
            shanghu(change);
              break;
          }
          system("pause");
          shanghu(change);
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
             shanghu(change);
              break;
          case'2':
              testList = sortBeveragePrice(testList, -1);
              showStaff(testList);
              system("pause");
              system("cls");
              shanghu(change);
              break;
          default:
              printf("输入有误");
              system("pause");
              system("cls");
             shanghu(change);
              break;
          }
          system("pause");
        shanghu(change);
          break;
      }
      system("pause");

     shanghu(change);
      break;
  }
  case'4':
  {system("cls");
      if (testList == NULL) {
          printf("请先初始化库存！\n");
          system("pause");
          shanghu(change);
          break;
      }
      if (isEmpty(testList)) {
          printf("库存为空！\n");
          system("pause");
          shanghu(change);
          break;
      }
      showStaff(testList);
      printf("请输入删除的产品编号\n");
      int bh ;
      scanf_s("%d",&bh);
      getchar();
      printf("%d", bh);
      deleteBeverage(testList, bh);
      printf("成功删除\n");
      system("cls");
      showStaff(testList);
      system("pause");
      shanghu(change);
      break;}
  case'5':
  {system("cls");
      if (testList == NULL) {
          printf("请先初始化库存！\n");
          system("pause");
          shanghu(change);
          break;
      }
      showStaff(testList);
      printf("请输入产品编号\n");
      int bi=_getch()-'0';
      if(bi>getLinkTotalNodeNum(testList))
      {
          printf("请输入正确的编号\n");
          system("pause");
          shanghu(change);
         break;
      }
      else{
      printf("请输入产品信息\n");
      char ke[20];
      gets(ke);
      changeBeverageInfo(testList, bi, ke);
      printf("修改成功\n");
      system("pause");
       shanghu(change);
      break;}}
   case'6':
      system("cls");
      int u=clientRequest_SHOW(change);
      if(u==0)
      {
          printf("当前无退货申请\n");
          system("pause");
           shanghu(change);
          break;
      }
      else{
      printf("请选择要操作的条目：\n");
      int v;
      scanf_s("%d",&v);
      getchar();
      printf("该条目退货原因为：\n");
      clientRequest_SHOWMORE(change,v);
      printf("请选择是否批准退货\n");
      printf("1.批准  2.不批准\n");
      int y;
      scanf_s("%d",&y);
      getchar();
      clientRequest_POP(change,v,y, pInfo);
      printf("操作成功\n");
      system("pause");
      shanghu(change);
      break;}
  case'7':
      system("cls");
      if (pInfo == NULL) {
          printf("请先设定资金！\n");
          system("pause");
          shanghu(change);
          break;
      }
      printf("请输入初始化库存地址\n");
      char o[50];
      gets(o);
      testList= createFromFile(o, pInfo);
      printf("初始化成功\n");
      system("pause");
      shanghu(change);
      break;
  case'8':
      system("cls");
      printf("请输入资金：\n");
      float g;
      char c[20];
      if(scanf_s("%f",&g)>0)
          {pInfo = initInteractInfo(g);
          printf("充值成功\n");
          getchar();
          system("pause");
           shanghu(change);}
      else{gets(c);
          printf("请输入正确的金额\n");
           system("pause");
          shanghu(change);}
      break;
  case'9':
        system("cls");
        if (pInfo) {
            showInfoSaving(pInfo);
        } else {
            printf("请先设定起始资金!\n");
        }
        system("pause");
        shanghu(change);
  case'0':
      break;
  default:
      printf("输入有误，请重新输入\n");
      system("pause");
      system("cls");
       shanghu(change);
      break;}
  return 0;
      }

int denglu(pClientLinkedList list , pClientshoppingcar car, pclientRequestList change){
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
  gets(zh);
  printf("请输入密码\n");
  char mi[20];
  gets(mi);
 p=signIn(list, zh, mi, &status);
 switch (status) {
 case 1:
 kehu(p, list,car, change);
    break;
 case 0:
     system("pause");
     break;
 case 4:
  shanghu(change);
  break;
 case -1:
    system("pause");
     break;
 }
     break;}
  case'2':
  {system("cls");
    if (testList == NULL || pInfo == NULL) {
        printf("当前商户尚未开张！\n请先完成库存和资金的初始化!\n");
        system("pause");
        break;
    }
  printf("请输入用户名\n");
  char yh[20];
  gets(yh);
  if(strlen(yh)==0)
     { printf("用户名不能为空\n");
      system("pause");
      break;}
  printf("请输入账号\n");
  char hz[20];
  gets(hz);
  if(strlen(hz)==0)
     { printf("账号不能为空\n");
      system("pause");
      break;}
  printf("请输入密码\n");
  char im[20];
  gets(im);
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
      denglu(list, car,change);
      break;
  }return 0;
}

int main()
{
    beverageRecordInit();
    pclientRequestList change=clientRequestListInit();
pClientshoppingcar car= initshoppingcar();
   recordInit();
  pClientLinkedList list=initClient();
  signUp(list, "111", "111", "shanghu",0,0,-1);
 while(1)
{system("cls");
 printf("欢迎进入酒水管理系统\n");
 system("pause");
 system("cls");
 denglu(list, car,change);

}
    return 0;
}
