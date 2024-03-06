#include <stdio.h>
#include <omp.h>

int fibonacci(int n) {
    int a = 0, b = 1, next, i;
    if (n <= 1)
        return n;

    #pragma omp parallel
    {
        #pragma omp single
        {
            for (i = 2; i <= n; i++) {
                #pragma omp task shared(a, b) firstprivate(next)
                {
                    next = a + b;
                    a = b;
                    b = next;
                }
            }
        }
    }
    return b;
}

int main() {
    int n = 10; // Change n to the desired Fibonacci number
    omp_set_nested(1); // Enable nested parallelism
    omp_set_dynamic(0); // Disable dynamic adjustment of the number of threads
    int result = fibonacci(n);
    printf("Fibonacci number at position %d is %d\n", n, result);
    return 0;
}
