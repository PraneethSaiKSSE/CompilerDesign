#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROD_SIZE 100

typedef struct {
    char nonTerminal;
    char firstSet[MAX_PROD_SIZE];
} FirstSet;

// Function to check if a character is a non-terminal
int isNonTerminal(char symbol) {
    return isupper(symbol);
}

// Function to add a character to the FIRST set of a non-terminal
void addToFirstSet(FirstSet *firstSets, char nonTerminal, char symbol) {
    int i;
    for (i = 0; firstSets[i].nonTerminal != '\0'; i++) {
        if (firstSets[i].nonTerminal == nonTerminal) {
            int j;
            for (j = 0; firstSets[i].firstSet[j] != '\0'; j++) {
                if (firstSets[i].firstSet[j] == symbol) {
                    return;
                }
            }
            firstSets[i].firstSet[j] = symbol;
            firstSets[i].firstSet[j + 1] = '\0';
            return;
        }
    }
    // Non-terminal not found, add it to the firstSets array
    firstSets[i].nonTerminal = nonTerminal;
    firstSets[i].firstSet[0] = symbol;
    firstSets[i].firstSet[1] = '\0';
    firstSets[i + 1].nonTerminal = '\0';
}

// Function to compute the FIRST set for a given non-terminal
void computeFirstSet(char grammar[][MAX_PROD_SIZE], int numProductions, FirstSet *firstSets, char nonTerminal) {
    int i, j;
    for (i = 0; i < numProductions; i++) {
        if (grammar[i][0] == nonTerminal) {
            int productionIndex = 3;

            // If the production starts with a terminal, add it to the FIRST set
            if (!isNonTerminal(grammar[i][productionIndex])) {
                addToFirstSet(firstSets, nonTerminal, grammar[i][productionIndex]);
                continue;
            }

            // If the production starts with a non-terminal, find its FIRST set
            while (grammar[i][productionIndex] != '\0') {
                char symbol = grammar[i][productionIndex];

                // If the symbol is a terminal, add it to the FIRST set and stop processing this production
                if (!isNonTerminal(symbol)) {
                    addToFirstSet(firstSets, nonTerminal, symbol);
                    break;
                }

                // Find the FIRST set of the current non-terminal symbol
                for (j = 0; firstSets[j].nonTerminal != '\0'; j++) {
                    if (firstSets[j].nonTerminal == symbol) {
                        int k;
                        for (k = 0; firstSets[j].firstSet[k] != '\0'; k++) {
                            addToFirstSet(firstSets, nonTerminal, firstSets[j].firstSet[k]);
                        }
                        // If the symbol can derive e, continue with the next symbol in the production
                        if (firstSets[j].firstSet[0] == '\0') {
                            productionIndex++;
                        }
                        break;
                    }
                }
                if (firstSets[j].nonTerminal == '\0') {
                    // Non-terminal not found in the firstSets array, stop processing this production
                    break;
                }
            }
        }
    }
}

int main() {
    char grammar[MAX_PROD_SIZE][MAX_PROD_SIZE];
    int numProductions;
    FirstSet firstSets[MAX_PROD_SIZE];
    int i;

    // Input the grammar
    printf("Enter the number of productions: ");
    scanf("%d", &numProductions);
    getchar(); // Clear the newline character from the input buffer

    printf("Enter the grammar (e.g., E->E+T|E->T): \n");
    for (i = 0; i < numProductions; i++) {
        fgets(grammar[i], MAX_PROD_SIZE, stdin);
    }

    // Compute the FIRST sets for all non-terminals
    for (i = 0; i < numProductions; i++) {
        if (isNonTerminal(grammar[i][0])) {
            computeFirstSet(grammar, numProductions, firstSets, grammar[i][0]);
        }
    }

    // Print the computed FIRST sets
    printf("\nComputed FIRST sets:\n");
    for (i = 0; firstSets[i].nonTerminal != '\0'; i++) {
        printf("FIRST(%c) = {", firstSets[i].nonTerminal);
        int j;
        for (j = 0; firstSets[i].firstSet[j + 1] != '\0'; j++) {
            printf("%c, ", firstSets[i].firstSet[j]);
        }
        printf("%c}\n", firstSets[i].firstSet[j]);
    }

    return 0;
}

