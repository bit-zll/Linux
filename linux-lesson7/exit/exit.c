#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
void func(void)
{
    printf("i am func\n");
}
int main()
{
    atexit(func);
    printf("---begin---");
    //fflush(stdout);
    //_exit(2);
    //printf("---end---\n");
    return 0;
}
