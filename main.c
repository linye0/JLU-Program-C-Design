#include <string.h>
#include "merchantAndClient.h"
#include<time.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

int kehu(pClientLinkedList a,pBeverageList testList,pClientLinkedList list){
    pBeverageList p;
    system("cls");
    printf("  ��¼�ɹ�\n");
    printf("��ѡ�����б�\n");
    printf("1.��ѯ���\n");
    printf("2.��ѯ��Ʒ\n");
    printf("3.����\n");
    printf("4.��ֵ\n");
    printf("5.�����û���������\n");
    printf("6.��ѯ�����¼\n");
    printf("7.ע���˻�\n");
    printf("8.�˳�\n");
    char f=_getch();
    switch(f)
    {
    case'1':
    system("cls");
   printf("���Ĵ��Ϊ:\n");
   printf("%d\n",a->saving);
    system("pause");
    system("cls");
    kehu(a,testList,list);
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
      kehu(a,testList,list);
        break;
    case'2':
        system("cls");
        showStaff(testList);
        printf("������Ʒ�ƣ�\n");
        char o[20];
        gets_s(o,19);
        searchBeverageBrand(testList,o);
        system("pause");
     kehu(a,testList,list);
        break;
    case'3':
        system("cls");
        showStaff(testList);
        printf("���������ƣ�\n");
        char p[20];
        gets_s(p,19);
        searchBeverageName(testList,p);
        system("pause");
     kehu(a,testList,list);
        break;
    case'4':
        system("cls");
        showStaff(testList);
        printf("��������Ϣ��\n");
        char j[20];
        gets_s(j,19);
        searchBeverageInfo(testList,j);
        system("pause");
       kehu(a,testList,list);
        break;
    default:
        printf("������������������\n");
        system("pause");
       kehu(a,testList,list);
        break;
    }
    break;
    case'3':
    system("cls");
    showStaff(testList);
    printf("��ѡ���ˮ���\n");
    int h;
    scanf_s("%d",&h);
    h=h+1;
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
    system("pause");}
    else
    {printf("����\n");
     system("pause");}}
    else
        printf("��������ȷ������\n");
       system("pause");
  kehu(a,testList,list);
    break;
    case '4':
        system("cls");
        printf("�������ֵ��\n");
        int g;
        char c[20];
        if(scanf_s("%d",&g)>0)
            {deposit(a, g);
            printf("��ֵ�ɹ�\n");
            system("pause");
            kehu(a,testList,list);}
        else{gets_s(c,19);
            printf("��������ȷ�Ľ��\n");
             system("pause");
            kehu(a,testList,list);}
        break;
    case'5':
        system("cls");
        printf("�����������룺\n");
        char y[20];
        gets_s(y,19);
        NewPassword(a,a->account,y);
        system("pause");
       kehu(a,testList,list);
        break;
    case'6':
        system("cls");
        printf("%10s%11s%10s%11s%10s%10s%9s\n","�˺�","�û���","����Ʒ��","��������","����۸�","��������","ʱ��");
        int i=searchClientBuy(a->account);
           printf("�ܹ���%d����¼\n",i);
        system("pause");
        kehu(a,testList,list);
        break;
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
        break;
    default:
    printf("������������������\n");
    system("pause");
    system("cls");
  kehu(a,testList,list);
    break;
    }return 0;
}
int denglu(pClientLinkedList list ,pBeverageList testList){
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
    kehu(p,testList,list);
    break;
 case 0:
     system("pause");
  denglu(list,testList);
     break;
 case 4:
  shanghu(testList);
  break;
 case -1:
    system("pause");
   denglu(list,testList);
     break;
 }
     break;}
  case'2':
  {system("cls");

  printf("�������û���\n");
  char yh[20];
  gets_s(yh,19);
  printf("�������˺�\n");
  char hz[20];
  gets_s(hz,19);
  printf("����������\n");
  char im[20];
  gets_s(im,19);
  signUp(list, hz, im, yh,0,0,1);
  printf("ע��ɹ�");
  system("pause");
  system("cls");
      break;}
  default:
      printf("������������������\n");
      system("pause");
      system("cls");
      denglu(list,testList);
      break;
  }return 0;
}
int shanghu(pBeverageList testList){
    system("cls");
printf("��ѡ�����б�\n");
  printf("1.����\n");
  printf("2.��ѯ���\n");
  printf("3.��Ʒ����\n");
  printf("4.ɾ�����\n");
  printf("5.�޸���Ʒ��Ϣ\n");
  printf("6.����\n");
  char d =_getch();
  switch(d)

  {case'1':
  {system("cls");
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
      printf("��������Ʒ��Ϣ\n");
      char fs[20];
      gets_s(fs,19);
       newBeverageNode(fe, fd, fg, k, l, fs);
       printf("�����ɹ�");
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
              printf("��������");
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
              printf("��������");
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
              printf("��������");
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
              printf("��������");
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
      printf("������ɾ���Ĳ�Ʒ���\n");
      int bh ;
      scanf_s("%d",&bh);
      printf("%d", bh);
      deleteBeverage(testList, bh);
      printf("�ɹ�ɾ��\n");
      system("cls");
      showStaff(testList);
      system("pause");
      shanghu(testList);
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
      shanghu(testList);
      break;}
  case'6':
  {system("cls");
      break;}
  default:
      printf("������������������\n");
      system("pause");
      system("cls");
      shanghu(testList);
      break;}return 0;
      }
int main()
{
   init();
  pBeverageList testList = createFromFile("C:\\Users\\86188\\Desktop\\test.txt");
   recordInit();
  pClientLinkedList list=initClient();
  signUp(list, "111", "111", "shanghu",0,0,-1);
 while(1)
{system("cls");
 printf("��ӭ�����ˮ����ϵͳ\n");
 system("pause");
 system("cls");
 denglu(list,testList);

}
    return 0;
}

