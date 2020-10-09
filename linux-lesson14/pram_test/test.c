#include <stdio.h>

int swap(int a,int b)
{
    int c = a;
    a = b;
    b = c;
    printf("%d-%d\n",a,b);
}

void func(int *data)
{
    *data = 10;
}
int main()
{
    swap(1,2);
    int i;
    func(&i);
    printf("i=%d\n",i);
    return 0;
}
