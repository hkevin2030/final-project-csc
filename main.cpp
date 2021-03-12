//
// Created by mana0303 on 3/11/2021.
//

#include <iostream>
#include <istream>
#include <iomanip>
#include <time.h>
#define array_size 3

//


void InitialGrid(int n[][array_size]){
    for (int i = 0; i < array_size ; ++i) {
        for(int z = 0; z < array_size; z++){
            n[i][z] =  -1;
        }
    }
}



void PrintGrid(int n[][array_size]){

    std::cout << std::setw(6) << "A" << std::setw(4)  << "B" << std::setw(4) << "C" << std::endl;

    for(int i = 0; i < array_size; i++){
        std::cout << std::setw(3) << i+1;
        for (int z = 0; z < array_size; z++){
            if (z == 2) {
                break;
            }
            if (n[i][z] == -1){
                std::cout << std::setw(1) <<  " " << std::setw(3) <<  "|";
            }

            if (n[i][z] == 2){
                std::cout << std::setw(1) <<  "X" << std::setw(3) <<  "|";
            }
            if (n[i][z] == 1){
                std::cout << std::setw(1) <<  "O" << std::setw(3) <<  "|";
            }

        }
        std::cout << std::endl;
        std::cout << std::setw(5);
        for(int y = 0; y < 10; y++){
            std::cout << "-";
        }
        std::cout << std::endl;
    }

}


bool isLocation_Clear(int row, int column, int n[][array_size]){
//    User is places 2 on array (X)
//    Computer is places 1 on array (O)
    return (n[row][column] != -1);
}

bool FireShot(int row, int column, int n[][array_size], int outcome_status){

    if(isLocation_Clear(row, column, n)){
        n[row][column] = outcome_status;
        return true;
    }

    return false;
}

bool CheckGame(){
    return false;
}

bool userTakeTurn(){
    std::string user_input;
    enum {
        A = 0,
        B = 1,
        C = 2,
    };
    std::cout << "Enter location: ";
    std::cin >> user_input;
    return false;
}

bool AITakeTurn(int n[][array_size]){

    int x, y;
    x = rand() % 2 + 0;
    y = rand() % 2 + 0;
   if(FireShot(0, 1, n, 1)){
       return true;
   }
    return false;
}



int main(){
    int game_board[array_size][array_size];
    std::string mode, command, exit;

    InitialGrid(game_board);
    srand(time(NULL));
    long chance = (rand() % (2 - 1 + 1)) + 1;


    while (true) {
        do {
            std::cout << "Enter Q for quit, P for print grid, or F for play turn: ";
            std::cin >> command;
        } while (command != "Q" && command != "P" && command != "F");

        if (command == "Q") {
            break;
        }

        if (command == "P") {
            PrintGrid(game_board);
        }

        if(command == "F"){
            AITakeTurn(game_board);
        }

    }





    return 0;
}