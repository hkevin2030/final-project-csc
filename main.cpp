/*
 * Author: Kevin Ho
 * Course: CSCD ####
 * Professor:
 * Description: Tic Tac Toe Game player vs AI
*/



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


/** main (int)
 * Initial program entry
 * @return  N/A
 */

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
                printBoard(gameboard);
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

/** initalBoard (void)
 * Initializes array with default values
 * @param array
 */

void initalBoard(int array[][boardSize]){
    for(int i = 0; i < boardSize; i++){
        for(int z = 0; z < boardSize; z++){
            array[i][z] = -1;
        }
    }
}

/** printBoard (void)
 * Prints the array to the screen with formatting
 * @param array
 */
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
        for(int y = 0; y < 12; y++){
            cout << "-";
        }
        cout << endl;
    }

}


/** userMove (void)
 * user inputs placement of 'X' on gameboard.
 * Function checks for invalid placement and input
 * @exception STOI conversion
 * @param array
 */
void userMove(int array[][boardSize]) {
    int user_Move = 2;
    string user_input, temp;
    int x = -1,y;

    cout << "Please enter the square location in this format (Ex: A1, B2): " << endl;
    cin >> user_input;

    // Converting values A = 0, B = 1, C = 2
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

    // Preventing program exception from conversion
    temp = user_input.at(1);
    try {
        y = stoi(temp);
    }
    catch (exception& exception) {
        cout << "Please try again, invalid input " << endl;
        userMove(array);
    }
    y = y - 1;
    if(y > 3 || y < 0){
        cout << "Please try again, invalid input " << endl;
        userMove(array);
    }

    if(array[y][x]  != -1){
        cout << "Square is already taken please try again!" << endl;
        userMove(array);
    }
    else{
        array[y][x] = user_Move;
    }

}

/** cpuMove (void)
 * CPU places 'O' to the array
 * Functions checks for invalid placement and overwrite protection
 * @param array
 */

void cpuMove(int array[][boardSize]) {

    for(int i =  0; i< boardSize; i++){
        for(int z = 0; z<boardSize; z++) {
            if (array[i][z] != -1){
                // If it not -1 continue
                // make sure opp. value can not be overwritten
                continue;
            }
            else{
                // else set  i,z to 1
                array[i][z] = 1;
                return;
            }
        }
    }

}

/** checkFullBoard (bool)
 * checks the array for all spots filled, if all spots all filled then return true, else false.
 * @param array
 * @return IF array full
 */

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

/** checkForGame  (bool)
 * Checks to see if the user or the CPU have a win, based on horizontal, vertical, and diagonal possibilities.
 * @param array
 * @return GAME WON
 */

bool checkForGame(int array[][boardSize]) {
    //keep count of owned squares
    int user_count = 0;
    int cpu_count = 0;

    /*
     * CHECK ROWS
     */
    for(int i = 0; i < boardSize; i++)
    {
        //make sure each row count is reset
        user_count = 0;
        cpu_count = 0;

        //columns
        for(int j = 0; j < boardSize; j++)
        {
            //if empty space, forget checking the rest
            if( array[i][j] == -1) {
                break;
            }
            else if (array[i][j] == 1) {
                cpu_count++;
            }
            else if (array[i][j] == 2) {
                user_count++;
            }
        }

        // check for winner based on rows
        if(user_count == 3 || cpu_count == 3) {
            if (user_count == 3){
                cout << "You won the game!" << endl;
            }
            else {
                cout << "CPU has won the game!" << endl;
            }
            return true;
        }
    }

    /*
     * CHECK COLUMNS
     */
    for(int j = 0; j < boardSize; j++)
    {
        user_count = 0;
        cpu_count = 0;

        //loop through rows
        for(int i = 0; i < boardSize; i++)
        {
            //if empty space, forget checking the rest
            if( array[i][j] == -1) {
                break;
            }
            else if (array[i][j] == 1) {
                cpu_count++;
            }
            else if (array[i][j] == 2) {
                user_count++;
            }
        }

        // Check winner based on columns
        if(user_count == 3 || cpu_count == 3) {
            if (user_count == 3){
                cout << "You won the game!" << endl;
            }
            else {
                cout << "CPU has won the game!" << endl;
            }
            return true;
        }
    }
    /*
     * CHECK DIAGONAL
     */

    //if not rows or columns win, check left to right diagonal
    user_count = 0;
    cpu_count = 0;
    for(int i = 0; i < boardSize; i++)
    {
        //if empty space, forget checking the rest
        if( array[i][i] == -1) {
            break;
        }
        else if (array[i][i] == 1) {
            cpu_count++;
        }
        else if (array[i][i] == 2) {
            user_count++;
        }
    }

    // check winner based on diagonal

    if(user_count == 3 || cpu_count == 3) {
        if (user_count == 3){
            cout << "You won the game!" << endl;
        }
        else {
            cout << "CPU has won the game!" << endl;
        }
        return true;
    }

    //check last diagonal right to left
    //make sure count is reset outside of the loop
    user_count = 0;
    cpu_count = 0;
    for(int i = 0, j = (boardSize - 1); i < boardSize; i++, j--)
    {
        // if empty space, forget checking the rest
        if( array[i][j] == -1) {
            break;
        }
        else if (array[i][j] == 1) {
            cpu_count++;
        }
        else if (array[i][j] == 2) {
            user_count++;
        }
    }

    // check winner based on diagonal opp.
    if(user_count == 3 || cpu_count == 3){
        if (user_count == 3){
            cout << "You won the game!" << endl;
        }
        else {
            cout << "CPU has won the game!" << endl;
        }
        return true;
    }
    //if we found no winning conditions
    return false;

}




