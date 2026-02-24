#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

// --- Lock-Free Stack Implementation ---
typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* stack_head = NULL;

void push(int val) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = __atomic_load_n(&stack_head, __ATOMIC_RELAXED);
    while (!__atomic_compare_exchange_n(&stack_head, &newNode->next, newNode, 
                                        false, __ATOMIC_RELEASE, __ATOMIC_RELAXED));
}

bool pop(int* result) {
    Node* oldHead = __atomic_load_n(&stack_head, __ATOMIC_ACQUIRE);
    while (oldHead != NULL) {
        if (__atomic_compare_exchange_n(&stack_head, &oldHead, oldHead->next, 
                                        false, __ATOMIC_RELEASE, __ATOMIC_RELAXED)) {
            *result = oldHead->data;
            free(oldHead); // Note: Simple free() is used for this demo only
            return true;
        }
    }
    return false;
}

// --- Stress Test Code ---
#define NUM_THREADS 10
#define OPS_PER_THREAD 100000

void* thread_func(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < OPS_PER_THREAD; i++) {
        push(id * OPS_PER_THREAD + i);
        int val;
        pop(&val);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    printf("Starting stress test with %d threads...\n", NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        // Create threads using the standard pthread_create function
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        // Wait for all threads to finish
        pthread_join(threads[i], NULL);
    }

    printf("Test complete. Stack head is %p\n", (void*)stack_head);
    return 0;
}
