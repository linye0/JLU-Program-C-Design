#include <stdio.h>
#include "merchantAndClient.h"

int main()
{
    pClientLinkedList head;
    head=initClient();

    signUp(head,"helloworld","123456","zhang",0,0,0);
    signUp(head,"hhh","123","test",200,0,0);//检查重名!!别忘记了!!
    signUp(head,"hhh","123","test1",200,0,0);
    int n;
    clientNode user=signIn(head,"hhh","123456",&n);
    printf("\n%d%s",n,user->username);
    changeAccount(head,"hhh","hh1");

    pClientLinkedList user2=clientLogout(head,"aaa",&n);
    while(user2!=NULL)
    {
        printf("%s\n",user2->username);
        user2=user2->next;
    }
    return 0;
}


