#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
kehu(){system("cls");
    printf("  ��¼�ɹ�\n");
    printf("��ѡ�����б�\n");
    printf("1.���\n");
    printf("2.��ѯ��Ʒ\n");
    printf("3.����\n");
    char f=_getch();
    switch(f)
    {
    case'1':
    system("cls");
    printf("����\n");
    system("pause");
    system("cls");
    break;
    case'2':
    system("cls");
    printf("��ѯ��Ʒ����\n");
    system("pause");
    system("cls");
    break;
    case'3':
    system("cls");
    printf("��������\n");
    system("pause");
    system("cls");
    break;
    default:
    printf("������������������\n");
    system("pause");
    system("cls");
    kehu();
    }return 0;
}
int main()
{
 while(1)
{
 printf("��ӭ�����ˮ����ϵͳ\n");
 printf("   ��ѡ���������\n");
 printf("1.�̻�       2.�ͻ�\n");
 char ch =_getch();
 switch(ch)
 {case'1':
 {system("cls");
  printf("��ѡ�����б�\n");
  printf("1.����\n");
  printf("2.��ѯ������Ϣ\n");
  printf("3.��ѯ���\n");
  printf("4.��Ʒ����\n");
  printf("5.ɾ�����\n");
  printf("6.�޸���Ʒ��Ϣ\n");
  char d =_getch();
  switch(d)

  {case'1':
  {system("cls");
      printf("��������\n");
      system("pause");
      system("cls");
      break;}
  case'2':
  {system("cls");
      printf("��ѯ������Ϣ����\n");
      system("pause");
      system("cls");
      break;}
  case'3':
  {system("cls");
      printf("��ѯ��溯��\n");
      system("pause");
      system("cls");
      break;}
  case'4':
  {system("cls");
      printf("��Ʒ������\n");
      system("pause");
      system("cls");
      break;}
  case'5':
  {system("cls");
      printf("ɾ����溯��\n");
      system("pause");
      system("cls");
      break;}
  case'6':
  {system("cls");
      printf("�޸���Ʒ��Ϣ����\n");
      system("pause");
      system("cls");
      break;}
  default:
      printf("������������������\n");
      system("pause");
      system("cls");
      break;
  }
  break;
}
 case'2':
 {system("cls");
  printf("    ��ӭ����\n");
  printf("     ��ѡ��\n");
  printf("1.��¼     2.ע��\n");
  char c=_getch();
  switch(c)
  {
  case'1':
  {system("cls");
      printf("��¼����\n");
      system("pause");
     kehu();
     break;}
  case'2':
  {system("cls");
      printf("ע�ắ��\n");
      system("pause");
      system("cls");
      break;}
  default:
      printf("������������������\n");
      system("pause");
      system("cls");
      break;
  }

  break;
 }
 default:
     printf("������������������\n");
     system("pause");
     system("cls");
     break;
 }

}
    return 0;
}
