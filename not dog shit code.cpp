#include <iostream>
#include <map>
#include <string>

void makeGrid();
void DrawBoard();
void setPos(int num);
void getBoardState();
bool checkWin();

std::map<int,std::string> grid;
int pos;
char c;
bool activePlayer;
std::string boardState = "";

int main() {
    system("clear");
    system("setterm -cursor off");
    pos = 1;
    activePlayer = 0;
    makeGrid();
    while (1){
        std::cout << "It is currently Player " << activePlayer + 1 << "'s turn" << std::endl;
        DrawBoard();
        getBoardState();
        system("stty raw");
        c = getchar(); 
        system("stty cooked");
        if (c == 'A'){setPos(-3);}
        else if (c == 'B'){setPos(3);}
        else if (c == 'C'){setPos(1);}
        else if (c == 'D'){setPos(-1);}
        else if (c == 'q'){system("setterm -cursor on");system("stty cooked");return 1;}
        else if (c == 'x' && activePlayer == 0 && grid.at(pos) == "-"){grid.at(pos) = "X";activePlayer = 1;}
        else if (c == 'o' && activePlayer == 1 && grid.at(pos) == "-"){grid.at(pos) = "O";activePlayer = 0;}
        getBoardState();
        if (c == 'x' || c == 'o'){
            if (checkWin()){
                system("clear");
                DrawBoard();
                if (activePlayer){std::cout << "Player 1 wins!\n";}
                if (!activePlayer){std::cout << "Player 2 wins!\n";}
                system("stty cooked");
                system("setterm -cursor on");
                return 1;
            }
        }
        if (boardState.find("-") == std::string::npos){for (size_t i = 1; i < grid.size() + 1; i++){grid.at(i) = "-";}}
        system("clear");
    }
}

void DrawBoard(){
    for (size_t i = 1; i < grid.size() + 1; i++){
        if (i == pos){std::cout << "\033[" << 7 << ";" << 36 << "m" << grid.at(i) << "\033[0m";}
        else {std::cout << "\033[" << 0 << ";" << 36 << "m" << grid.at(i) << "\033[0m";}
        if (i % 3 == 0){std::cout << "\n";}
    }
}

void makeGrid(){
    for (size_t i = 1; i < 10; i++){grid.insert(std::pair<int,std::string>(i,"-"));}
}

void setPos(int num){
    pos = pos + num;
    if (pos > 9){pos = pos - 9;}
    if (pos < 1){pos = pos + 9;}
}

void getBoardState(){boardState = "";for (size_t i = 1; i < grid.size() + 1; i++){boardState = boardState + grid.at(i);}}

bool checkWin(){
    int hitsx = 0; int hitso = 0;
    std::string temp;
    std::string winStates[8] = {"123","456","789","147","258","369","159","357"};
    for (size_t i = 0; i < 8; i++){
        hitsx = 0; hitso = 0;
        for (size_t x = 0; x < 3; x++){temp = winStates[i][x];if (grid.at(std::stoi(temp)) == "X"){hitsx++;}}
        for (size_t x = 0; x < 3; x++){temp = winStates[i][x];if (grid.at(std::stoi(temp)) == "O"){hitso++;}}
        if (hitsx == 3){return 1;}
        if (hitso == 3){return 1;}
    }
    return 0;
}