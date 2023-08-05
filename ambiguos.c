#include <stdio.h>
#include <string.h>

int isAmbiguous(char* input, char* rule1, char* rule2, int start, int end) {
	int i;
    if (start == end) {
        return 1; // Empty substring is ambiguous
    }

    for (i = start + 1; i < end; i++) {
        if (input[i] == rule2[0]) {
            int len = strlen(rule1);
            if (i - start >= len && strncmp(input + start, rule1, len) == 0) {
                return isAmbiguous(input, rule1, rule2, start + len, i) && isAmbiguous(input, rule1, rule2, i, end);
            }
        }
    }

    return 0; // Not ambiguous
}

int main() {
    char input[100];
    char rule1[100];
    char rule2[100];

    printf("Enter the first rule (S->aSb|ab): ");
    scanf("%s", rule1);

    printf("Enter the second rule (S->aSb|ab): ");
    scanf("%s", rule2);

    printf("Enter an input string: ");
    scanf("%s", input);

    int ambiguous = isAmbiguous(input, rule1, rule2, 0, strlen(input) - 1);
    if (ambiguous) {
        printf("The given grammar is ambiguous for the input.\n");
    } else {
        printf("The given grammar is not ambiguous for the input.\n");
    }

    return 0;
}

