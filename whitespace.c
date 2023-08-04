#include <stdio.h>

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    int whitespaceCount = 0;
    int newLineCount = 0;
    int currentChar;

    while ((currentChar = fgetc(inputFile)) != EOF) {
        if (currentChar == ' ' || currentChar == '\t') {
            whitespaceCount++;
        } else if (currentChar == '\n') {
            newLineCount++;
        }
    }

    fclose(inputFile);

    printf("Number of white spaces: %d\n", whitespaceCount);
    printf("Number of new line characters: %d\n", newLineCount);

    return 0;
}

