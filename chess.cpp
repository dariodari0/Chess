// important for VS
#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#endif


#ifndef BEGIN
#define BEGIN    "      A   B   C   D   E   F   G   H      \n"
#endif
#ifndef FRINGE
#define FRINGE   "    +---+---+---+---+---+---+---+---+   \n"
#endif
#ifndef EMPTY
#define EMPTY " |   |   |   |   |   |   |   |   | "
#endif
#ifndef END
#define END    "      A   B   C   D   E   F   G   H      \n"
#endif

const char startup[8][8] = { 'r', 'b', 'n', 'q', 'k', 'n', 'b', 'r', 'p', 'p','p','p','p','p','p', 'p', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'R', 'B', 'N', 'Q', 'K', 'N', 'B', 'R' };


using namespace std;

const int BOARD_SIZE = 8;

char board[BOARD_SIZE][BOARD_SIZE];


#ifdef _WIN32
void gotoXY(short x, short y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#else
void gotoXY(short x, short y)
{
	cout << "\033[" << y << ";" << x << "f" << flush;
}
#endif

void clearLine(short y)
{
	gotoXY(0, y);
	cout << setw(128) << " ";
	gotoXY(0, y);
}


void clearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}


void clearLinesFrom(short y, short count)
{
	for (short i = 0; i < count; i++)
		clearLine(y + i);
}


struct Move {
	char fromCh;
	int fromInt;
	char toCh;
	int toInt;
};


Move getMove() {

	Move move;
	string passd;
	char *temp;
	getline(cin, passd);


	istringstream iss(passd);
	iss >> move.fromCh;
	iss >> move.fromInt;
	iss >> move.toCh;
	iss >> move.toInt;

	move.fromCh = toupper(move.fromCh);
	move.toCh = toupper(move.toCh);


	return move;
}

//function validates the move whether it is within the chessboard
//letter >= A i <= H and number >= 1 <= 8
//and returns proper bool value
//struct Move {
//char fromCh;
//int fromInt;
//char toCh;
//int toInt; }
bool valid(Move m)
{

	if (m.fromCh < 'A' || m.fromCh >= 'A'+BOARD_SIZE) {
		return false;
	}
	else if (m.toCh < 'A' || m.toCh >= 'A'+BOARD_SIZE) {
		return false;
	}
	else if (m.fromInt < 1 || m.fromInt >= BOARD_SIZE) {
		return false;
	}
	else if (m.toInt < 1 || m.toInt >= BOARD_SIZE) {
		return false;
	}
	return true;
}


int translateLetter(char letter) {
	int result = letter - 'A';
	if (result >= 0 && result <8) {
		return result;
	}
	else
	{
		throw "Nie ma takiej kolumny";
	}

}

int translateInt(int number) {

	if (number < 0 && number > 8) {
		throw "Nie ma takiego numeru wiersza na szachownicy!";
	}
	number = number - 1;
	//mozna to zrobic sprytniej, ale tak jest czytelnie
	//zamieniam numery bo tablica ma odwrotnie numeracje niz to co sie wyswietla na szachownicy

	switch (number) {
	case 0:
		return 7;
	case 1:
		return 6;
	case 2:
		return 5;
	case 3:
		return 4;
	case 4:
		return 3;
	case 5:
		return 2;
	case 6:
		return 1;
	case 7:
		return 0;
	}
	//żeby kompilator nie darl sie, blad wychwyci walidacja
	return 100;

}


void makeMove(Move m, char board[][8])
{
	int columnFrom = translateLetter(m.fromCh);
	int columnTo = translateLetter(m.toCh);
	int rowFrom = translateInt(m.fromInt);
	int rowTo = translateInt(m.toInt);
	char figure = ' ';
	/*
	if (board[rowFrom][columnFrom] == ' ') {
		throw "Niepoprawny ruch, na polu startowym nie ma nic!";
	}
	if (board[rowTo][columnTo] != ' ') {
		throw "Niepoprawny ruch, pole docelowe jest zajęte!";
	}
	*/
	figure = board[rowFrom][columnFrom];
	board[rowFrom][columnFrom] = ' ';
	board[rowTo][columnTo] = figure;
	figure = ' ';

}


