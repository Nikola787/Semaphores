#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dispatch/dispatch.h>
#include <unistd.h>
#include "functions.h"

int main(){

    customerS = dispatch_semaphore_create(0);
    barberS = dispatch_semaphore_create(0);
    mutex = dispatch_semaphore_create(1);
    
    pthread_create(&barber, NULL, barberT, NULL);

    for(int i=0; i<MAX_BROJ_MUSTERIJA; i++){
        pthread_create(&musterije[i], NULL, customerT, (void *)(uintptr_t)(i+1));
        brojac--;
        sleep(1);
    }

    for(int i=0; i<MAX_BROJ_MUSTERIJA; i++){
        pthread_join(musterije[i], NULL);
    }
        pthread_join(barber, NULL);
    
    dispatch_release(customerS);
    dispatch_release(barberS);
    dispatch_release(mutex);

    printf("\nKraj programa\n");
    return 0;
}
