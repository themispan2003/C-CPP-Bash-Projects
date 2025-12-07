#include <iostream>
#include <iomanip>

void show_balance(double balance);
double deposit();
double withdraw(double balance);

int main(){

    int choice = 0;
    double balance = 150.51;

    do{
    std::cout<<"\nEnter your choice:\n\n";
    std::cout<<"1. Show balance\n";
    std::cout<<"2. Deposit money\n";
    std::cout<<"3. Withdraw money\n";
    std::cout<<"4. Exit.\n\n";
    std::cin >> choice;
    std::cin.clear();
    fflush(stdin);

    switch(choice){
        case 1:
            show_balance(balance);
            break;
        case 2:
            balance += deposit();
            show_balance(balance);
            break;
        case 3:
            balance-=withdraw(balance);
            show_balance(balance);        
            break;
        case 4:
            std::cout<<"\nThank you for using our app!\n";
            break;
        default:
            std::cout<<"\nPlease! Enter a choice (1-4): \n";
    }
    } while(choice!=4);
    return 0;
}

void show_balance(double balance){
    std::cout<<"\nThe balance is: $ "<<std::setprecision(2)<<std::fixed<<balance<<" \n";
}

double deposit(){
    double amount = 0;
    std::cout<<"\nEnter an amount to be deposited: ";
    std::cin >> amount;
    if(amount>0){
        return amount;
    }
    else{
        std::cout<<"\nThat is not a valid amount.\n";
        return 0;
    }
}

double withdraw(double balance){
    double amount = 0;
    std::cout<<"\nEnter an amount to be withdrawnd: ";
    std::cin >> amount;

    if(amount>balance){
        std::cout<<"\nNot enough money in the account!\n";
        return 0;
    }
    else if(amount < 0){
        std::cout<<"\nThat is not a valid amount!\n";
        return 0;
    }
    else{
        return amount;
    }
}