#include "fmm.h"

// Slow fmm :)
void fmm(int n, int* m1, int* m2, int* result) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i * n + j] = 0;  // result[i][j] = 0
            for (int k = 0; k < n; k++) 
                result[i * n + j] += m1[i * n + k] * m2[k * n + j];  // result[i][j] += m1[i][k] * m2[k][j]
        }
    }
}

