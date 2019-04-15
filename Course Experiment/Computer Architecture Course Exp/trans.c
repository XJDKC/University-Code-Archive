/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define SQUARE_SIDE(N) (N%8?16:8)

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int temp[8];
    int i,j,k,l;

    if (N%8)
    {
        for (i=0;i<N;i+=SQUARE_SIDE(N))
            for (j=0;j<M;j+=SQUARE_SIDE(N))
            {
                for (k=i;k<min(i+SQUARE_SIDE(N),N);k++)
                {
                    for (l=0;l<min(SQUARE_SIDE(N),M-j);l++)
                        if (k != j+l)
                            B[j+l][k]=A[k][j+l];
                        else
                            temp[0]=A[k][j+l];
                    if (i==j)
                        B[k][k]=temp[0];
                }
            }
    }
    else
    {
        for (i=0;i<N;i+=8)
            for (int j=0;j<M;j+=8)
            {
                for (int k=i;k<i+4;k++)
                {
                    for (l=0;l<8;l++)
                        temp[l]=A[k][j+l];
                    for (l=0;l<4;l++)
                    {
                        B[j+l][k] = temp[l];
                        B[j+l][k+4] = temp[l+4];
                    }
                }
                for (int k=j+4;k<j+8;k++)
                {
                    for (l=0;l<4;l++)
                        temp[l]=B[k-4][i+l+4];
                    for (l=4;l<8;l++)
                        temp[l]=A[i+l][k];

                    for (l=4;l<8;l++)
                        B[k-4][i+l]=A[i+l][k-4];
                    for (l=0;l<8;l++)
                        B[k][i+l]=temp[l];
                }
            }
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

