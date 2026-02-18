///Checking if a number is prime requires testing divisors up to its square root and so makes this a pure computation
// with no shortcuts. Doing this for every number from 2 to 5,000,000 is very CPU-heavy. 
// Single threading will use one thread, multithreading will split the numbers up.
#include <math.h> 
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

#define LIMIT 5000000
#define NUM_THREADS 4

// Each thread writes its count to its own slot to avoid race conditions
long long prime_counts[NUM_THREADS];

typedef struct { int id, start, end; } ThreadArgs;

double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i <= (int)sqrt(n); i++)
        if (n % i == 0) return 0;
    return 1;
}

// Each thread runs this function on its own range of numbers
void *count_primes(void *arg) {
    ThreadArgs *a = (ThreadArgs *)arg;
    long long count = 0;
    for (int i = a->start; i < a->end; i++)
        if (is_prime(i)) count++;

    // Save this thread's count in its own slot
    prime_counts[a->id] = count;
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadArgs args[NUM_THREADS];
    int chunk = LIMIT / NUM_THREADS;  // should be around 1.25 million numbers per thread

    double start = get_time();

    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].id = i;
        args[i].start = i * chunk;
        args[i].end = (i == NUM_THREADS - 1) ? LIMIT : (i + 1) * chunk;

        // Each thread immediately starts checking its range of numbers
        // All 4 threads run simultaneously on different CPU cores
        pthread_create(&threads[i], NULL, count_primes, &args[i]);
    }

    // Wait for all threads to finish before summing results
    for (int i = 0; i < NUM_THREADS; i++) pthread_join(threads[i], NULL);

    // Add up each thread's count to get the total
    long long total = 0;
    for (int i = 0; i < NUM_THREADS; i++) total += prime_counts[i];

    double elapsed = get_time() - start;

    printf("Primes found: %lld\n", total);
    printf("Time: %.4f sec\n", elapsed);
    return 0;
}