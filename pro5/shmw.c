#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include"shmd.h"
#include<string.h>
#include<fcntl.h>


/*
函数功能：创建共享内存段，写入进程ID和指令字符串
*/
int main()
{

    int shmid;
    key_t key;
    void *shm;
    Shmd *shmd;
    int fd;
    char str[STR_SIZE];
       
    if((fd=open(PATH,O_RDONLY)) == 0)
    {
        printf("open ls.txt error\n");
        exit(1);
    }
    
    if(read(fd,str,STR_SIZE) == -1)
    {
        printf("读取文件错误\n");
        exit(1);
    }

    
    key=ftok(KEY_PATH,66);

    shmid = shmget(key,sizeof(Shmd),IPC_CREAT | 0666);
    if(-1 == shmid)
    {
        perror("创建共享内存段失败：\n");
        exit(1);
    }

    shm = shmat(shmid,0,0);
    if((void *)-1 == shm)
    {
        perror("获取共享内存段指针失败：\n");
        exit(1);
    }

    shmd = (Shmd *)shm;

    shmd->wpid = getpid();

    //shmd->buf = "pwd";
    //strcpy(shmd->buf,"pwd");

    strcpy(shmd->buf,str);

    printf("%s\n",shmd->buf);
    if(-1 == shmdt(shm))
    {
        perror("解除共享内存失败：\n");
        exit(1); 
    }

    while(1);
    {
        ;
    }
}
