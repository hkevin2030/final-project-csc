//
// Created by mana0303 on 3/11/2021.
//



#include <iostream>
#include <istream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>

#define boardSize 3

using namespace std;

void initalBoard(int array[][boardSize]);

void printBoard(int array[][boardSize]);

void userMove(int array[][boardSize]);

void cpuMove(int array[][boardSize]);

bool checkFullBoard(int array[][boardSize]);

bool checkForGame(int array[][boardSize]);



int main (){

    int gameboard[boardSize][boardSize];
    initalBoard(gameboard);
    srand(time(0));
    string command;
    int random = (rand() % 2) +1;


    if (random == 1){
        cout << "On the coin flip CPU lost, you are first." << endl;
    }
    if (random == 2){
        cout << "On the coin flip CPU won, CPU already took its turn." << endl;
        cpuMove(gameboard);
        random = 1;
    }
    printBoard(gameboard);

    while (true){

        do {
            std::cout << "Enter Q for quit, P for print game, or C to continue turn: ";
            std::cin >> command;
        } while (command != "Q" && command != "P" && command != "C");

        if (command == "Q") {
            break;
        }

        if (command == "P") {
            printBoard(gameboard);
        }

        if (command == "C") {

            if(random == 1){
                userMove(gameboard);
            }
            cpuMove(gameboard);

            if (checkFullBoard(gameboard)) {
                break;
            }

            if (checkForGame(gameboard)) {
                printBoard(gameboard);
                break;
            }
        }

    }



    return 0;
}

void initalBoard(int array[][boardSize]){
    for(int i = 0; i < boardSize; i++){
        for(int z = 0; z < boardSize; z++){
            array[i][z] = -1;
        }
    }
}

void printBoard(int array[][boardSize]) {
    cout << setw(6) << "A" << setw(4)  << "B" << setw(4) << "C" << endl;

    for(int i = 0; i < boardSize; i++){
        cout << setw(3) << i+1 << " ";
        for (int z = 0; z < boardSize; z++){
            if (z == 3) {
                break;
            }
            if (array[i][z] == -1){
                cout << setw(2) <<  " " << setw(2) <<  "|";
            }

            if (array[i][z] == 2){
                cout << setw(2) <<  "X" << setw(2) <<  "|";
            }
            if (array[i][z] == 1){
                cout << setw(2) <<  "O" << setw(2) <<  "|";
            }

        }
        cout << endl;
        cout << setw(5);
        for(int y = 0; y < 10; y++){
            cout << "-";
        }
        cout << endl;
    }

}

void userMove(int array[][boardSize]) {
    int user_Move = 2;
    string user_input, temp;
    int x = -1,y;

    cout << "Please enter the square placement in this format: 'A1' for the top corner square for example: " << endl;
    cin >> user_input;

    if(user_input.at(0) == 'A'){
         x = 0;
    }
    else if (user_input.at(0) == 'B'){
        x = 1;
    }
    else if (user_input.at(0) == 'C'){
        x = 2;
    }
    else{
        cout << "Please try again, invalid input" << endl;
        userMove(array);
    }

    temp = user_input.at(1);

    y = stoi(temp);

    if(y > 3 || y < 0){
        cout << "Please try again, invalid input " << endl;
        userMove(array);
    }

    y = y - 1;
    if(array[y][x]  != -1){
        cout << "Square is already taken please try again!" << endl;
        userMove(array);
    }
    else{
        array[y][x] = user_Move;
    }

}

void cpuMove(int array[][boardSize]) {

    for(int i =  0; i< boardSize; i++){
        for(int z = 0; z<boardSize; z++) {
            if (array[i][z] != -1){
                continue;
            }
            else{
                array[i][z] = 1;
                return;
            }
        }
    }

}

bool checkFullBoard(int array[][boardSize]) {
    int counter = 0;
    for(int i = 0;  i< boardSize; i++){
        for(int x = 0; x < boardSize; x++){
            if(array[i][x] != -1){
                counter++;
            }
        }
    }
    if(counter == 9){
        cout << "Game over! Game board is full!" << endl;
        return true;
    }
    return false;
}

bool checkForGame(int array[][boardSize]) {

    int countX = 0;
    int countO = 0;

    // Check rows

    for (int i = 0; i < boardSize; i++) {
        countX = 0;
        countO = 0;

        for (int j = 0; j < boardSize; j++) {
            if (array[i][j] == -1)
                break;
            else if (array[i][j] == 1)
                countO++;
            else if (array[i][j] == 2)
                countX++;
        }
    }

    if (countX == 3 || countO == 3) {
        if (countX == 3) {
            cout << "You have won the game!" << endl;
        } else {
            cout << "CPU has won the game!" << endl;
        }
        return true;
    }

    //check columns
    for (int j = 0; j < boardSize; j++) {

        countX = 0;
        countO = 0;

        for (int i = 0; i < boardSize; i++) {

            if (array[i][j] == -1)
                break;
            else if (array[i][j] == 1)
                countO++;
            else if (array[i][j] == 2)
                countX++;
        }
    }

    //did we find a winner?
    if (countX == 3 || countO == 3) {
        if (countX == 3) {
            cout << "You have won the game!" << endl;
        } else {
            cout << "CPU has won the game!" << endl;
        }
        return true;
    }


    countX = 0;
    countO = 0;
    for (int i = 0; i < boardSize; i++) {

        if (array[i][i] == '.')
            break;
        else if (array[i][i] == 1)
            countO++;
        else if (array[i][i] == 2)
            countX++;
    }

    //did we find a winner?
    if (countX == 3 || countO == 3) {
        if (countX == 3) {
            cout << "You have won the game!" << endl;
        } else {
            cout << "CPU has won the game!" << endl;
        }
        return true;
    }

    countX = 0;
    countO = 0;
    for (int i = 0, j = (boardSize - 1); i < boardSize; i++, j--) {
        if (array[i][j] == -1)
            break;
        else if (array[i][j] == 1)
            countO++;
        else if (array[i][j] == 2)
            countX++;
    }

    //did we find a winner?
    if (countX == 3 || countO == 3) {
        if (countX == 3) {
            cout << "You have won the game!" << endl;
        } else {
            cout << "CPU has won the game!" << endl;
        }
        return true;
    }
    //if we found no winning conditions
    return false;

}



