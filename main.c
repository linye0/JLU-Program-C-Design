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
    printf("  ��¼�ɹ�\n");
    printf("��ѡ�����б�\n");
    printf("1.��ѯ�û�������Ϣ\n");
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
    printCLientInfo(a);//��������ͻ���Ϣ
    system("pause");
    system("cls");
   kehu(a,list,car, change);
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
   kehu(a,list,car, change);
        break;
    case'2':
        system("cls");
        showStaff(testList);
        printf("������Ʒ�ƣ�\n");
        char o[20];
        gets(o);
        searchBeverageBrand(testList,o);
        system("pause");
    kehu(a,list,car, change);
        break;
    case'3':
        system("cls");
        showStaff(testList);
        printf("���������ƣ�\n");
        char p[20];
        gets(p);

        searchBeverageName(testList,p);
        system("pause");
  kehu(a,list,car, change);
        break;
    case'4':
        system("cls");
        showStaff(testList);
        printf("��������Ϣ��\n");
        char j[20];
        gets(j);
        searchBeverageInfo(testList,j);
        system("pause");
     kehu(a,list,car, change);
        break;
    default:
        printf("������������������\n");
        system("pause");
      kehu(a,list,car, change);
        break;
    }
    break;
    case'3':
    system("cls");
    showStaff(testList);
    printf("��ѡ���ˮ���\n");
    int h = 0;
    scanf("%d",&h);
    if (h < 0) {
        printf("��������ȷ������!\n");
        system("pause");
        break;
    }
    int b=getLinkTotalNodeNum(testList);
    b=b-1;
    char j[20];
    gets(j);
    if(h>=1&&h<=b)
    {h=h+1;
    p=find(testList, h);
    printf("��ѡ�񶩹�����\n");
    int nm;
    scanf("%d",&nm);
    if (nm < 0) {
        printf("��������ȷ������!\n");
        system("pause");
        break;
    }
    char o[20]=" ";
    gets(o);
    if(nm>0&&strlen(o) == 0){
    if(a->saving>=(p->price*nm))
    {
    int k=buy(a, p, nm);
    if(k<0){
        printf("��Ǹ����治������\n");
        system("pause");
    }else{
    reduceSaving(pInfo, -p->price*nm);
    printf("�����ɹ�\n");
    system("pause");
    }
 kehu(a,list,car, change);
    break;}
    else
    {printf("����\n");
     system("pause");
   kehu(a,list,car, change);
    break;}}
    else
        printf("��������ȷ������\n");
       system("pause");
kehu(a,list,car, change);
    break;}
    else {
        printf("��������ȷ�ı��\n");
        system("pause");
     kehu(a,list,car, change);
        break;
    }
    case '4':
        system("cls");
        printf("�������ֵ��\n");
        float g;
        char c[20];
        if(scanf("%f",&g)>0)
        {
            if (g < 0) {
                printf("��������ȷ������!\n");
                system("pause");
                break;
            }
        getchar();
            deposit(a, g);
            printf("��ֵ�ɹ�\n");
            system("pause");
             kehu(a,list,car, change);}
        else{gets(c);
            printf("��������ȷ�Ľ��\n");
             system("pause");
            kehu(a,list,car, change);}
        break;
    case'5':
        system("cls");
        printf("��ѡ��ʵ�ֵĹ��ܣ�\n");
        printf("1.����û���\n");
        printf("2.�������\n");
        char k=_getch();
        system("cls");
        switch(k){
        case '1':
            printf("���������û�����\n");
            char z[20];
            gets(z);
            changeUsername(a,a->username,z);
            printf("�ѳɹ������û���\n");
            system("pause");
            kehu(a,list,car, change);
            break;
        case '2':
            printf("�����������룺\n");
            char y[20];
            gets(y);
            NewPassword(a,a->account,y);
            printf("�ѳɹ���������\n");
            system("pause");
            kehu(a,list,car, change);
            break;
        default:
            system("pause");
           kehu(a,list,car, change);
            break;
        }


        system("pause");
       kehu(a,list,car, change);
        break;
    case'6':
        system("cls");
        printf("%10s%11s%10s%11s%10s%10s%10s%9s%20s\n","�˺�","�û���","����Ʒ��","��������","����۸�","��������","����","ʱ��","״̬");
        searchClientBuy(a->account);
        printf("��������ҹؼ���,����ؼ����м��ÿո�ֿ�\n");
        char s[100];
        gets(s);
        if(blank(s)== 0)
           { printf("�ؼ��ʲ���Ϊ��\n");
            system("pause");
            kehu(a,list,car, change);
            break;
        }
        int x=infoCheck(a,s);
        if(x==0) {
            strcat(s," ");
            strcat(s,a->account);
        }
        printf("%10s%11s%10s%11s%10s%10s%10s%9s%20s\n","�˺�","�û���","����Ʒ��","��������","����۸�","��������","����","ʱ��","״̬");
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
                   gets(u);
                   clientRequest_PUSH(change,a,testList,s,u );
                   printf("�˻��������ύ\n");
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
        break;
    case'7':
        system("cls");
        printf("���Ƿ�ȷ��ע���˻���\n");
        printf("1.ȷ��     2.ȡ��\n");
        //�е����⣻
        char f=_getch();
            int status;
        switch (f) {
        case '1':

        clientLogout(list,a->account,&status);
        if(status==0)
            printf("ɾ���ɹ�\n");
        else
            printf("ɾ��ʧ�ܣ�������\n");
        system("pause");
            break;
        case '2':
           kehu(a,list,car, change);
            break;
        default:
            printf("��������ȷ��ѡ��\n");
            system("pause");
            kehu(a,list,car, change);
             break;
        }
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
         scanf("%d",&k);
         char m[50]=" ";
         gets_s(m,49);
         if(k>getLinkTotalNodeNum(testList)-1||k<1)
         {
             printf("��������ȷ�ı��\n");
             system("pause");
              kehu(a,list,car, change);
             break;
         }
         if(strlen(m)!=0)
         {
             printf("��������ȷ�ı��\n");
             system("pause");
              kehu(a,list,car, change);
             break;
         }
         else{
          k++;
         pBeverageNode p0=find(testList, k);
         printf("��ѡ���������\n");
         int r;
         scanf("%d",&r);
         b=getchar();
         if (r < 0||r>p0->storeNum) {
             printf("��������ȷ������!\n");
             system("pause");
             kehu(a,list,car, change);
             break;
         }
         addshoppingcar(car,a,p0,r);
         printf("��ӳɹ�\n");
         showshoppingcar(car,a->username);
         system("pause");
          kehu(a,list,car, change);
         break;}
   case '2':
         system("cls");
         showshoppingcar(car,a->username);
         printf("��ѡ��Ҫ�޸ĵ����\n");
         int j;
         scanf("%d",&j);
         char c[50]=" ";
         gets_s(c,49);

         if(j>getNum(car)-1||j<1)
         {
             printf("��������ȷ�ı��\n");
             system("pause");
            kehu(a,list,car, change);
            break;
         }
         if(strlen(c)!=0)
         {
             printf("��������ȷ�ı��\n");
             system("pause");
            kehu(a,list,car, change);
            break;
         }
         else{
             j++;
         pClientshoppingcar p1= finding(car, j);
         printf("������Ҫ�޸ĵ�����\n");
         int y;
         scanf("%d",&y);
         char sa[50]=" ";
         gets_s(sa,49);
         if (y < 1) {
             printf("��������ȷ������!\n");
             system("pause");
             kehu(a,list,car, change);
             break;
         }
         if(strlen(sa)!=0)
         {
             printf("��������ȷ�ı��\n");
             system("pause");
            kehu(a,list,car, change);
            break;
         }
         changeshoppingcar(car,p1->name,y );
         printf("�޸ĳɹ�\n");
         showshoppingcar(car,a->username);
         system("pause");
        kehu(a,list,car, change);
        break;}
    case '3':
         system("cls");
         int status;
         showshoppingcar(car,a->username);
         printf("��ѡ��Ҫɾ�������\n");
         int h;
         scanf("%d",&h);
         char d[50]=" ";
         gets_s(d,49);

         if(h>getNum(car)-1||h<1)
         {
             printf("��������ȷ�ı��\n");
             system("pause");
            kehu(a,list,car, change);
            break;
         }
         if(strlen(d)!=0)
         {
             printf("��������ȷ�ı��\n");
             system("pause");
            kehu(a,list,car, change);
            break;
         }
         else{
             h++;
         pClientshoppingcar p2=finding(car,h);
         car=deleteshoppingcar(car,p2->name,&status);
         printf("ɾ���ɹ�\n");
         showshoppingcar(car,a->username);
         system("pause");
         kehu(a,list,car, change);
         break;}
   case '4':
         system("cls");
         printf("��ѡ��Ҫ���ҵķ�ʽ\n");
         printf("1.��ˮ����   2.��ˮƷ��\n");
         char mi=_getch();
         switch (mi) {
         case'1':
             system("cls");
             showshoppingcar(car,a->username);
             printf("������Ҫ���ҵ�����\n");
             char w[20] = {0};
             gets(w);
             searchshoppingcar(car, w);
             system("pause");
             kehu(a,list,car, change);
             break;
         case '2':
             system("cls");
             showshoppingcar(car,a->username);
             printf("������Ҫ���ҵ�Ʒ��\n");
             char wi[20] = {0};
             gets(wi);
             searchshoppingcar2(car, wi);
             system("pause");
             kehu(a,list,car, change);
             break;
         default:
             printf("��������ȷ�ı��\n");
             system("pause");
          kehu(a,list,car, change);
             break;

         }


   case'5':
         system("cls");
         showshoppingcar(car,a->username);
         printf("������Ҫ����ı��\n");
         int p;
         scanf("%d",&p);
         char de[50]=" ";
       gets_s(de,49);
         if(p>getNum(car)-1||p<1)
         {
             printf("��������ȷ�ı��\n");
             system("pause");
            kehu(a,list,car, change);
            break;
         }
         if(strlen(de)!=0)
         {
             printf("��������ȷ�ı��\n");
             system("pause");
            kehu(a,list,car, change);
            break;
         }
         else{
             p++;
         pClientshoppingcar p3=finding(car, p);
         pBeverageNode p4=findname(testList, p3->name);
         if(a->saving>=(p3->cost))
         {buy(a,p4,p3->amount);
          reduceSaving(pInfo, p3->cost);
             deleteshoppingcar(car,p3->name,&status);
             printf("����ɹ�\n");
         system("pause");
      kehu(a,list,car, change);
         break;}
         else
         {printf("����\n");
          system("pause");
        kehu(a,list,car, change);
         break;}}

   case'6':
         system("cls");
         kehu(a,list,car, change);
         break;
     default:
         printf("������������������\n");
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
    printf("������������������\n");
    system("pause");
    system("cls");
 kehu(a,list,car, change);
    break;
    }return 0;
}

