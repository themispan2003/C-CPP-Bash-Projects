#include <iostream>
#include <ctime>

int main(){
    srand(time(0));
    int randonNum = (rand()%5)+1;
    switch (randonNum)
    {
    case  1:
        std::cout<<"Kerdises ena sticker!\n";
        break;
    case  2:
        std::cout<<"Kerdises ena pagwto!\n";
        break;
    case  3:
        std::cout<<"Kerdises ena t-shirt!\n";
        break;
    case  4:
        std::cout<<"Kerdises ena mixanaki!\n";
        break;
    case  5:
        std::cout<<"Kerdises ena aytokinhto!\n";
        break;
    default:
        break;
    }
    return 0;
}