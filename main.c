#include <string.h>
#include "merchantAndClient.h"
#include<time.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

int kehu(pClientLinkedList a,pBeverageList testList,pClientLinkedList list,pClientshoppingcar car, pclientRequestList change){
    pBeverageList p;
    system("cls");
    printf("  ��¼�ɹ�\n");
    printf("��ѡ�����б�\n");
    printf("1.��ѯ���\n");
    printf("2.��ѯ��Ʒ\n");
    printf("3.����\n");
    printf("4.��ֵ\n");
    printf("5.�����û���������\n");
    printf("6.��ѯ�����¼���˻���\n");
    printf("7.ע���˻�\n");
    printf("8.���ﳵ\n");
    printf("9.�˳�\n");
    char f=_getch();
    switch(f)
    {
    case'1':
    system("cls");
   printf("���Ĵ��Ϊ:\n");
   printf("%f\n",a->saving);
    system("pause");
    system("cls");
    kehu(a,testList,list,car, change);
    break;
    case'2':
    system("cls");
    printf("��ѡ��\n");
    printf("1���鿴������Ʒ\n");
    printf("2������Ʒ�Ʋ�����Ʒ\n");
    printf("3������������Ʒ\n");
    printf("4�����ݾ�ˮ��Ϣ������Ʒ\n");
    char m=_getch();
    switch(m){
    case'1':
        system("cls");
        showStaff(testList);
        system("pause");
      kehu(a,testList,list,car, change);
        break;
    case'2':
        system("cls");
        showStaff(testList);
        printf("������Ʒ�ƣ�\n");
        char o[20];
        gets_s(o,19);
        searchBeverageBrand(testList,o);
        system("pause");
     kehu(a,testList,list,car, change);
        break;
    case'3':
        system("cls");
        showStaff(testList);
        printf("���������ƣ�\n");
        char p[20];
        gets_s(p,19);
        searchBeverageName(testList,p);
        system("pause");
   kehu(a,testList,list,car, change);
        break;
    case'4':
        system("cls");
        showStaff(testList);
        printf("��������Ϣ��\n");
        char j[20];
        gets_s(j,19);
        searchBeverageInfo(testList,j);
        system("pause");
      kehu(a,testList,list,car, change);
        break;
    default:
        printf("������������������\n");
        system("pause");
      kehu(a,testList,list,car, change);
        break;
    }
    break;
    case'3':
    system("cls");
    showStaff(testList);
    printf("��ѡ���ˮ���\n");
    int h;
    scanf_s("%d",&h);
    int b=getLinkTotalNodeNum(testList);
    b=b-1;
    char j[20];
    gets_s(j,19);
    if(h>=1&&h<=b)
    {h=h+1;
    p=find(testList, h);
    printf("��ѡ�񶩹�����\n");
    int nm;
    scanf_s("%d",&nm);
    char o[20]=" ";
    gets_s(o,19);
    if(nm>0&&strlen(o) == 0){
    if(a->saving>=(p->price*nm))
    {
    buy(a, p, nm);
    printf("�����ɹ�\n");
    system("pause");
 kehu(a,testList,list,car, change);
    break;}
    else
    {printf("����\n");
     system("pause");
   kehu(a,testList,list,car, change);
    break;}}
    else
        printf("��������ȷ������\n");
       system("pause");
 kehu(a,testList,list,car, change);
    break;}
    else {
        printf("��������ȷ�ı��\n");
        system("pause");
      kehu(a,testList,list,car, change);
        break;
    }
    case '4':
        system("cls");
        printf("�������ֵ��\n");
        float g;
        char c[20];
        if(scanf_s("%f",&g)>0)
            {deposit(a, g);
            printf("��ֵ�ɹ�\n");
            system("pause");
             kehu(a,testList,list,car, change);}
        else{gets_s(c,19);
            printf("��������ȷ�Ľ��\n");
             system("pause");
             kehu(a,testList,list,car, change);}
        break;
    case'5':
        system("cls");
        printf("�����������룺\n");
        char y[20];
        gets_s(y,19);
        NewPassword(a,a->account,y);
        system("pause");
        kehu(a,testList,list,car, change);
        break;
    case'6':
        system("cls");
        searchClientBuy(a->account);
        printf("��������ҹؼ���,����ؼ����м��ÿո�ֿ�\n");
        char s[100];
        gets_s(s,19);
        int x=infoCheck(a,s);
        if(x==0)
        {printf("%10s%11s%10s%11s%10s%10s%10s%9s%20s\n","�˺�","�û���","����Ʒ��","��������","����۸�","��������","����","ʱ��","״̬");
        int i=searchClientBuy(s);
           printf("�ܹ���%d����¼\n",i);
           if(i==1)
           {
               printf("��ѡ���Ƿ�Ҫ�˻�\n");
               printf("1.�˻�  2.���˻�\n");
               char g=_getch();
               switch (g) {
               case'1':
                   printf("�������˻�ԭ��\n");
                   char u[100];
                   gets_s(u,39);
                   clientRequest_PUSH(change,a,testList,s,u );
                   printf("�˻��������ύ\n");
                   system("pause");
                   kehu(a,testList,list,car, change);
                   break;
               case '2':
                   system("pause");
                   kehu(a,testList,list,car, change);
                   break;
               default:
                   system("pause");
                   kehu(a,testList,list,car, change);
                   break;
               }
           }
        system("pause");
        kehu(a,testList,list,car, change);
        break;}
        else
        {
            system("pause");
            kehu(a,testList,list,car, change);
            break;
        }
    case'7':
        system("cls");
        int status;
        clientLogout(list,a->account,&status);
        if(status==0)
            printf("ɾ���ɹ�\n");
        else
            printf("ɾ��ʧ�ܣ�������\n");
        system("pause");
        break;
    case'8':
        system("cls");
     showshoppingcar(car,a->username);
     printf("\n��ѡ��\n");
     printf("1.��ӹ��ﳵ\n");
     printf("2.�޸Ĺ��ﳵ\n");
     printf("3.ɾ�����ﳵ\n");
     printf("4.���ҹ��ﳵ\n");
     printf("5.�����ﳵ����Ʒ\n");
     printf("6.����\n");
     char u=_getch();
     switch (u) {
     case'1':
         system("cls");
         showStaff(testList);
         printf("��ѡ����Ӿ�ˮ���\n");
         int k;
         scanf_s("%d",&k);
         char b=getchar();
         k++;
         pBeverageNode p0=find(testList, k);
         printf("��ѡ���������\n");
         int r;
         scanf_s("%d",&r);
         b=getchar();
         addshoppingcar(car,a,p0,r);
         printf("��ӳɹ�\n");
         showshoppingcar(car,a->username);
         system("pause");
          kehu(a,testList,list,car, change);
         break;
   case '2':
         system("cls");
         showshoppingcar(car,a->username);
         printf("��ѡ��Ҫ�޸ĵ����\n");
         int j;
         scanf_s("%d",&j);
         char c=getchar();
         j++;
         pClientshoppingcar p1= finding(car, j);
         printf("������Ҫ�޸ĵ�����\n");
         int y;
         scanf_s("%d",&y);
         c=getchar();
         changeshoppingcar(car,p1->name,y );
         printf("�޸ĳɹ�\n");
         showshoppingcar(car,a->username);
         system("pause");
         kehu(a,testList,list,car, change);
        break;
    case '3':
         system("cls");
         int status;
         showshoppingcar(car,a->username);
         printf("��ѡ��Ҫɾ�������\n");
         int h;
         scanf_s("%d",&h);
         char d=getchar();
         h++;
         pClientshoppingcar p2=finding(car,h);
         car=deleteshoppingcar(car,p2->name,&status);
         printf("ɾ���ɹ�\n");
         showshoppingcar(car,a->username);
         system("pause");
         kehu(a,testList,list,car, change);
         break;
   case '4':
         system("cls");
         showshoppingcar(car,a->username);
         printf("������Ҫ���ҵ�����\n");
         char ch=getchar();
         char w[20];
         gets_s(w,19);
         searchshoppingcar(car, w);
         system("pause");
           kehu(a,testList,list,car, change);
         break;
   case'5':
         system("cls");
         showshoppingcar(car,a->username);
         printf("������Ҫ����ı��\n");
         int p;
         scanf_s("%d",&p);
         char de=getchar();
         p++;
         pClientshoppingcar p3=finding(car, p);
         pBeverageNode p4=findname(testList, p3->name);
         if(a->saving>=(p3->cost))
         {buy(a,p4,p3->amount);
             deleteshoppingcar(car,p3->name,&status);
             printf("����ɹ�\n");
         system("pause");
      kehu(a,testList,list,car, change);
         break;}
         else
         {printf("����\n");
          system("pause");
        kehu(a,testList,list,car, change);
         break;}

   case'6':
         system("cls");
          kehu(a,testList,list,car, change);
         break;
     default:
         printf("������������������\n");
         system("pause");
         system("cls");
      kehu(a,testList,list,car, change);
         break;

     }

        break;
    case'9':
         system("cls");
        break;
    default:
    printf("������������������\n");
    system("pause");
    system("cls");
 kehu(a,testList,list,car, change);
    break;
    }return 0;
}

