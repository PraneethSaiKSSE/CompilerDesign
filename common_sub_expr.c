#include <stdio.h>

int main() {
    int x = 5;
    int y = 3;

    int result1 = x * y + 10;  // Common subexpression: x * y
    int result2 = x * y - 5;   // Common subexpression: x * y
    printf("\nHERE x*y is common sub-expression which is calculated once and reused in both results\n ");

    printf("Result 1: %d\n", result1);
    printf("Result 2: %d\n", result2);

    return 0;
}

