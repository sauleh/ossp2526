///Checking if a number is prime requires testing divisors up to its square root and so makes this a pure computation
// with no shortcuts. Doing this for every number from 2 to 5,000,000 is very CPU-heavy. 
// Single threading will use one thread, multithreading will split the numbers up.
#include <math.h> 
#include <time.h>
#include <stdio.h>

#define LIMIT 5000000  // check all numbers from 2 up to this value

double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

// Returns 1 if n is prime, 0 if not
// We only check divisors up to sqrt(n) due to the fact that if no divisor exists
// up to that point, the number is prime. This is the standard efficient method, but still expensive across millions of numbers.
int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i <= (int)sqrt(n); i++)
        if (n % i == 0) return 0;  // found a divisor, not prime
    return 1;
}

int main() {
    double start = get_time();

    // Check every number one by one. For large numbers near 5,000,000, sqrt(n) ≈ 2236, so each check does up to ~2236 divisions. Very CPU-heavy.
    long long count = 0;
    for (int i = 2; i < LIMIT; i++)
        if (is_prime(i)) count++;

    double elapsed = get_time() - start;

    printf("Primes found: %lld\n", count);
    printf("Time: %.4f sec\n", elapsed);
    return 0;
}