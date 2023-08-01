#include <stdio.h>
#include <string.h>

#define MAX_PROD_SIZE 100

void eliminateLeftRecursion(char grammar[][MAX_PROD_SIZE], int numProductions, char nonTerminal) {
    int i, j;
    int newProductions = 0;

    for (i = 0; i < numProductions; i++) {
        if (grammar[i][0] == nonTerminal) {
            if (grammar[i][3] == nonTerminal) {
                char alpha[MAX_PROD_SIZE] = "";
                char beta[MAX_PROD_SIZE] = "";
                int alphaIndex = 0, betaIndex = 0;

                for (j = 3; grammar[i][j] != '\0'; j++) {
                    if (grammar[i][j] == nonTerminal) {
                        alpha[alphaIndex++] = '\0';
                    }
                    alpha[alphaIndex++] = grammar[i][j];
                }
                alpha[alphaIndex] = '\0';

                for (j = 0; j < numProductions; j++) {
                    if (grammar[j][0] == nonTerminal && i != j) {
                        beta[betaIndex++] = '\0';
                        strcat(beta, &grammar[j][3]);
                        strcat(beta, "'");
                    }
                }
                beta[betaIndex] = '\0';

                strcpy(grammar[i], "");
                strcpy(grammar[i], nonTerminal);
                strcat(grammar[i], "->");
                strcat(grammar[i], beta);
                strcpy(grammar[numProductions + newProductions], "");
                strcpy(grammar[numProductions + newProductions], nonTerminal);
                strcat(grammar[numProductions + newProductions], "'");
                strcat(grammar[numProductions + newProductions], "->");
                strcat(grammar[numProductions + newProductions], alpha);
                strcat(grammar[numProductions + newProductions], beta);
                newProductions++;
            }
        }
    }

    printf("\nGrammar after eliminating left recursion for %c:\n", nonTerminal);
    for (i = 0; i < numProductions + newProductions; i++) {
        printf("%s\n", grammar[i]);
    }
}

int main() {
    char grammar[MAX_PROD_SIZE][MAX_PROD_SIZE];
    int numProductions;
    char nonTerminal;
    int i;

    printf("Enter the number of productions: ");
    scanf("%d", &numProductions);
    fflush(stdin);

    printf("Enter the grammar (e.g., E->E+T;E->T): \n");
    for (i = 0; i < numProductions; i++) {
        fgets(grammar[i], MAX_PROD_SIZE, stdin);
    }

    printf("\nEnter the non-terminal for which left recursion should be eliminated: ");
    scanf("%c", &nonTerminal);

    eliminateLeftRecursion(grammar, numProductions, nonTerminal);

    return 0;
}

