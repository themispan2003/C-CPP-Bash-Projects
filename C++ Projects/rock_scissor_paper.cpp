#include <iostream>
#include <ctime>

char get_user_choice();
char get_computer_choice();
void show_choice(char choice);
char choose_winner(char player, char computer);

int main(){

    char player;
    char computer;
    char cont;
    char sc;
    int w=0;
    int l=0;
    int t =0;
    do {
    player = get_user_choice();
    std::cout<<"\nYour choice: ";
    show_choice(player);
    computer = get_computer_choice();
    std::cout<<"Computer's choice: ";
    show_choice(computer);

    sc = choose_winner(player,computer);

    if(sc == 'w'){
        w++;
    }
    else if(sc == 'l'){
        l++;
    }
    else{
        w++;
        l++;
    }

    std::cout<<"Enter c if you want to continue!\n";
    std::cin>>cont;
    }while(cont =='c');

    std::cout<< "\nYou: "<<w<<"- Computer: "<<l;
    return 0;
}

char get_user_choice(){
    char player;
    std::cout<<"\nRock-Scissor-Paper Game!\n";
    do {
    std::cout<<"Choose an option:\n";
    std::cout<<"'r' for rock!\n";
    std::cout<<"'s' for scissors!\n";
    std::cout<<"'p' for paper!\n\n";
    std::cin>>player;
    }while (player!='r' && player!='s' && player!='p');

    return player;
}

char get_computer_choice(){
    srand(time(0));
    int num = (rand() %3) + 1;

    switch(num){
        case 1:
            return 'r';
        case 2:
            return 's';
        case 3:
            return 'p';
        }
        return '0';
}

void show_choice(char choice){
    switch(choice){
        case 'r':
            std::cout<<"Rock\n";
            break;
        case 's':
            std::cout<<"Scissors\n";
            break;
        case 'p':
            std::cout<<"Paper\n";
            break;
    }
}

char choose_winner(char player, char computer){

    switch (player)
    {
    case 'r':
        if(computer == 'r'){
            std::cout<<"It is a tie.\n";
        }
        else if(computer == 's'){
            std::cout<<"You won!\n";
            return 'w';
        }
        else{
            std::cout<<"You lost!\n";
            return 'l';
        }
        break;
    case 's':
        if(computer == 'r'){
            std::cout<<"You lost!\n";
            return 'l';
        }
        else if(computer == 's'){
            std::cout<<"It is a tie!\n";
        }
        else{
            std::cout<<"You won!\n";
            return 'w';
        }
        break;
    case 'p':
        if(computer == 'r'){
            std::cout<<"You won .\n";
            return 'w';
        }
        else if(computer == 's'){
            std::cout<<"You lost!\n";
            return 'l';
        }
        else{
            std::cout<<"It is a tie!\n";
        }
        break;
    }
    return 's';
}