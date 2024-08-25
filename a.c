#include<stdlib.h>
#include<fcntl.h>
#include <stdio.h>
#include<string.h>
#include<stdbool.h>  
#include<math.h>
#include<unistd.h>
#include<sys/epoll.h>
#include<pthread.h>
#include<sys/wait.h>
#include<signal.h>
#include<sys/shm.h>
#include<unistd.h>
#include <sys/stat.h>
int flag;
int* fd;
void foo(){
     while(1){
       if(flag == 0){
        printf("parent %d\n" , fd[0]) ; 
        flag = 1;
        }
        sleep(2);
     }
}




int main(){
    flag = 1; 
   key_t key = ftok("/",1);
   int shmid = shmget(key,4096,0666 | IPC_CREAT);
   fd = shmat(shmid,NULL,0666);
   if(fork() == 0){
     while(1){
            printf("write num: ");
            scanf("%d" , &fd[0]);
            flag = 0;
     }
   }else{
      foo();
      wait(0);
      
   }
   

   
}


