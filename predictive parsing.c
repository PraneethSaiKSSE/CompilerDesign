#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Function to implement the predictive parser
bool parseExpression(char** input, char lookahead);

bool match(char** input, char expected) {
    if (**input == expected) {
        (*input)++;
        return true;
    }
    return false;
}

bool parseFactor(char** input) {
    if (match(input, '(')) {
        bool result = parseExpression(input, ')');
        return result && match(input, ')');
    } else if (isalnum(**input)) {
        (*input)++;
        return true;
    }
    return false;
}

bool parseTermTail(char** input) {
    if (match(input, '*')) {
        return parseFactor(input) && parseTermTail(input);
    }
    return true; // Epsilon production (empty)
}

bool parseTerm(char** input) {
    return parseFactor(input) && parseTermTail(input);
}

bool parseExprTail(char** input) {
    if (match(input, '+')) {
        return parseTerm(input) && parseExprTail(input);
    }
    return true; // Epsilon production (empty)
}

bool parseExpression(char** input, char lookahead) {
    return parseTerm(input) && parseExprTail(input);
}

int main() {
    char expression[100];
    printf("Enter an arithmetic expression: ");
    scanf("%99[^\n]", expression);

    // Tokenizing the input expression and using a pointer to track the current token
    char* input_ptr = expression;
    
    bool success = parseExpression(&input_ptr, '\0');

    if (success && *input_ptr == '\0') {
        printf("Input expression is valid!\n");
    } else {
        printf("Input expression is invalid!\n");
    }

    return 0;
}

