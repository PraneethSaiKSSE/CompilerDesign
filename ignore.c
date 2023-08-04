#include <stdio.h>
int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }
    int currentChar, prevChar = EOF;
    int inComment = 0; 
    while ((currentChar = fgetc(inputFile)) != EOF) {
        if (inComment) {
            if (prevChar == '*' && currentChar == '/') {
                inComment = 0;
                prevChar = EOF;
                continue;
            }
        } else {
            if (prevChar == '/' && currentChar == '*') {
                inComment = 1;
                prevChar = EOF;
                continue;
            }
        }

        if (!inComment && currentChar != ' ' && currentChar != '\t') {
            putchar(currentChar);
        }

        prevChar = currentChar;
    }

    fclose(inputFile);
    return 0;
}

