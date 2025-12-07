#include <stdio.h>
#include <stdlib.h>

float add(float result);
float sub(float result);
float mul(float result);
float divi(float result);
float mod(float result);
int menu();
void print_number(float result);

int main() {

    int choice;
    float res = 0;

    do {
        choice = menu();

        switch(choice) {
            case 1:
                res = add(res);
                break;

            case 2:
                res = sub(res);
                break;

            case 3:
                res = mul(res);
                break;

            case 4:
                res = divi(res);
                break;

            case 5:
                res = mod(res);
                break;

            case 6:
                printf("Exit...\n");
                exit(0);
                break;

            case 7:
                print_number(res);
                break;

            case 8:
                res = 0;
                printf("Result reset to 0\n");
                break;

            default:
                printf("Error!\n");
        }

    } while(choice != 6);

    return 0;
}

float add(float result) {
    float num;
    printf("Give a number to add: ");
    scanf("%f", &num);
    result += num;
    printf("RESULT: %f\n", result);
    return result;
}

float sub(float result) {
    float num;
    printf("Give a number to subtract: ");
    scanf("%f", &num);
    result -= num;
    printf("RESULT: %f\n", result);
    return result;
}

float mul(float result) {
    float num;
    printf("Give a number to multiply: ");
    scanf("%f", &num);
    result *= num;
    printf("RESULT: %f\n", result);
    return result;
}

float divi(float result) {
    float num;
    printf("Give a number to divide: ");
    scanf("%f", &num);
    if(num == 0) {
        printf("Error: Division by 0\n");
        return result;
    }
    result /= num;
    printf("RESULT: %f\n", result);
    return result;
}

float mod(float result) {
    int num1 = (int)result;
    int num2;

    printf("Give a number for modulo: ");
    scanf("%d", &num2);

    if(num2 == 0) {
        printf("Error: Modulo by 0\n");
        return result;
    }

    int r = num1 % num2;
    printf("RESULT: %d\n", r);

    return (float)r;
}

int menu() {
    int choice;
    printf("\n======== MENU ========\n");
    printf("1. + Add\n");
    printf("2. - Sub\n");
    printf("3. x Mul\n");
    printf("4. : Div\n");
    printf("5. %% Mod\n");
    printf("6. -> Exit\n");
    printf("7. # Show result\n");
    printf("8. 0 Initialise\n");
    printf("Choose: ");
    scanf("%d", &choice);

    while(choice < 1 || choice > 8) {
        printf("Choose again: ");
        scanf("%d", &choice);
    }

    return choice;
}

void print_number(float result) {
    printf("FINAL RESULT: %f\n", result);
}
