#include <stdio.h>
#include <stdlib.h>

typedef struct eigenV{
    int nSize;
    int* e;
}Eigen;

typedef struct matrix{
    int nSize; //n x n size
    int** m; //matrix a
    int* e;  //u vector matrix
}Matrix;

//Setup matrix
Matrix* setupMatrix(int sz){
    Matrix* A = (Matrix*)malloc(sizeof(Matrix));
    A->nSize = sz;
    //Init array of arrays
    A->m = (int**)malloc(sizeof(int*) * sz);
    A->e = (int*)malloc(sizeof(int) * sz);

    for(int i = 0; i < sz; i++){
        A->m[i] = (int*)malloc(sizeof(int) * sz);       
    }
    return A;
}

//setup EigenVector
Eigen* setupEigen(int sz){
    Eigen* U = (Eigen*)malloc(sizeof(Eigen));
    U->nSize = sz;
    U->e = (int*)malloc(sizeof(int) * sz);
    return U;
}

Eigen* calculateEigenVector(Matrix* mA){
    Eigen* result = setupEigen(mA->nSize);

    for(int row = 0; row < mA->nSize; row++){
        result->e[row] = 0;
        for(int col = 0; col < mA->nSize; col++){
            result->e[row] += mA->m[row][col] * mA->e[col];
        }
    }
    return result;
}


void insertIntoMatrix(Matrix* mA, char* argv[]){
    int argIndex = 2;

}

void printResult(Eigen* result){
    for(int row = 0; row < result->nSize; row++){
        printf("row %d: %d\n", row, result->e[row]);
    }
}

void freeMatrices(Matrix* matrix){
    free(matrix->e);
    
    for(int i = 0; i < matrix->nSize; i++){
        free(matrix->m[i]);
    }
    free(matrix->m);
    free(matrix);
}

int main(int argc, char* argv[]){
    int userInput;
    int argIndex = 2;
    int row = 0;
    //Init matrix data structure
    int sz = atoi(argv[1]);
    int areaSz = sz * sz;
    Matrix* mA = setupMatrix(sz);

    for(int i = 0; i < mA->nSize; i++){
        for(int j = 0; j< mA->nSize; j++){
            mA->m[i][j] = atoi(argv[argIndex]);
            argIndex += 1;
            printf("array number: %d\n", mA->m[i][j]);
        }
    } 
    while(scanf("%d", &userInput) == 1){
        mA->e[row] = userInput;
        row += 1;
    }

    Eigen* result = calculateEigenVector(mA);
    
    printResult(result);
    
    free(result->e);
    free(result);
    freeMatrices(mA);
    return 0;
}
