#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int sharedi = 0;
void increse_num(void);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void increse_num(void){
    long i,tmp;
    for(i=0;i<100000;i++){
        if(pthread_mutex_lock(&mutex)!=0){
            perror("pthread_mutex_lock");
            exit(EXIT_FAILURE);
        }
        tmp = sharedi;
        tmp += 1;
        sharedi = tmp;

        if(pthread_mutex_unlock(&mutex)!=0){
            perror("pthread_mutex_unlock");
            exit(EXIT_FAILURE);
        }
    }

    return ;
}

int main(){

    int ret;
    pthread_t thread1,thread2,thread3;

    ret = pthread_create(&thread1,NULL,(void*)increse_num,NULL);
    ret = pthread_create(&thread2,NULL,(void*)increse_num,NULL);
    ret = pthread_create(&thread3,NULL,(void*)increse_num,NULL);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);

    printf("the global var{sharedi}:%d\n",sharedi);


    return 0;
}