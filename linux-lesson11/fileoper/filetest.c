#include <stdio.h>
#include <string.h>
int main()
{
    FILE* fp= fopen("./linux84","w+");
    if(!fp)
    {
        printf("open file failed\n");
        return -1;
    }
    printf("open file succes\n");
    
    const char* str="linux so easy";
    ssize_t ret=fwrite(str,1,strlen(str),fp);
    printf("write block count is %d\n",ret);

    fseek(fp,1,SEEK_SET);

    char buf[1024]={0};
    ret= fread(buf,1,4,fp);
    printf("ret=%d,buf=%s\n",ret,buf);
    fclose(fp);
    return 0;
}
