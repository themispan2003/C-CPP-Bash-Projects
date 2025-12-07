#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const char *p;   // pointer points current position of expression 

void skipSpaces() { // skips the gaps
    while (*p == ' ') p++;
}

double parseNumber() { // Parsing  double nums
    skipSpaces();
    double result = 0.0;
    double frac = 0.1;
    int hasDot = 0;

    if (!isdigit(*p) && *p != '.')
        return 0.0;

    while (isdigit(*p) || *p == '.') {
        if (*p == '.') {
            hasDot = 1;
            p++;
            continue;
        }

        if (!hasDot) {
            result = result * 10 + (*p - '0');
        } else {
            result = result + (*p - '0') * frac;
            frac *= 0.1;
        }
        p++;
    }
    return result;
}

double parseExpression(); // forward declarations

double parseFactor() {
    skipSpaces();

    if (*p == '(') {
        p++; // skip '('
        double val = parseExpression();
        skipSpaces();
        if (*p == ')') p++; else {
            printf("Wrong: ')' misses\n");
            exit(1);
        }
        return val;
    }
    return parseNumber(); //number
}

double parseTerm() {
    double value = parseFactor();

    while (1) {
        skipSpaces();
        if (*p == '*') {
            p++;
            value *= parseFactor();
        }
        else if (*p == '/') {
            p++;
            double divisor = parseFactor();
            if (divisor == 0) {
                printf("Wrong: div by 0!\n");
                exit(1);
            }
            value /= divisor;
        }
        else break;
    }

    return value;
}

double parseExpression() {
    double value = parseTerm();

    while (1) {
        skipSpaces();
        if (*p == '+') {
            p++;
            value += parseTerm();
        }
        else if (*p == '-') {
            p++;
            value -= parseTerm();
        }
        else break;
    }

    return value;
}

int main() {
    char expr[256];

    printf("Give the expression: ");
    fgets(expr, sizeof(expr), stdin);

    p = expr;
    double result = parseExpression();

    printf("Result: %.6f\n", result);
    return 0;
}
