#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include"shmd.h"
#include<string.h>

/*
函数功能：读取共享内存段的信息，执行指令并每个两秒打印一次
*/
int main()
{

    int shmid;
    key_t key;
    void *shm;
    Shmd *shmd;
    key=ftok(KEY_PATH,66);

    shmid = shmget(key,0,0);
    if(-1 == shmid)
    {
        perror("获取共享内存段失败：\n");
        exit(1);
    }

    shm = shmat(shmid,0,0);
    if((void *)-1 == shm)
    {
        perror("获取共享内存段指针失败：\n");
        exit(1);
    }

    shmd = (Shmd *)shm;

    shmd->rpid = getpid();   
    //shmd->flag = 0;
    while(1)
    {
        sleep(2);
        printf("write进程ID为%d,read进程ID为%d\n",shmd->wpid,shmd->rpid);
        
        printf("指令字符串为%s\n",shmd->buf);

        printf("指令执行内容如下：\n");
        system(shmd->buf);
    }    
    
    if(-1 == shmdt(shm))
    {
        perror("解除共享内存失败：\n");
        exit(1); 
    }

    printf("删除共享内存，按enter：");
    getchar();
    
    if(-1 == shmctl(shmid,IPC_RMID,NULL))
    {
        perror("删除共享内存失败：\n");
        exit(1); 
    }
    return 0;
}
