//Multiplying two 512×512 matrices requires 512 × 512 × 512 = 134 million operations. 
// This is the most compute-heavy of the three exercises. The result matrix C has 512 rows, and crucially, each row of C can be computed completely independently of every other row.
// This makes it a perfect fit for multithreading and so we assign groups of rows to each thread with zero dependencies between them.

#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define N 512
#define NUM_THREADS 4

double A[N][N], B[N][N], C[N][N];

// Each thread only needs to know which rows it is responsible for
typedef struct { int start_row, end_row; } ThreadArgs;

// Each thread computes its assigned rows of C independently

void *multiply(void *arg) {
    ThreadArgs *a = (ThreadArgs *)arg;

    // Thread only works on rows [start_row, end_row)
   
    for (int i = a->start_row; i < a->end_row; i++)
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    return NULL;
}

double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int main() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = B[i][j] = i + j + 1;

    pthread_t threads[NUM_THREADS];
    ThreadArgs args[NUM_THREADS];
    int chunk = N / NUM_THREADS;  // 512 / 4 = 128 rows per thread

    double start = get_time();

    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].start_row = i * chunk;
        args[i].end_row = (i == NUM_THREADS - 1) ? N : (i + 1) * chunk;

        // Each thread starts computing its rows immediately
    
        pthread_create(&threads[i], NULL, multiply, &args[i]);
    }

    // Main thread waits here until ALL threads finish their rows.
    
    for (int i = 0; i < NUM_THREADS; i++) pthread_join(threads[i], NULL);

    double elapsed = get_time() - start;

    printf("C[0][0] = %.0f\n", C[0][0]); // should match single-threaded version
    printf("Time: %.4f sec\n", elapsed);
    return 0;
}
