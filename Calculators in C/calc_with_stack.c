#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

double numStack[MAX]; // Stoiva gia gia arithmous
int numTop = -1;

void pushNum(double n) { numStack[++numTop] = n; }
double popNum() { return numStack[numTop--]; }

char opStack[MAX]; //Stoiva gia telestes
int opTop = -1;

void pushOp(char c) { opStack[++opTop] = c; }
char popOp() { return opStack[opTop--]; }
char peekOp() { return opStack[opTop]; }

int prec(char op) {   //Protaireotites telestwn
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void applyOp(char op) { //Efarmogh Praxis
    double b = popNum();
    double a = popNum();
    double r;

    switch(op) {
        case '+': r = a + b; break;
        case '-': r = a - b; break;
        case '*': r = a * b; break;
        case '/':
            if (b == 0) {
                printf("Wrong: You can't divide with 0!\n");
                exit(1);
            }
            r = a / b;
            break;
        default:
            printf("Not valid operation!\n");
            exit(1);
    }
    pushNum(r);
}

double evaluate(const char *expr) {
    int i = 0;
    while (expr[i] != '\0') {
        if (isspace(expr[i])) { i++; continue; }

        if (isdigit(expr[i]) || (expr[i] == '.')) { //Arithmos
            char buffer[64];
            int bi = 0;

            while (isdigit(expr[i]) || expr[i] == '.') {
                buffer[bi++] = expr[i++];
            }
            buffer[bi] = '\0';

            pushNum(atof(buffer));
            continue;
        }

        if (expr[i] == '(') { //Aristeri Parethensi
            pushOp(expr[i]);
            i++;
            continue;
        }

        if (expr[i] == ')') { //Dexia Parenthesi 
            while (opTop != -1 && peekOp() != '(') {
                applyOp(popOp());
            }
            if (opTop == -1) {
                printf("Wrong: Not balanced parentheses!\n");
                exit(1);
            }
            popOp(); // Vgazoume tis dexia parenthesi
            i++;
            continue;
        }

        // Telestes
        if (strchr("+-*/", expr[i])) {
            char op = expr[i];
            // Vgale telestes megaliterhs h ishs proteraiothtas
            while (opTop != -1 && prec(peekOp()) >= prec(op)) {
                applyOp(popOp());
            }
            pushOp(op);
            i++;
            continue;
        }

        printf("Invalid character: %c\n", expr[i]);
        exit(1);
    }

    while (opTop != -1) {
        if (peekOp() == '(') { //Telos, vgale ypoloipous telestes kai arithmous
            printf("Wrong: Not  balanced parentheses!\n");
            exit(1);
        }
        applyOp(popOp());
    }

    return popNum();
}

int main() {
    char expr[MAX];

    printf("Give the expression: ");
    fgets(expr, MAX, stdin);

    double result = evaluate(expr);
    printf("Result: %.6f\n", result);

    return 0;
}
