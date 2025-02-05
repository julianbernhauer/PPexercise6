#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MATRIX_SIZE 1000 // if you get memory problem, you can lower the size but revert it back before submission

typedef struct {
    float **matrix1;
    float **matrix2;
    float **result;
    int start_row;
    int end_row;
    int size;
} ThreadData;

void *thread_matrix_add(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    // implement the rest here, i.e, the for loop
    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < data->size; j++) {
            data->result[i][j] = data->matrix1[i][j] + data->matrix2[i][j];
        }
    }
    pthread_exit(NULL);
}

void parallel_for_matrix_add(float **matrix1, float **matrix2, float **result, int size, int num_threads) {
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];
    int chunk = size / num_threads;

    for (int i = 0; i < num_threads; i++) {
        thread_data[i].matrix1 = matrix1;
        thread_data[i].matrix2 = matrix2;
        thread_data[i].result = result;
        thread_data[i].size = size;
        thread_data[i].start_row = i * chunk;
        //letzte row sollte tritzdem bearbeitet werden
        thread_data[i].end_row = (i == num_threads - 1) ? size : (i + 1) * chunk;
        pthread_create(&threads[i], NULL, thread_matrix_add, &thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
}

int main() {
    int size = MATRIX_SIZE;
    int num_threads = 4;

    float **matrix1 = (float **)malloc(size * sizeof(float *));
    float **matrix2 = (float **)malloc(size * sizeof(float *));
    float **result = (float **)malloc(size * sizeof(float *));

    for (int i = 0; i < size; i++) {
        matrix1[i] = (float *)malloc(size * sizeof(float));
        matrix2[i] = (float *)malloc(size * sizeof(float));
        result[i] = (float *)malloc(size * sizeof(float));
    }

    // Initialize matrices
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix1[i][j] = i + j;
            matrix2[i][j] = (i - j) * 2;
        }
    }

    // Start the timer
    clock_t start = clock();

    parallel_for_matrix_add(matrix1, matrix2, result, size, num_threads);

    // Stop the timer
    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sample results: %f %f %f\n", result[0][0], result[size - 1][size - 1], result[size / 2][size / 2]);
    printf("Time taken: %f seconds\n", cpu_time_used);

    for (int i = 0; i < size; i++) {
        free(matrix1[i]);
        free(matrix2[i]);
        free(result[i]);
    }

    free(matrix1);
    free(matrix2);
    free(result);

    return 0;
}
