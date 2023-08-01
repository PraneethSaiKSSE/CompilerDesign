#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROD_SIZE 100

typedef struct {
    char nonTerminal;
    char followSet[MAX_PROD_SIZE];
} FollowSet;

// Function to check if a character is a non-terminal
int isNonTerminal(char symbol) {
    return isupper(symbol);
}

// Function to add a character to the FOLLOW set of a non-terminal
void addToFollowSet(FollowSet *followSets, char nonTerminal, char symbol) {
    int i;
    for (i = 0; followSets[i].nonTerminal != '\0'; i++) {
        if (followSets[i].nonTerminal == nonTerminal) {
            int j;
            for (j = 0; followSets[i].followSet[j] != '\0'; j++) {
                if (followSets[i].followSet[j] == symbol) {
                    return;
                }
            }
            followSets[i].followSet[j] = symbol;
            followSets[i].followSet[j + 1] = '\0';
            return;
        }
    }
    // Non-terminal not found, add it to the followSets array
    followSets[i].nonTerminal = nonTerminal;
    followSets[i].followSet[0] = symbol;
    followSets[i].followSet[1] = '\0';
    followSets[i + 1].nonTerminal = '\0';
}

// Function to compute the FOLLOW set for a given non-terminal
void computeFollowSet(char grammar[][MAX_PROD_SIZE], int numProductions, FollowSet *followSets, char nonTerminal) {
    if (nonTerminal == grammar[0][0]) {
        addToFollowSet(followSets, nonTerminal, '$');
    }

    int i, j, k;
    for (i = 0; i < numProductions; i++) {
        for (j = 3; grammar[i][j] != '\0'; j++) {
            if (grammar[i][j] == nonTerminal) {
                int nextSymbolIndex = j + 1;
                while (grammar[i][nextSymbolIndex] != '\0') {
                    char nextSymbol = grammar[i][nextSymbolIndex];

                    // If the next symbol is a terminal, add it to the FOLLOW set
                    if (!isNonTerminal(nextSymbol)) {
                        addToFollowSet(followSets, nonTerminal, nextSymbol);
                        break;
                    }

                    // If the next symbol is a non-terminal, find its FIRST set
                    int foundEpsilon = 0;
                    for (k = 0; followSets[k].nonTerminal != '\0'; k++) {
                        if (followSets[k].nonTerminal == nextSymbol) {
                            int l;
                            for (l = 0; followSets[k].followSet[l] != '\0'; l++) {
                                if (followSets[k].followSet[l] == 'e') {
                                    foundEpsilon = 1;
                                } else {
                                    addToFollowSet(followSets, nonTerminal, followSets[k].followSet[l]);
                                }
                            }
                            if (!foundEpsilon) {
                                break;
                            }
                        }
                    }

                    // If e is in the FIRST set of the next symbol, continue with the next symbol in the production
                    if (!foundEpsilon) {
                        break;
                    }

                    nextSymbolIndex++;
                }

                // If the whole production is processed and e is in the FIRST set of the next symbol, add e to the FOLLOW set
                if (grammar[i][nextSymbolIndex] == '\0') {
                    addToFollowSet(followSets, nonTerminal, 'e');
                }
            }
        }
    }
}

int main() {
    char grammar[MAX_PROD_SIZE][MAX_PROD_SIZE];
    int numProductions;
    FollowSet followSets[MAX_PROD_SIZE];
    int i;

    // Input the grammar
    printf("Enter the number of productions: ");
    scanf("%d", &numProductions);
    getchar(); // Clear the newline character from the input buffer

    printf("Enter the grammar (e.g., E->E+T|E->T): \n");
    for (i = 0; i < numProductions; i++) {
        fgets(grammar[i], MAX_PROD_SIZE, stdin);
    }

    // Compute the FOLLOW sets for all non-terminals
    for (i = 0; i < numProductions; i++) {
        if (isNonTerminal(grammar[i][0])) {
            computeFollowSet(grammar, numProductions, followSets, grammar[i][0]);
        }
    }

    // Print the computed FOLLOW sets
    printf("\nComputed FOLLOW sets:\n");
    for (i = 0; followSets[i].nonTerminal != '\0'; i++) {
        printf("FOLLOW(%c) = {", followSets[i].nonTerminal);
        int j;
        for (j = 0; followSets[i].followSet[j + 1] != '\0'; j++) {
            printf("%c, ", followSets[i].followSet[j]);
        }
        printf("%c}\n", followSets[i].followSet[j]);
    }

    return 0;
}

