#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4
#define OPERATIONS 100000

int array[1000000];
int index_pos = 0;

void* writer(void* arg) {
    for (int i = 0; i < OPERATIONS; i++) {
        array[index_pos++] = i;
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, writer, NULL);

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    printf("Final index: %d\n", index_pos);
    return 0;
}