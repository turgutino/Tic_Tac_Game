
#include <iostream>
#include <windows.h>
using namespace std;


const string RESET = "\033[0m";
const string RED_BACKGROUND = "\033[41m";
const string BLUE_BACKGROUND = "\033[44m";
const string WHITE_BACKGROUND = "\033[47m";
const string RED_TEXT = "\033[31m";
const string BLUE_TEXT = "\033[34m";
const string WHITE_TEXT = "\033[37m";

void Print_Board(char**& board) {
    system("cls");
    cout << "Tic Tac Toe Board : " << endl;
    cout << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            string color;
            if (board[i][j] == 'X') color = BLUE_TEXT + WHITE_BACKGROUND;
            else if (board[i][j] == 'O') color = RED_TEXT + WHITE_BACKGROUND;
            else color = WHITE_BACKGROUND;

            cout << color << " " << board[i][j] << " " << RESET;
            if (j < 2) cout << "|";
        }
        cout << endl;
        if (i < 2) cout << "---|---|---" << endl;
    }
}

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void Delete_Board(char** board) {
    for (int i = 0; i < 3; ++i) {
        delete[] board[i];
    }
    delete[] board;
}

char Winner_Board(char**& board) {
    
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0];
    }
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i];
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2];
    return '/';
}

void Bot_Move(char** board) {
   
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                if (Winner_Board(board) == 'O') return;
                board[i][j] = ' ';
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'X';
                if (Winner_Board(board) == 'X') {
                    board[i][j] = 'O';
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                return;
            }
        }
    }
}

void User_Move(char** board, char player) {
    int n;
    cout << endl;
    cout << "Player " << player << ", make your move (1-9) : ";
    cin >> n;

    int row = (n - 1) / 3;
    int col = (n - 1) % 3;

    if (board[row][col] == ' ') {
        board[row][col] = player;
    }
    else {
        cout << endl;
        cout << "This spot is already taken. Choose another." << endl;;
        User_Move(board, player);
    }
}

void main() {
    char** board = new char* [3] {new char [3] {' ', ' ', ' '}, new char [3] {' ', ' ', ' '}, new char [3] {' ', ' ', ' '}};
    int Move_Count = 0;
    Print_Board(board);
    char player = 'X';

    while (true) {
        User_Move(board, player);
        Print_Board(board);
        Move_Count++;
        char Winner_Player = Winner_Board(board);
        if (Winner_Player == 'X' || Winner_Player == 'O') {
            setColor(Winner_Player == 'X' ? FOREGROUND_GREEN : FOREGROUND_RED);
            cout << endl;
            cout << "Winner: " << Winner_Player << "!" << endl;
            
            setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); 
            break;
        }
        else if (Move_Count == 9) {
            setColor(FOREGROUND_RED | FOREGROUND_GREEN); 
            cout << endl;
            cout << "The game is a draw!" << endl;
            setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); 
            break;
        }

        player = 'O';
        Bot_Move(board);
        Print_Board(board);
        Move_Count++;
        Winner_Player = Winner_Board(board);
        if (Winner_Player == 'X' || Winner_Player == 'O') {
            setColor(Winner_Player == 'X' ? FOREGROUND_GREEN : FOREGROUND_RED); 
            cout << endl;
            cout << "Winner: " << Winner_Player << "!" << endl;
            setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); 
            break;
        }
        else if (Move_Count == 9) {
            setColor(FOREGROUND_RED | FOREGROUND_GREEN); 
            cout << endl;
            cout << "The game is a draw!" << endl;
            setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); 
            break;
        }

        player = 'X';
    }

    Delete_Board(board);
}
    