//displays board - takes array board[8][8]
// and reads its contents, and displays on the screen
void displayBoard(char board[][8])
{
	cout << BEGIN;
	cout << FRINGE;

	for (int i = 0; i<8; i++) {
		cout << " " << 8 - i << " ";
		for (int j = 0; j<8; j++) {
			cout << " " << "|" << " " << board[i][j];
		}
		cout << " " << "|" << " " << 8 - i << " ";
		cout << "\n";
		cout << FRINGE;

	}
	cout << END;
	cout << "\n";
}

//initializes board according to the following schema
//      A   B   C   D   E   F   G   H
//   +---+---+---+---+---+---+---+---+
// 8 | r | b | n | q | k | n | b | r | 8
//   +---+---+---+---+---+---+---+---+
// 7 | p | p | p | p | p | p | p | p | 7
//   +---+---+---+---+---+---+---+---+
// 6 |   |   |   |   |   |   |   |   | 6
//   +---+---+---+---+---+---+---+---+
// 5 |   |   |   |   |   |   |   |   | 5
//   +---+---+---+---+---+---+---+---+
// 4 |   |   |   |   |   |   |   |   | 4
//   +---+---+---+---+---+---+---+---+
// 3 |   |   |   |   |   |   |   |   | 3
//   +---+---+---+---+---+---+---+---+
// 2 | P | P | P | P | P | P | P | P | 2
//   +---+---+---+---+---+---+---+---+
// 1 | R | B | N | Q | K | N | B | R | 1
//   +---+---+---+---+---+---+---+---+
//      A   B   C   D   E   F   G   H
void initBoard(char board[][8])
{
	clearScreen();
	//rząd 8
	board[7][0] = 'R';
	board[7][1] = 'B';
	board[7][2] = 'N';
	board[7][3] = 'Q';
	board[7][4] = 'K';
	board[7][5] = 'N';
	board[7][6] = 'B';
	board[7][7] = 'R';
	//rząd 7
	for (int i = 0; i<8; i++) {
		board[6][i] = 'P';
	}
	//rzędy 6 - 3
	for (int i = 2; i<6; i++) {
		for (int j = 0; j<8; j++) {
			board[i][j] = ' ';
		}
	}

	//rząd 2
	for (int i = 0; i<8; i++) {
		board[1][i] = 'p';
	}

	//rząd 1
	board[0][0] = 'r';
	board[0][1] = 'b';
	board[0][2] = 'n';
	board[0][3] = 'q';
	board[0][4] = 'k';
	board[0][5] = 'n';
	board[0][6] = 'b';
	board[0][7] = 'r';
}


void doMove(char board[][8])
{
	cout << "Your move:" << endl << flush;
	Move m = getMove();

	while (!valid(m)) {
		clearLine(20);
		cout << "Error. Try again:" << endl << flush;
		m = getMove();
	}
	makeMove(m, board);
	
}


bool endOfGame(char board[][8])
{
	return false;
}

int main()
{
	initBoard(board);
	do {
		displayBoard(board);
		doMove(board);
		clearScreen();
	} while (!endOfGame(board));
}


/*
Player 1 i Player 2 ub black/white
druga validacja bool sprawdzajace czy dane pole jest juz zajete 
dopuszczamy mae i duze litery / zamiana malej i duzej litery
Funkcja usuwania spacji i liter z alfabetu dalej niz H
litera liczba itera liczba <-- VALID 


Homowork group: sprawdzamy black/white, sprawdzamy czy dana figura wykonuje poprawny ruch (zasady gry bez roszad) do niedzieli 

homowork individual: check another code (dwie, trzy poprawki zasugerowac)
biblioteki jak cos to tylko standardowe!!
*/