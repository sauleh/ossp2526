// We have an array of 100 million numbers. 
// The single-threaded version loops through all 100 million one by one
// The multi-threaded version splits the array into 4 equal chunks and assigns one chunk to each thread, so all 4 chunks are summed simultaneously. 

#include <stdio.h>
#include <time.h>

// 100 million elements so it is large enough to make the difference in
// execution time clearly visible between single and multi threaded
#define SIZE 100000000

long long array[SIZE];

// A precise timer using the system's monotonic clock as it is more accurate than time() for measuring short durations.
double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int main() {
    // Fill array with 1s so the expected result is exactly SIZE
    for (int i = 0; i < SIZE; i++) array[i] = 1;

    double start = get_time(); // record time before work starts

    // Since there is one loop for one core w/ 100 million iterations, the CPU cannot move to the next element until it finishes the current one
    long long total = 0;
    for (int i = 0; i < SIZE; i++) total += array[i];

    double elapsed = get_time() - start; // time after work finishes

    printf("Result: %lld\n", total);
    printf("Time: %.4f sec\n", elapsed);
    return 0;
}