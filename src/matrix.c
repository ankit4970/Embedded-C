/* ************************************************************************************************
 * matrix.c
 *************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* ************************************************************************************************
 * printMatrix
 * 		Print matrix
 *************************************************************************************************/
void printMatrix(int matrix[][3])
{
	for (int i = 0 ; i < 3 ; ++i)
	{
		for ( int j =0 ; j < 3 ; ++j)
		{
			printf("%d,",matrix[i][j]);
		}
		printf("\n");
	}
}

/* ************************************************************************************************
 * printMatrixSinglePointer
 * 		Print matrix using a single integer pointer 
 *************************************************************************************************/
void printMatrixSinglePointer(int *matrix)
{
	for (int i = 0 ; i < 3 ; ++i)
	{
		for (int j = 0 ; j < 3 ; ++j)
		{
			printf("%d,", *(matrix+i*3+j));
		}
		printf("\n");
	}
}

/* ************************************************************************************************
 * transposeMatrix
 * 		Transpose a square matrix in-place
 *************************************************************************************************/
void transposeMatrix(int A[][3], int row, int column)
{
    for (int i = 0 ; i < row ; ++i)
    {
    	for (int j = 0 ; j < i ; ++j)
    	{
    		int temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
    	}
    }
}

/* ************************************************************************************************
 * matrixRotate90
 * 		Rotate a matrix 90 degree clock-wise
 *************************************************************************************************/
void matrixRotate90()
{
	int M = 3;
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    for (int i = 0 ; i < M/2.0 ; ++i)
    {
        for (int j = i ; j < M-i ; ++j)
        {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[M-j][i];
            matrix[M-j][i] = matrix[M-i][M-j];
            matrix[M-i][M-j] = matrix[j][M-i];
            matrix[j][M-i] = temp;
        }
    }
    printMatrix(matrix);
}

/* ************************************************************************************************
 * rotateMatrix
 * 		Rotate a matrix 90 degree clock-wise (Method 2)
 *************************************************************************************************/
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void rotateMatrix() 
{
	int M = 3;
	int matrix[3][3] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};

    int k = 0;
    
    transposeMatrix(matrix, M, M);

    for (int i = 0 ; i < M ; ++i)
    {
        for (int j = 0 , k = M-1 ; j < k ; ++j , --k)
        {
            swap(&matrix[i][j], &matrix[i][k]);
        }
    }
}

/* ************************************************************************************************
 * matrixMultiply
 *************************************************************************************************/
void matrixMultiply(int m1, int m2, int **mat1, int n1, int n2, int **mat2)
{
    int x, i, j;
    int res[m1][n2];
    for (i = 0; i < m1; i++)
    {
        for (j = 0; j < n2; j++)
        {
            res[i][j] = 0;
            for (x = 0; x < m2; x++)
            {
                res[i][j] += mat1[i][x] * mat2[x][j];
            }
        }
    }
    for (i = 0; i < m1; i++)
    {
        for (j = 0; j < n2; j++)
        {
            printf("%d ", *(*(res+i)+j));
        }
        printf("\n");
    }
}

/* ************************************************************************************************
 * matrixMain
 *************************************************************************************************/
int matrixMain()
{
	int* matrixPointer = (int*)malloc(sizeof(int)*3*3);

	for (int i = 0 ; i < 3 ; ++i)
	{
		for ( int j = 0 ; j < 3 ; ++j)
		{
			*(matrixPointer+i*3+j) = i*3+j;
		}
	}

	printMatrixSinglePointer(matrixPointer);

	int matrixPointer1[3][3] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};
	
	transposeMatrix(matrixPointer1, 3, 3);
	printMatrix(matrixPointer1);

	return 0;
}