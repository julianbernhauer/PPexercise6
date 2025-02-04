#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

float dotProduct(float *array1, float *array2, int size)
{
    float sum = 0.0;

    // Add a suitable OpenMP pragma
    for (int i = 0; i < size; i++)
    {
        sum += array1[i] * array2[i];
    }

    return sum;
}

int main()
{
    int size = 1000000; // if you get memory problem, you can lower the size but revert it back before submission
    float *arr1 = (float *)malloc(size * sizeof(float));
    float *arr2 = (float *)malloc(size * sizeof(float));

    if (arr1 == NULL || arr2 == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Initialize arrays
    for (int i = 0; i < size; i++)
    {
        arr1[i] = i + 1;
        arr2[i] = size - i;
    }

    // Start the timer
    clock_t start = clock();

    float result = dotProduct(arr1, arr2, size);

    // Stop the timer
    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Dot product: %f\n", result);
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(arr1);
    free(arr2);
    return 0;
}