int shanghu(pBeverageList testList,pclientRequestList change){
    system("cls");
printf("��ѡ�����б�\n");
  printf("1.����\n");
  printf("2.��ѯ���\n");
  printf("3.��Ʒ����\n");
  printf("4.ɾ�����\n");
  printf("5.�޸���Ʒ��Ϣ\n");
  printf("6.����˻�����\n");
  printf("7.����\n");
  char d =_getch();
  switch(d)

  {case'1':
  {system("cls");
      printf("��ѡ�������ʽ\n");
      printf("1.�ֶ����������Ϣ\n");
      printf("2.���ļ����������Ϣ\n");
      char j=_getch();
      switch (j) {
      case'1':
      system("cls");
      printf("������Ʒ��\n");
      char fe[20];
      gets_s(fe,19);
      printf("��������Ʒ��\n");
      char fd[20];
      gets_s(fd,19);
      printf("���������ʱ��\n");
      char fg[20];
      gets_s(fg,19);
      printf("��������Ʒ����\n");
      int k;
      scanf_s("%d",&k);
      printf("��������Ʒ�۸�\n");
      int l;
      scanf_s("%d",&l);
      char ch=getchar();
      printf("��������Ʒ��Ϣ\n");
      char fs[20];
      gets_s(fs,19);
      pBeverageList newNode=newBeverageNode(fe, fd, fg, k, l, fs);
      insertLast(testList, newNode);
       printf("�����ɹ�");
          break;
      case'2':
          system("cls");
          printf("�������ļ���ַ\n");
          char u[50];
          gets_s(u,49);
          addFromFile(u, testList);
          printf("�����ɹ�");
          break;
      default:printf("�����������������\n");
          break;}
      showStaff(testList);
      system("pause");
      system("cls");
     shanghu(testList,change);
      break;}
  case'2':
  {system("cls");
      showStaff(testList);
      system("pause");
      system("cls");
     shanghu(testList,change);
      break;}
  case'3':
  {system("cls");
      system("cls");
      printf("��ѡ��\n");
      printf("1���Ծ�ˮ�Խ���ʱ��Ϊ�ؼ��ʽ�������\n");
      printf("2���Ծ�ˮ��Ʒ��Ϊ�ؼ��ʽ�������\n");
      printf("3���Ծ�ˮ�Կ����Ϊ�ؼ��ʽ�������\n");
      printf("4���Ծ�ˮ�Լ۸�Ϊ�ؼ��ʽ�������\n");
      char m=_getch();
      switch(m){
      case'1':
          system("cls");
          printf("��ѡ������ʽ��\n");
          printf("1������\n");
          printf("2������\n");
          char l=_getch();
          switch (l) {
          case'1':
              testList = sortBeverageTime(testList, 1);
              showStaff(testList);
              system("pause");
              system("cls");
             shanghu(testList,change);
              break;
          case'2':
              testList = sortBeverageTime(testList, -1);
              showStaff(testList);
              system("pause");
              system("cls");
             shanghu(testList,change);
              break;
          default:
              printf("��������");
              system("pause");
              system("cls");
            shanghu(testList,change);
              break;
          }
          system("pause");
          shanghu(testList,change);
          break;
      case'2':
          system("cls");
          printf("��ѡ������ʽ��\n");
          printf("1������\n");
          printf("2������\n");
          char r=_getch();
          switch (r) {
          case'1':
              testList = sortBeverageBrand(testList, 1);
              showStaff(testList);
              system("pause");
              system("cls");
             shanghu(testList,change);
              break;
          case'2':
              testList = sortBeverageBrand(testList, -1);
              showStaff(testList);
              system("pause");
              system("cls");
           shanghu(testList,change);
              break;
          default:
              printf("��������");
              system("pause");
              system("cls");
          shanghu(testList,change);
              break;
          }
          system("pause");
         shanghu(testList,change);
          break;
      case'3':
          system("cls");
          printf("��ѡ������ʽ��\n");
          printf("1������\n");
          printf("2������\n");
          char t=_getch();
          switch (t) {
          case'1':
              testList = sortBeverageStoreNum(testList, 1);
              showStaff(testList);
              system("pause");
              system("cls");
             shanghu(testList,change);
              break;
          case'2':
              testList = sortBeverageStoreNum(testList, -1);
              showStaff(testList);
              system("pause");
              system("cls");
              shanghu(testList,change);
              break;
          default:
              printf("��������");
              system("pause");
              system("cls");
            shanghu(testList,change);
              break;
          }
          system("pause");
          shanghu(testList,change);
          break;
      case'4':
          system("cls");
          printf("��ѡ������ʽ��\n");
          printf("1������\n");
          printf("2������\n");
          char y=_getch();
          switch (y) {
          case'1':
              testList = sortBeveragePrice(testList, 1);
              showStaff(testList);
              system("pause");
              system("cls");
            shanghu(testList,change);
              break;
          case'2':
              testList = sortBeveragePrice(testList, -1);
              showStaff(testList);
              system("pause");
              system("cls");
             shanghu(testList,change);
              break;
          default:
              printf("��������");
              system("pause");
              system("cls");
            shanghu(testList,change);
              break;
          }
          system("pause");
        shanghu(testList,change);
          break;
      }
      system("pause");

    shanghu(testList,change);
      break;
  }
  case'4':
  {system("cls");
      showStaff(testList);
      printf("������ɾ���Ĳ�Ʒ���\n");
      int bh ;
      scanf_s("%d",&bh);
      printf("%d", bh);
      deleteBeverage(testList, bh);
      printf("�ɹ�ɾ��\n");
      system("cls");
      showStaff(testList);
      system("pause");
     shanghu(testList,change);
      break;}
  case'5':
  {system("cls");
      showStaff(testList);
      printf("�������Ʒ���\n");
      int bi=_getch()-'0';
      printf("�������Ʒ��Ϣ\n");
      char ke[20];
      gets_s(ke,19);
      changeBeverageInfo(testList, bi, ke);
      printf("�޸ĳɹ�\n");
      system("pause");
      shanghu(testList,change);
      break;}
   case'6':
      system("cls");
      int u=clientRequest_SHOW(change);
      if(u==0)
      {
          printf("��ǰ���˻�����\n");
          system("pause");
          shanghu(testList,change);
          break;
      }
      else{
      printf("��ѡ��Ҫ��������Ŀ��\n");
      int v;
      scanf_s("%d",&v);
      printf("����Ŀ�˻�ԭ��Ϊ��\n");
      clientRequest_SHOWMORE(change,v);
      printf("��ѡ���Ƿ���׼�˻�\n");
      printf("1.��׼  2.����׼\n");
      int y;
      scanf_s("%d",&y);
      clientRequest_POP(change,v,y);
      printf("�����ɹ�\n");
      system("pause");
      shanghu(testList,change);
      break;}
  case'7':
  {system("cls");
      break;}
  default:
      printf("������������������\n");
      system("pause");
      system("cls");
      shanghu(testList,change);
      break;}return 0;
      }

