#include "fmm.h"

#include "stdio.h"
#include "stdlib.h"


int* createUpSquareMatrix(int n,int start,int* matrix){
    int dim = n/2;
    int size = dim*dim;

    int* ret = (int*) malloc(sizeof(int) * size);
    if(!ret){
        free(ret);
        exit;
    }

    int* beg = matrix + start ;
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            *(ret+ (i * dim + j)) = *(beg+(i * dim + j));
        }
        beg +=dim;
    }
    return ret;
}

int* createBottomSquareMatrix(int n,int start,int* matrix){
    int dim = n/2;
    int size = dim*dim;

    int* ret = (int*) malloc(sizeof(int) * size);
    if(!ret) {
        free(ret);
        exit;
    }

    int* beg = matrix + n* (dim) +start;
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            *(ret+ (i * dim + j)) = *(beg+(i * dim + j));
        }
        beg +=dim;
    }
    return ret;
}


void MatMul(int* left, int* right,int* res,int n){
    int r;
    for(int k = 0; k<n; k++){
        for(int i = 0; i<n; i++){
            r = left[i * n + k];
            for(int j = 0; j < n; j++) {
                res[i * n + j] += r * right[k * n + j];
            }
        }
    }
}


int* createM1(int* A11,int* A22,int* B11,int*B22,int dim,int size){
    int* M1 = (int*)malloc(sizeof(int) * size);
    if(!M1){
        free(M1);
        exit;
    }
    int left[size];
    for (int i = 0; i< size; i++){
        left[i] = A11[i] + A22[i];
    }
    int right[size];
    for (int i = 0; i< size; i++){
        right[i] = B11[i] + B22[i];
    }
    MatMul(left,right,M1,dim);
    return M1;
}
int* createM2(int* A21,int* A22,int* B11,int dim,int size){
    int* M2 = (int*)malloc(sizeof(int) * size);
    if(!M2){
        free(M2);
        exit;
    }
    int left[size];
    for (int i = 0; i< size; i++){
        left[i] = A21[i] + A22[i];
    }
    MatMul(left,B11,M2,dim);
    return M2;
}
int* createM3(int* A11,int* B12,int* B22,int dim,int size){
    int* M3 = (int*)malloc(sizeof(int) * size);
    if(!M3){
        free(M3);
        exit;
    }
    int right[size];
    for (int i = 0; i< size; i++){
        right[i] = B12[i] - B22[i];
    }
    MatMul(A11,right,M3,dim);
    return M3;
}
int* createM4(int* A22,int* B21,int* B11,int dim,int size){
    int* M4 = (int*)malloc(sizeof(int) * size);
    if(!M4){
        free(M4);
        exit;
    }
    int right[size];
    for (int i = 0; i< size; i++){
        right[i] = B21[i] - B11[i];
    }
    MatMul(A22,right,M4,dim);
    return M4;
}
int* createM5(int* A11,int* A12,int* B22,int dim,int size){
    int* M5 = (int*)malloc(sizeof(int) * size);
    if(!M5){
        free(M5);
        exit;

    }
    int left[size];
    for (int i = 0; i< size; i++){
        left[i] = A11[i] + A12[i];
    }
    MatMul(left,B22,M5,dim);
    return M5;
}
int* createM6(int* A11,int* A21,int* B11,int* B12,int dim,int size){
    int* M6 = (int*)malloc(sizeof(int) * size);
    if(!M6){
        free(M6);
        exit;

    }
    int left[size];
    for (int i = 0; i < size; i++){
        left[i] = A21[i] - A11[i];
    }
    int right[size];
    for (int i = 0; i< size; i++){
        right[i] = B11[i] + B12[i];
    }
    MatMul(left,right,M6,dim);
    return M6;
}
int* createM7(int* A12,int* A22,int* B21,int* B22,int dim,int size){
    int* M7 = (int*)malloc(sizeof(int) * size);
    if(!M7){
        free(M7);
        exit;
    }
    int left[size];
    for (int i = 0; i< size; i++){
        left[i] = A12[i] - A22[i];
    }
    int right[size];
    for (int i = 0; i< size; i++){
        right[i] = B21[i] + B22[i];
    }
    MatMul(left,right,M7,dim);
    return M7;
}

