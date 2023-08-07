#include <stdio.h>

void deadFunction() {
   
    printf("This is dead code.\n");
}

int main() {
    int x = 5;
    
    if (0) {
        x = 10;  // This code is dead because the condition is always false
                //this line will be never executed in the output
    }
    printf("HERE if(0) never gets executed, it's a dead code\n");
    
    printf("x = %d\n", x);
    
    return 0;
}

