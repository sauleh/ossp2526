//Multiplying two 512×512 matrices requires 512 × 512 × 512 = 134 million operations. 
// This is the most compute-heavy of the three exercises. The result matrix C has 512 rows, and crucially, each row of C can be computed completely independently of every other row.
// This makes it a perfect fit for multithreading and so we assign groups of rows to each thread with zero dependencies between them.

#include <stdio.h>
#include <time.h>

#define N 512

double A[N][N], B[N][N], C[N][N];

double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int main() {
    // Initialize matrices with simple values
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = B[i][j] = i + j + 1;

    double start = get_time();

    // Three nested loops = O(N^3) complexity.
    // For each cell C[i][j], we compute the dot product of
    // row i of A and column j of B — that's N multiplications and additions.
    // With N=512: 512 * 512 * 512 = 134 million operations, all sequential.
    for (int i = 0; i < N; i++)           // for each row of C
        for (int j = 0; j < N; j++) {     // for each column of C
            C[i][j] = 0;
            for (int k = 0; k < N; k++)   // dot product
                C[i][j] += A[i][k] * B[k][j];
        }

    double elapsed = get_time() - start;

    printf("C[0][0] = %.0f\n", C[0][0]); 
    printf("Time: %.4f sec\n", elapsed);
    return 0;
}