void createC11(int* M1,int* M4, int* M5,int* M7,int* res,int n,int dim){

    int counter = 0;

    for(int i = 0;i < dim; i++){
        for(int j=0; j< dim; j++) {
            res[i * n + j] = M1[counter] + M4[counter] - M5[counter] + M7[counter];
            counter++;
        }
    }
}
void createC12( int* M3,int* M5,int* res,int n,int dim){
    int counter = 0;
    for(int i = 0;i < dim; i++){
        for(int j=0; j< dim; j++) {
            res[(i * n) + j + dim] = M3[counter] + M5[counter];
            counter++;
        }
    }
}
void createC21( int* M2,int* M4,int* res,int n,int dim,int start){
    int counter = 0;
    for(int i = 0;i < dim; i++){
        for(int j=0; j< dim; j++) {
            res[(i * n) + j + start] = M2[counter] + M4[counter];
            counter++;
        }
    }
}
void createC22(int* M1, int* M2,int* M3,int* M6,int* res,int n,int dim,int start){
    int counter = 0;
    for(int i = 0;i < dim; i++){
        for(int j=0; j< dim; j++) {
            res[(i * n) + j + start + dim] = M1[counter] - M2[counter] + M3[counter] + M6[counter];
            counter++;
        }
    }
}
void freeANB(int* A11,int* A12,int* A21, int* A22,int* B11,int* B12,int* B21, int* B22) {
    free(A11);
    free(A12);
    free(A21);
    free(A22);
    free(B11);
    free(B12);
    free(B21);
    free(B22);
}
void getMs(int* A,int* B,int** res,int n){
    int dim = n/2;
    int size = dim*dim;

    int* A11 = createUpSquareMatrix(n,0,A);
    int* A12 = createUpSquareMatrix(n,dim,A);
    int* A21 = createBottomSquareMatrix(n,0,A);
    int* A22 = createBottomSquareMatrix(n,dim,A);
    int* B11 = createUpSquareMatrix(n,0,B);
    int* B12 = createUpSquareMatrix(n,dim,B);
    int* B21 = createBottomSquareMatrix(n,0,B);
    int* B22 = createBottomSquareMatrix(n,dim,B);
    int* M1 =  createM1(A11,A22,B11,B22,dim,size);
    int* M2 = createM2(A21,A22,B11,dim,size);
    int* M3 = createM3(A11,B12,B22,dim,size);
    int* M4 = createM4(A22,B21,B11,dim,size);
    int* M5 = createM5(A11,A12,B22,dim,size);
    int* M6 = createM6(A11,A21,B11,B12,dim,size);
    int* M7 = createM7(A12,A22,B21,B22,dim,size);
    freeANB(A11,A12,A21,A22,B11,B12,B21,B22);
    res[1] = M1, res[2] = M2,res[3] = M3, res[4] = M4; res[5] = M5,res[6] = M6, res[7] = M7;
}

void printRes(int* res, int dim){
    for(int i = 0; i <dim; i++){
        for(int j = 0; j<dim; j++){
            printf("%d ",res[i * dim + j] );
        }
        printf("\n");
    }
}

void fmm(int n, int* m1, int* m2, int* result) {
   if(n == 0){
       *result = (*m1) * (*m2);
       return;
   }
   int size = n*n;
   int* res = (int*)malloc(sizeof(int) * size);
   int** Ms = (int**)malloc(sizeof(int*) * 7);
   getMs(m1,m2,Ms,n);

   int dim = n/2;
   int start = size / 2;
   createC11(Ms[1],Ms[4],Ms[5],Ms[7],res,n,dim);
   createC12(Ms[3],Ms[5],res,n,dim);
   createC21(Ms[2],Ms[4],res,n,dim,start);
   createC22(Ms[1],Ms[2],Ms[3],Ms[6],res,n,dim,start);
   for (int i = 0; i < n; i++) {
       for (int j = 0; j < n; j++) {
           result[i * n + j] = 0;
           for (int k = 0; k < n; k++) {
               result[i * n + j] += m1[i * n + k] * m2[k * n + j];
           }
       }
   }
    debug small matric's
  // printRes(result, n);
}
    MatMul(m1,m2,result,n);
}
