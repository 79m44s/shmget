#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include"shmd.h"
#include<string.h>
#include<signal.h>

/*
函数功能：控制shmr.c和shmw.c运行，销毁共享内存段
*/

int main()
{

    int shmid;
    key_t key;
    void *shm;
    Shmd *shmd;
    char ch;
    
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

    printf("p--pause,o--continue,k--kill,q--quit input\n");
    
    while(1)
    {
        switch(ch = getchar())
        {
            case('p'):
                      {
                          kill(shmd->rpid,SIGTSTP);
                          break;
                      }
            case('o'):
                      {
                          kill(shmd->rpid,SIGCONT);
                          break;
                      }
            case('q'):
                      {
                          kill(shmd->rpid,SIGINT);
                          kill(shmd->wpid,SIGINT);
                          break;
                      }
            default:
                      {
                          printf("p--pause,o--continue,q--quit\n");
                          break;
                      }
        }

        if('q' == ch)
        {
            break;
        }
    }

    if(-1 == shmdt(shm))
    {
        perror("解除共享内存失败：\n");
        exit(1); 
    }
   
    if(-1 == shmctl(shmid,IPC_RMID,NULL))
    {
        perror("删除共享内存失败：\n");
        exit(1); 
    }

    printf("已删除共享内存\n");
    return 0;
}
