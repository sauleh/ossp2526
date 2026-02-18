#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 8
#define WITHDRAW_AMOUNT 1
#define OPERATIONS 1000000

int balance = 1000000;

void* withdraw(void* arg) {
    for (int i = 0; i < OPERATIONS; i++) {
        if (balance >= WITHDRAW_AMOUNT) {
            balance -= WITHDRAW_AMOUNT;
        }
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, withdraw, NULL);

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    printf("Final balance: %d\n", balance);
    return 0;
}