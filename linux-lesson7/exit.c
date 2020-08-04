#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void func(void)
{
    printf("i am func\n");
}

int main()
{
    atexit(func);
    printf("---begin---\n");
    //_exit(2);
    //printf("---end---\n");
    return 0;
}