int denglu(pClientLinkedList list ,pBeverageList testList,pClientshoppingcar car, pclientRequestList change){
    pClientLinkedList p;
    int status;
    system("cls");
  printf("     ��ѡ��\n");
  printf("1.��¼     2.ע��\n");
  char c=_getch();
  switch(c)
  {
  case'1':
  {system("cls");
  printf("�������˺�\n");
  char zh[20];
  gets_s(zh,19);
  printf("����������\n");
  char mi[20];
  gets_s(mi,19);
 p=signIn(list, zh, mi, &status);
 switch (status) {
 case 1:
 kehu(p,testList,list,car, change);
    break;
 case 0:
     system("pause");
     break;
 case 4:
  shanghu(testList,change);
  break;
 case -1:
    system("pause");
     break;
 }
     break;}
  case'2':
  {system("cls");

  printf("�������û���\n");
  char yh[20];
  gets_s(yh,19);
  if(strlen(yh)==0)
     { printf("�û�������Ϊ��\n");
      system("pause");
      break;}
  printf("�������˺�\n");
  char hz[20];
  gets_s(hz,19);
  if(strlen(hz)==0)
     { printf("�˺Ų���Ϊ��\n");
      system("pause");
      break;}
  printf("����������\n");
  char im[20];
  gets_s(im,19);
  if(strlen(im)==0)
     { printf("���벻��Ϊ��\n");
      system("pause");
      break;}
  signUp(list, hz, im, yh,0,0,1);
  printf("ע��ɹ�");
  system("pause");
  system("cls");
      break;}
  default:
      printf("������������������\n");
      system("pause");
      system("cls");
      denglu(list,testList,car,change);
      break;
  }return 0;
}

int main()
{
    pclientRequestList change=clientRequestListInit();
pClientshoppingcar car= initshoppingcar();
  pBeverageList testList = createFromFile("D:\\qt\\qt project\\1\\beverage.txt");
   recordInit();
  pClientLinkedList list=initClient();
  signUp(list, "111", "111", "shanghu",0,0,-1);
 while(1)
{system("cls");
 printf("��ӭ�����ˮ����ϵͳ\n");
 system("pause");
 system("cls");
 denglu(list,testList,car,change);

}
    return 0;
}

