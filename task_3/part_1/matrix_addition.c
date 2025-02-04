#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define MATRIX_SIZE 1000 // if you get memory problem, you can lower the size but revert it back before submission

void addMatrices(float **matrix1, float **matrix2, float **result, int size)
{
    // Add a suitable OpenMP pragma
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

int main()
{
    int size = MATRIX_SIZE;

    float **matrix1 = (float **)malloc(size * sizeof(float *));
    float **matrix2 = (float **)malloc(size * sizeof(float *));
    float **result = (float **)malloc(size * sizeof(float *));

    for (int i = 0; i < size; i++)
    {
        matrix1[i] = (float *)malloc(size * sizeof(float));
        matrix2[i] = (float *)malloc(size * sizeof(float));
        result[i] = (float *)malloc(size * sizeof(float));
    }

    // Initialize matrices
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix1[i][j] = i + j;
            matrix2[i][j] = (i - j) * 2;
        }
    }

    // Start the timer
    clock_t start = clock();

    addMatrices(matrix1, matrix2, result, size);

    // Stop the timer
    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sample results: %f %f %f\n", result[0][0], result[size - 1][size - 1], result[size / 2][size / 2]);
    printf("Time taken: %f seconds\n", cpu_time_used);

    for (int i = 0; i < size; i++)
    {
        free(matrix1[i]);
        free(matrix2[i]);
        free(result[i]);
    }

    free(matrix1);
    free(matrix2);
    free(result);

    return 0;
}