int shanghu(pclientRequestList change){
    system("cls");
printf("��ѡ�����б�\n");
  printf("1.����\n");
  printf("2.��ѯ���\n");
  printf("3.��Ʒ����\n");
  printf("4.ɾ�����\n");
  printf("5.�޸���Ʒ��Ϣ\n");
  printf("6.����˻�����\n");
  printf("7.��ʼ�����\n");
  printf("8.�趨�ʽ�\n");
  printf("9.��ѯ�ʽ�\n");
  printf("0.����\n");
  char d =_getch();
  switch(d)

  {case'1':
  {system("cls");
      if (pInfo == NULL) {
          printf("�����趨�ʽ�\n");
          system("pause");
          shanghu(change);
          break;
      }
      printf("��ѡ�������ʽ\n");
      printf("1.�ֶ����������Ϣ\n");
      printf("2.���ļ����������Ϣ\n");
      char j=_getch();
      switch (j) {
      case'1':
      if (testList == NULL) {
          printf("���ȳ�ʼ����棡\n");
          getchar();
          system("pause");
          shanghu(change);
      }
      system("cls");
      printf("������Ʒ��\n");
      char fe[20];
      gets(fe);
      printf("��������Ʒ��\n");
      char fd[20];
      gets(fd);
      printf("���������ʱ��\n");
      char fg[20];
      gets(fg);
      printf("��������Ʒ����\n");
      int k;
      scanf("%d",&k);
      if (k < 0) {
          printf("��������ȷ������!\n");
          system("pause");
          break;
      }
      printf("��������Ʒ�۸�\n");
      int l;
      scanf("%d",&l);
      char ch=getchar();
      printf("��������Ʒ��Ϣ\n");
      char fs[20];
      gets(fs);
      pBeverageList newNode=newBeverageNode(fe, fd, fg, k, l, fs, pInfo);
      insertLast(testList, newNode);
       printf("�����ɹ�");
          break;
      case'2':
          system("cls");
          printf("�������ļ���ַ\n");
          char u[1000];
          gets(u);
          if (testList) addFromFile(u, testList, pInfo);
          else testList = createFromFile(u, pInfo);

          break;
      default:printf("�����������������\n");
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
      printf("\n�Ƿ񱣴浱ǰ��棿��1���� 0����\n");
      int a = 0;
      scanf("%d", &a);
      getchar();
      if (a == 1) writeIntoFile(testList);
      system("pause");
      system("cls");
     shanghu(change);
      break;}
  case'3':
  {system("cls");
      if (testList == NULL) {
          printf("���ȳ�ʼ����棡\n");
          system("pause");
          shanghu(change);
          break;
      }
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
              printf("��������");
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
              printf("��������");
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
              printf("��������");
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
              printf("��������");
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
          printf("���ȳ�ʼ����棡\n");
          system("pause");
          shanghu(change);
          break;
      }
      if (isEmpty(testList)) {
          printf("���Ϊ�գ�\n");
          system("pause");
          shanghu(change);
          break;
      }
      showStaff(testList);
      printf("������ɾ���Ĳ�Ʒ���\n");
      int bh ;
      scanf("%d",&bh);
      getchar();
      if (bh < 0) {
          printf("��������ȷ������!\n");
          system("pause");
          break;
      }
      printf("%d", bh);
      deleteBeverage(testList, bh);
      printf("�ɹ�ɾ��\n");
      system("cls");
      showStaff(testList);
      system("pause");
      shanghu(change);
      break;}
  case'5':
  {system("cls");
      if (testList == NULL) {
          printf("���ȳ�ʼ����棡\n");
          system("pause");
          shanghu(change);
          break;
      }
      showStaff(testList);
      printf("�������Ʒ���\n");
      int bi=_getch()-'0';
      if(bi>getLinkTotalNodeNum(testList))
           {
               printf("��������ȷ�ı��\n");
               system("pause");
               shanghu(change);
              break;
           }
           else{
      printf("�������Ʒ��Ϣ\n");
      char ke[20];
      gets(ke);
      changeBeverageInfo(testList, bi, ke);
      printf("�޸ĳɹ�\n");
      system("pause");
       shanghu(change);
      break;}}
   case'6':
      system("cls");
      int u=clientRequest_SHOW(change);
      if(u==0)
      {
          printf("��ǰ���˻�����\n");
          system("pause");
           shanghu(change);
          break;
      }
      else{
      printf("��ѡ��Ҫ��������Ŀ��\n");
      int v;
      scanf("%d",&v);
      getchar();
      if (v < 0) {
          printf("��������ȷ������!\n");
          system("pause");
          break;
      }
      printf("����Ŀ�˻�ԭ��Ϊ��\n");
      clientRequest_SHOWMORE(change,v);
      printf("��ѡ���Ƿ���׼�˻�\n");
      printf("1.��׼  2.����׼\n");
      int y;
      scanf("%d",&y);
      getchar();
      clientRequest_POP(change,v,y, pInfo);
      printf("�����ɹ�\n");
      system("pause");
      shanghu(change);
      break;}
  case'7':
      system("cls");
      if (pInfo == NULL) {
          printf("�����趨�ʽ�\n");
          system("pause");
          shanghu(change);
          break;
      }
      printf("�������ʼ������ַ\n");
      char o[50];
      gets(o);
      testList= createFromFile(o, pInfo);
      system("pause");
      shanghu(change);
      break;
  case'8':
      system("cls");
      printf("�������ʽ�\n");
      float g;
      char c[20];
      if(scanf("%f",&g)>0)
          {
                    getchar();
          if (g < 0) {
              printf("��������ȷ������!\n");
              system("pause");
              break;
          }
          pInfo = initInteractInfo(g);
          printf("��ֵ�ɹ�\n");
          system("pause");
           shanghu(change);}
      else{gets(c);
          printf("��������ȷ�Ľ��\n");
           system("pause");
          shanghu(change);}
      break;
  case'9':
        system("cls");
        if (pInfo) {
            showInfoSaving(pInfo);
        } else {
            printf("�����趨��ʼ�ʽ�!\n");
        }
        system("pause");
        shanghu(change);
  case'0':
      break;
  default:
      printf("������������������\n");
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
  printf("     ��ѡ��\n");
  printf("1.��¼     2.ע��\n");
  char c=_getch();
  switch(c)
  {
  case'1':
  {system("cls");
  printf("�������˺�\n");
  char zh[20];
  gets(zh);
  printf("����������\n");
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
        printf("��ǰ�̻���δ���ţ�\n������ɿ����ʽ�ĳ�ʼ��!\n");
        system("pause");
        break;
    }
  printf("�������û���\n");
  char yh[20];
  gets(yh);
  if(strlen(yh)==0)
     { printf("�û�������Ϊ��\n");
      system("pause");
      break;}
  if(Check(yh)==-1)
  {
      printf("�û����������ַ���������� ��������ȷ��ʽ�����ƣ�\n");
      system("pause");
      break;
  }
  printf("�������˺�\n");
  char hz[20];
  gets(hz);
  if(strlen(hz)==0)
     { printf("�˺Ų���Ϊ��\n");
      system("pause");
      break;}
  if(Check(hz)==-1)
  {
      printf("�˺ű������ַ���������� ��������ȷ��ʽ�����ƣ�\n");
      system("pause");
      break;
  }
  printf("����������\n");
  char im[20];
  gets(im);
  if(strlen(im)==0)
     { printf("���벻��Ϊ��\n");
      system("pause");
      break;}
  signUp(list, hz, im, yh,0,0,0);
  printf("ע��ɹ�");
  system("pause");
  system("cls");
      break;}
  default:
      printf("������������������\n");
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
  signUp(list, "0", "0", "0",0,0,-1);
 while(1)
{system("cls");
 printf("��ӭ�����ˮ����ϵͳ\n");
 system("pause");
 system("cls");
 denglu(list, car,change);

}
    return 0;
}
