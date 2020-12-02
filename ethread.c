#include "ethread.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main(int argc, char* argv[]){
    int userInput;
    int argIndex = 2;
    int unitRow = 0;
    int nSz = atoi(argv[1]);
    int area = nSz * nSz;

    //pointers to rows
    Data* args = (Data*)malloc(sizeof(Data) * nSz);

    setupRows(args, area, nSz);

    for(int row = 0; row < args->data->nSize; row++){
        for(int col = 0; col < args->data->nSize; col++){
            (args + row)->data->m[col] = atoi(argv[argIndex]);
            argIndex += 1;
        }
    }
    while(scanf("%d", &userInput) == 1){
        for(int i = 0; i < args->data->nSize; i++){
            //FIX THIS: There are repeats that can better processing time
            (args + i)->data->e[unitRow] = userInput;
        }
        unitRow += 1;
    }

    pthread_t t[nSz];  

    for(int i = 0; i < nSz; i++){
        pthread_create(&t[i], NULL, (void* (*) (void*))calculateEigenVector, (void*)(args + i));
    }
    for(int i = 0; i < nSz; i++){
        pthread_join(t[i], NULL);
    }
    printResults(args, nSz);
    freeMatrices(args, nSz);
    return 0;
}

//Setup product matrices
void setupRows(Data* row, int area, int nSz){
    //nSz = amount of rows = amount of threads = amount of structures
    for(int i = 0; i < nSz; i++) {
        (row + i)->data = (Matrix*)malloc(sizeof(Matrix));

        (row + i)->data->area = area;
        (row + i)->data->nSize = nSz;
        (row + i)->data->product = 0;

        (row + i)->data->m = (int*)malloc(sizeof(int) * nSz);
        (row + i)->data->e = (int*)malloc(sizeof(int) * nSz);
    }
}

void* calculateEigenVector(void* arg){

    //cast the 'arg' parameter to the correct data structure type
    Data* mA = (Data*)arg;
    for(int i = 0; i < mA->data->nSize; i++){
        mA->data->product += mA->data->m[i] * mA->data->e[i];
    }
    return NULL;
}

void freeMatrices(Data* args, int nSz){
    for(int i = 0; i < nSz; i++){
        free((args + i)->data->e);
        free((args + i)->data->m);
        free((args + i)->data);
    }
    free(args);
}

void printResults(Data* args, int nSz){
    for(int i = 0; i < nSz; i++){
        printf("THREAD %d: %d\n", i ,(args + i)->data->product);
    }
}
