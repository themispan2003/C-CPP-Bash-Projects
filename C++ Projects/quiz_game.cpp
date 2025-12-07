#include <iostream>

int main(){
    std::string questions[]={"1. What year was C++ created?: ",
                             "2. Who invented C++?: ",
                             "3. Whar is the predecessor of C++??: ",
                             "4. Is C++ a object-oriented programming language"};
    std::string options[][4]={{"A. 1969", "B. 1975","C. 1985", "D. 1989"},
                              {"A. Elon Musk","B. Bjarne Stroustrup","C. Dennis Ritchie","D. Jonas Djikstra"},
                              {"A. C","B. Pascal","C. Java","D. Combol"},
                              {"A. No","B. Yes", "C. I don't know", "D. I am not sure"}};
    char answerKey[]= {'C','B','A','B'};
    
    int size = sizeof(questions)/sizeof(questions[0]);
    char guess;
    int score; 

    for (int i=0;i<size;i++){
        std::cout<<'\n'<<questions[i]<<'\n';
        for(int j=0;j<sizeof(options[i])/sizeof(options[i][0]);j++){
            std::cout<<options[i][j]<<'\n';
        }
        std::cin>>guess;
        guess=toupper(guess);

        if (guess==answerKey[i]){
            std::cout<<"Correct !\n";
            score++;
        }
        else{
            std::cout<<"Wrong!\n";
            std::cout<<"Answer: "<< answerKey[i]<<'\n';
        }
    }

    std::cout<<"\n"<<"RESULTS\n";
    std::cout<<"CORRECT GUESSES\n";
    std::cout<<"# of QUESTIONS "<< size << '\n';
    std::cout<<"Score: "<<(score/(double)size)*100<<"%";
    
    return 0;
}