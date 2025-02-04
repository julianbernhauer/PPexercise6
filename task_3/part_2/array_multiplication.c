#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    float *array1;
    float *array2;
    float *result;
    int start;
    int end;
} ThreadData;

void *thread_multiply(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    // implement the rest here, i.e, the for loop
    return NULL;
}

void parallel_for_multiply(float *array1, float *array2, float *result, int size, int num_threads) {
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];
    
    // fill in data structure for each thread
    // create the thread with respective workload
    // join the threads in the end and, if necessary, aggregate results
}

int main() {
    int size = 5000000; // if you get memory problem, you can lower the size but revert it back before submission
    int num_threads = 4;

    float *arr1 = (float *)malloc(size * sizeof(float));
    float *arr2 = (float *)malloc(size * sizeof(float));
    float *result = (float *)malloc(size * sizeof(float));

    if (arr1 == NULL || arr2 == NULL || result == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Initialize arrays
    for (int i = 0; i < size; i++) {
        arr1[i] = i + 1;
        arr2[i] = (i + 1) * 2;
    }

    // Start the timer
    clock_t start = clock();

    parallel_for_multiply(arr1, arr2, result, size, num_threads);

    // Stop the timer
    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print a few results as a sanity check
    printf("Result array: ");
    for (int i = 0; i < 5; i++) {
        printf("%f ", result[i]);
    }
    printf("\nTime taken: %f seconds\n", cpu_time_used);

    free(arr1);
    free(arr2);
    free(result);
    return 0;
}
