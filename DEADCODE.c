#include <stdio.h>

int main() {
    int x = 5;
    int y = 3;
    int z = 0;  // This variable is unused

    int result = x + y;
    printf("\n HERE Z IS THE DEAD CODE IT DOES NOT EFFECT FINAL RESULT\n");
    printf("Result: %d\n", result);

    return 0;
}

