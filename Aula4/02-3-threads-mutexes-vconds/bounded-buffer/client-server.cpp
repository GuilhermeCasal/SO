#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <cctype>
#include <string>
#include "thread.h"

#define FIFOSZ  10

typedef struct FIFO
{
    uint32_t ii;   ///< point of insertion
    uint32_t ri;   ///< point of retrieval
    uint32_t cnt;  ///< number of items stored
    uint32_t ids[FIFOSZ];  ///< storage memory
    pthread_cond_t notEmpty = PTHREAD_COND_INITIALIZER;
    pthread_cond_t notFull = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t accessCR = PTHREAD_MUTEX_INITIALIZER;
}FIFO;

typedef struct SLOT
{
    ServiceRequest req;
    ServiceResponse res;
    bool hasResponse = false;
    pthread_mutex_t accessCR = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t available = PTHREAD_COND_INITIALIZER;
}SLOT;

typedef struct ARG
{
    int id;
    int iter;
}ARG;


static SLOT slots[FIFOSZ];
static FIFO frees;
static FIFO pending;

//Inicializar as FIFO frees
void freesInit(void){
    mutex_lock(&frees.accessCR);
    frees.ii = frees.ri = 0;
    frees.cnt = FIFOSZ;

    uint32_t i;
    for ( i = 0; i < FIFOSZ; i++)
    {
        frees.ids[i] = i;
        cond_signal(&frees.notEmpty);
        mutex_unlock(&frees.accessCR);
    }
}

//Inicializar as FIFO pending
void pendingInit(void){
    mutex_lock(&frees.accessCR);
    pending.cnt = pending.ii = pending.ri = 0;
    cond_signal(&pending.notFull);
    mutex_unlock(&pending.accessCR);
}


int main(void){
    int nservers = 2;
    int nclients = 3;

    //inicializar os fifos
    freesInit();
    pendingInit();


}