#include <stdio.h>
#include <omp.h>

int fibonacci(int n) {
    int a = 0, b = 1, next, i;
    if (n <= 1)
        return n;

    #pragma omp parallel for
    for (i = 2; i <= n; i++) {
        next = a + b;
        a = b;
        b = next;
    }
    return b;
}

int main() {
    int n = 10; // Change n to the desired Fibonacci number
    int result = fibonacci(n);
    printf("Fibonacci number at position %d is %d\n", n, result);
    return 0;
}
