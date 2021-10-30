#define MAX_BROJ_MUSTERIJA 20

dispatch_semaphore_t customerS;
dispatch_semaphore_t barberS;
dispatch_semaphore_t mutex;

int brojMesta = 3;
int brojMusterija = 0;
int brojac = MAX_BROJ_MUSTERIJA;

pthread_t musterije[MAX_BROJ_MUSTERIJA];
pthread_t barber;

void cutHair(void){
    
    int vreme = (rand() % 4) + 1;
    
    dispatch_semaphore_wait(mutex,DISPATCH_TIME_FOREVER);
    brojMusterija--;
    dispatch_semaphore_signal(mutex);
    
    printf("BARBER: Musterija dobija uslugu sisanja %d sekunde\n", vreme);
    sleep(vreme);
    
}

void getHairCut(int i){
    printf("MUSTERIJA: Musterija #%d dobija uslugu\n", i);
}

void balk(int i){
    printf("MUSTERIJA: Sva mesta su zauzeta, musterija broj %d napusta objekat!\n", i);
}

void *barberT(void *arg){

    while(brojMusterija > 0 || brojac != 0){
        
        dispatch_semaphore_wait(customerS, DISPATCH_TIME_FOREVER);
        dispatch_semaphore_signal(barberS);
        cutHair();
    
    }
    
    pthread_exit(NULL);
}

void *customerT(void *arg){

    if(brojMusterija == brojMesta){
        balk((int)arg);
    }
    else{
        
        dispatch_semaphore_wait(mutex,DISPATCH_TIME_FOREVER);
        brojMusterija++;
        dispatch_semaphore_signal(mutex);
        
        printf("MUSTERIJA: Musterija %d zauzima slobodno mesto, trenutno je zauzeto %d mesta u cekaonici\n",(int)arg, brojMusterija);
               
        dispatch_semaphore_signal(customerS);
        dispatch_semaphore_wait(barberS, DISPATCH_TIME_FOREVER);
        getHairCut((int)arg);
    }
    
    pthread_exit(NULL);
    }

