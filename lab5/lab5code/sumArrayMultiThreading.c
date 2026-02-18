// We have an array of 100 million numbers. 
// The single-threaded version loops through all 100 million one by one
// The multi-threaded version splits the array into 4 equal chunks and assigns one chunk to each thread, so all 4 chunks are summed simultaneously. 

#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define SIZE 100000000
#define NUM_THREADS 4   // change this to the number of your CPU cores

long long array[SIZE];

// Each thread stores its result in its own slot in this array and avoids a "race condition" where two threads write to the same variable at the same time and corrupt the result.
long long partial_sums[NUM_THREADS];

// Struct to pass multiple arguments to a thread as pthreads only allows one argument, so we put everything in a struct.

typedef struct {
    int thread_id;  // which thread this is
    int start;      // index to start summing
    int end;        // index to stop summing
} ThreadArgs;

// This is the function each thread runs.
void *partial_sum(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    long long sum = 0;

    // Each thread sums only its assigned portion of the array
    // Thread 0: elements 0 to 24,999,999 etc.
    for (int i = args->start; i < args->end; i++)
        sum += array[i];

    // Store the result
    partial_sums[args->thread_id] = sum;
    return NULL;
}

double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int main() {
    for (int i = 0; i < SIZE; i++) array[i] = 1;

    pthread_t threads[NUM_THREADS];   
    ThreadArgs args[NUM_THREADS];     
    int chunk = SIZE / NUM_THREADS;   

    double start = get_time();

    // Create all threads and they begin running immediately after creation
    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].thread_id = i;
        args[i].start = i * chunk;
        // Last thread takes any remaining elements in case SIZE isn't divisible evenly
        args[i].end = (i == NUM_THREADS - 1) ? SIZE : (i + 1) * chunk;

        // pthread_create(thread handle, attributes, function to run, argument)
        pthread_create(&threads[i], NULL, partial_sum, &args[i]);
    }

    // pthread_join waits for each thread to finish before continuing. Without this, the main program might try to read partial_sums before the threads have finished writing to it.
    for (int i = 0; i < NUM_THREADS; i++) pthread_join(threads[i], NULL);

    // Combine the 4 results into the final answer
    long long total = 0;
    for (int i = 0; i < NUM_THREADS; i++) total += partial_sums[i];

    double elapsed = get_time() - start;

    printf("Result: %lld\n", total);
    printf("Time: %.4f sec\n", elapsed);
    return 0;
}