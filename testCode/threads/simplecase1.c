#include <stdio.h>
#include <pthread.h> //when compile need to add -lpthread

void thread(void){
    int i;
    for(i = 0; i < 3; i++){
        printf("this is a pthread.\n");
    }
}

int main(int argc, char**argv ){
    pthread_t id;
    int i,ret;
    ret = pthread_create(&id, NULL, (void*)thread, NULL);
    if(ret != 0){
        printf("Create pthread error!\n");
        return -1;
    }
    pthread_join(id, NULL);

    for(i = 0; i<3; i++){
        printf("this is the main process.\n");
    }
    return 0;
}