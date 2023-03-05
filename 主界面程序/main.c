#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
kehu(){system("cls");
    printf("  登录成功\n");
    printf("请选择功能列表\n");
    printf("1.存款\n");
    printf("2.查询商品\n");
    printf("3.订购\n");
    char f=_getch();
    switch(f)
    {
    case'1':
    system("cls");
    printf("存款函数\n");
    system("pause");
    system("cls");
    break;
    case'2':
    system("cls");
    printf("查询商品函数\n");
    system("pause");
    system("cls");
    break;
    case'3':
    system("cls");
    printf("订购函数\n");
    system("pause");
    system("cls");
    break;
    default:
    printf("输入有误，请重新输入\n");
    system("pause");
    system("cls");
    kehu();
    }return 0;
}
int main()
{
 while(1)
{
 printf("欢迎进入酒水管理系统\n");
 printf("   请选择您的身份\n");
 printf("1.商户       2.客户\n");
 char ch =_getch();
 switch(ch)
 {case'1':
 {system("cls");
  printf("请选择功能列表\n");
  printf("1.进货\n");
  printf("2.查询进货信息\n");
  printf("3.查询库存\n");
  printf("4.商品排序\n");
  printf("5.删除库存\n");
  printf("6.修改商品信息\n");
  char d =_getch();
  switch(d)

  {case'1':
  {system("cls");
      printf("进货函数\n");
      system("pause");
      system("cls");
      break;}
  case'2':
  {system("cls");
      printf("查询进货信息函数\n");
      system("pause");
      system("cls");
      break;}
  case'3':
  {system("cls");
      printf("查询库存函数\n");
      system("pause");
      system("cls");
      break;}
  case'4':
  {system("cls");
      printf("商品排序函数\n");
      system("pause");
      system("cls");
      break;}
  case'5':
  {system("cls");
      printf("删除库存函数\n");
      system("pause");
      system("cls");
      break;}
  case'6':
  {system("cls");
      printf("修改商品信息函数\n");
      system("pause");
      system("cls");
      break;}
  default:
      printf("输入有误，请重新输入\n");
      system("pause");
      system("cls");
      break;
  }
  break;
}
 case'2':
 {system("cls");
  printf("    欢迎光临\n");
  printf("     请选择\n");
  printf("1.登录     2.注册\n");
  char c=_getch();
  switch(c)
  {
  case'1':
  {system("cls");
      printf("登录函数\n");
      system("pause");
     kehu();
     break;}
  case'2':
  {system("cls");
      printf("注册函数\n");
      system("pause");
      system("cls");
      break;}
  default:
      printf("输入有误，请重新输入\n");
      system("pause");
      system("cls");
      break;
  }

  break;
 }
 default:
     printf("输入有误，请重新输入\n");
     system("pause");
     system("cls");
     break;
 }

}
    return 0;
}
