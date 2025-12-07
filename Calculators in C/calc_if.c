#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define maxsize 1000

float add(float result);
float sub(float result);
float mul(float result);
float divi(float result);
int pos(int result);
int menu(int choise);
float read_number(float num);
void print_number(float result);
void exite();

int main(){
	
	int choice;
	float res=0;

	do{
	
		choice=menu(choice);
		
		if(choice==1)
		{
			printf("+\t");
			res=add(res);
		}
		else if(choice==2)
		{
			printf("-\t");
			res=sub(res);
		}
		else if(choice==3)	
		{
			printf("x\t");
			res=mul(res);
		}		
		else if(choice==4)
		{
			printf(":\t");
			res=divi(res);
		}	
		else if(choice==5)
		{
			printf("\t");
			res=pos(res);
		}	
		else if(choice==6)
		{
			printf("Exit\n");
			exite();
		}
		else if(choice==7)
		{
			print_number(res);
			printf("Result: %f\n", res);
		}
		else if(choice==8)
		{
			res=0;
		}	
		else
		{
			printf("Error!\n");
			printf("Exit!\n");		
		}	
	}while(choice!=6);
	
	exit(1);
		
	return 0;	
}


float add(float result){
	
	float num;
	
	printf("Give me a number to add: \n");
	scanf("%f", &num);
	

	result = result + num;
	
	printf("RESULT: %f\n", result);
	
	return result;
}

float sub(float result){
	
	float num;

	printf("Give me a number to add: \n");
	scanf("%f", &num);
	
	result = result - num;

	printf("RESULT: %f\n", result);

	return result;
}

float mul(float result){
	
	float num;
	
	printf("Give me a number to add: \n");
	scanf("%f", &num);
	
	result = result * num;

	printf("RESULT: %f\n", result);

	return result;
}

float divi(float result){
	
	float num;

	printf("Give me a number to add: \n");
	scanf("%f", &num);
	
	if(num==0){
		printf("Error. Not divided by 0\n");
	}
	else{
	result = result / num;	
	printf("RESULT: %f\n", result);
	}
	
	return result;
}

int pos(int result){
	
	int num;
	
	printf("Give me a number to add: \n");
	scanf("%d", &num);
	

	if(num==0){
		printf("Error. Not divided by 0\n");
	}
	else{
	result = result % num;	
	printf("RESULT: %d\n", result);
	}

	return result;
}

float read_number(float num){

	printf("Give me a number: \n");
	scanf("%f", &num);

	return num;
}

int menu(int choise){
	
	printf("1. + Add\n");
	printf("2. - Sub\n");
	printf("3. x Mul\n");
	printf("4. : Div\n");
	printf("5. [] Pos\n");
	printf("6. -> Exit\n");
	printf("7. # Show_result\n");
	printf("8. 0 Initialise\n");
	printf("Give me one choice: \n");
	scanf("%d", &choise);
	while( choise < 1 || choise > 8 ){
		printf("Give me one choice again: \n");
		scanf("%d", &choise);
	}
	return choise;
}

void print_number(float result){
	
	printf("FINAL RESULT: %f\n", result);	
}

void exite(){
	printf("Exit\n");
	exit(1);
}