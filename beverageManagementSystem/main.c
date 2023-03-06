#include <stdio.h>
#include "merchantAndClient.h"

int main()
{
    pClientLinkedList head;
    head=initClient();

    signUp(head,"helloworld","123456","zhang",0);
    signUp(head,"hhh","123","test",200);
    int n;
    clientNode user=signIn(head,"hhh","123456",&n);
    printf("\n%d%s",n,user->username);
    return 0;
}


