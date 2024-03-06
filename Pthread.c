#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2

int fib_sequence[100]; // Assuming a maximum sequence length of 100

// Function to compute Fibonacci sequence
void *compute_fibonacci(void *arg) {
    int *n = (int *)arg;
    int i;
    fib_sequence[0] = 0;
    fib_sequence[1] = 1;
    for (i = 2; i <= *n; i++) {
        fib_sequence[i] = fib_sequence[i - 1] + fib_sequence[i - 2];
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc, t, n;

    printf("Enter the number of Fibonacci sequence terms to compute: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    // Create threads
    rc = pthread_create(&threads[0], NULL, compute_fibonacci, (void *)&n);
    if (rc) {
        printf("Error: Unable to create thread, %d\n", rc);
        exit(-1);
    }

    // Join threads
    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    // Print Fibonacci sequence
    printf("Fibonacci Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", fib_sequence[i]);
    }
    printf("\n");

    pthread_exit(NULL);
}
