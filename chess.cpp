//     A   B   C   D   E   F   G   H
//   +---+---+---+---+---+---+---+---+
// 8 | r | n | b | q | k | b | n | r | 8
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
// 1 | R | N | B | Q | K | B | N | R | 1
//   +---+---+---+---+---+---+---+---+
//     A   B   C   D   E   F   G   H


//LIBRARIES --------------------------------------------------------------------------------------
// important for VS
//#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

namespace ErrorMessage {
	enum ErrorMessageTypes {
		badFormat,
		emptySpaceSelected,
		wrongColorSelected,
		badPieceMovement,
		squareIsOccupied
	};
}

using namespace std;

//CONSTANTS ----------------------------------------------------------------------------------------
const int BOARD_SIZE = 8;


//GLOBAL VARIABLES ---------------------------------------------------------------------------------

char board[BOARD_SIZE][BOARD_SIZE] = { ' ' };
const char startup[8][8] = { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r', 'p', 'p','p','p','p','p','p', 'p', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' };
bool whites;

struct Move {
	char fromCh;
	int fromInt;
	char toCh;
	int toInt;

	void Fill(char fromCh, int fromInt, char toCh, int toInt) {
		this->fromCh = fromCh;
		this->fromInt = fromInt;
		this->toCh = toCh;
		this->toInt = toInt;
	}

};

//GLOBAL FUNCTIONS ---------------------------------------------------------------------------------

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

//function so far is never used
/*
void clearLinesFrom(short y, short count)
{
for (short i = 0; i < count; i++)
clearLine(y + i);
}
*/


//removes spaces from char*
void removeSpaces(char* s)
{
	char* s2 = s;
	do {
		if (*s2 != ' ')
			*s++ = *s2;
	} while (*s2++);
}

//jawna translacja litery ze struktury Move do wsp�rz�dnych u�ywanych na szachownicy
int translateLetter(char letter) {
	int result = letter - 'A';
	if (result >= 0 && result < BOARD_SIZE) {
		return result;
	}
	return -1;

}


//jawna transalcja cyfry ze struktury Move do wsp�rz�dnych u�ywanych na szachownicy
int translateInt(int number) {

	if (number < 1 && number > BOARD_SIZE) {
		cout << "Nie ma takiego numeru wiersza na szachownicy!" << endl << flush;
		return -1;
	}
	//change numbering of rows - in MOVE struct there was numbering from 1 to BOARD_SIZE
	//we change it initially to numbering from 0 to BOARD_SIZE - 1
	//reverse numbers of rows to correctly address the array board
	return BOARD_SIZE - number;
}

int inverseTranslateInt(int x) {
	return BOARD_SIZE - x;
}

char inverseTranslateCh(int x) {
	return x + 'A';
}



void errorMessage(ErrorMessage::ErrorMessageTypes msg)
{
	switch (msg) {

	case ErrorMessage::badFormat:
		clearLine(20);
		cout << "Wrong coordinate format!" << endl << flush;
		break;
	case ErrorMessage::emptySpaceSelected:
		clearLine(20);
		cout << "No pawn on this square" << endl << flush;
		break;
	case ErrorMessage::wrongColorSelected:
		clearLine(20);
		cout << "This is not your pawn!" << endl << flush;
		break;
	case ErrorMessage::badPieceMovement:
		clearLine(20);
		cout << "This piece cannot do such movement!" << endl << flush;
		break;
	case ErrorMessage::squareIsOccupied:
		clearLine(20);
		cout << "Your pawn already occupies this field!" << endl << flush;
		break;
	default:
		clearLine(20);
		cout << "Error!" << endl << flush;

	}
}


// Check if proper pawn is selected or space is empty
bool isPieceSelected(const Move &m, char board[][BOARD_SIZE], bool whites) {

	char piece = board[translateInt(m.fromInt)][translateLetter(m.fromCh)];

	if (piece >= 'a' && piece <= 'z') {
		if (whites == true) {
			errorMessage(ErrorMessage::wrongColorSelected);
			return false;
		}
	}

	if (piece >= 'A' && piece <= 'Z') {
		if (whites == false) {
			errorMessage(ErrorMessage::wrongColorSelected);
			return false;
		}
	}

	if (piece == ' ') {
		errorMessage(ErrorMessage::emptySpaceSelected);
		return false;
	}


	return true;
}

// Check is pawn can enter selected square
bool isSquareAvailable(const Move &m, char board[][BOARD_SIZE], bool whites) {

	char piece = board[translateInt(m.toInt)][translateLetter(m.toCh)];

	if (piece >= 'a' && piece <= 'z') {
		if (whites == false) {
			errorMessage(ErrorMessage::squareIsOccupied);
			return false;
		}
	}
	else if (piece >= 'A' && piece <= 'Z') {
		if (whites == true) {
			errorMessage(ErrorMessage::squareIsOccupied);
			return false;
		}
	}

	return true;
}

bool valid(int x, int y) {
	if (x<0 || x >= BOARD_SIZE || y<0 || y >= BOARD_SIZE) {
		return false;
	}
	return true;
}

bool valid(Move m) {

	if (m.fromCh < 'A' || m.fromCh >= 'A' + BOARD_SIZE) {
		return false;
	}
	else if (m.toCh < 'A' || m.toCh >= 'A' + BOARD_SIZE) {
		return false;
	}
	else if (m.fromInt < 1 || m.fromInt > BOARD_SIZE) {
		return false;
	}
	else if (m.toInt < 1 || m.toInt > BOARD_SIZE) {
		return false;
	}
	return true;
}


//figure functions declarations
bool pawn(const Move &m, char board[][BOARD_SIZE]);
bool pPawn(const Move &m, char board[][BOARD_SIZE]);
bool king(const Move &m, char board[][BOARD_SIZE]);
bool rook(const Move &m, char board[][BOARD_SIZE]);
bool bishop(const Move &m, char board[][BOARD_SIZE]);
bool queen(const Move &m, char board[][BOARD_SIZE]);
bool knight(const Move &m, char board[][BOARD_SIZE]);

bool pawn(const Move &m, char board[][BOARD_SIZE]) {

	//czy gra bia�y czy czarny

	//czy pionek nale�y do odpowiedniego gracza

	//czy pionek nie mo�e szachowa� kr�la przeciwnika

	//czy pionek wykonuje sw�j pierwszy ruch w grze, wtedy moze i�� do przodu o 2 pola lub 1 pole - do przodu lub po skosie

	//je�eli pionek ju� nie jest na swojej pozycji startowej to rusza si� o 1 pole

	//je�eli pionek doszed� do ko�ca szachownicy to staje si� pp albo PP - pionkiem kt�ry mo�e chodzi� do ty�u

	//pionek nie mo�e przeskakiwa� w�asnych figur ani pion�w

	return true;
}

bool pPawn(const Move &m, char board[][BOARD_SIZE]) {



	//czy gra bialy czy czarny

	//czy pionek nalezy do wlasciwego gracza

	//czy pionek nie mo�e szachowa� kr�la przeciwnika

	//pionek mo�e robi� ruch tylko o 1 pole ale mo�e chodzi� te� do ty�u, nie mo�e przeskakiwa� w�asnych figur ani pion�w

	return true;
}
bool is_Deadlocked(const Move &m, char board[][BOARD_SIZE], bool whites) {
	//this function checks if the king is deadlocked(to be used in king's move validation[king])


	// from now on we'll be checking possible moves according to king's destiny position
	int toInt = m.toInt;
	char toCh = m.toCh;

	Move m_Pawn;
	Move m_pPawn;
	Move m_King;
	Move m_Rook;
	Move m_Bishop;
	Move m_Queen;
	Move m_Knight;

	char figure;

	for (int i = 0; i<BOARD_SIZE; i++) { //setting up the Move structures for each enemy figure
		for (int j = 0; j<BOARD_SIZE; j++) {
			figure = board[i][j];

			if (whites) {
				if (figure == 'p') m_Pawn.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'p') m_pPawn.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'k') m_King.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'r') m_Rook.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'b') m_Bishop.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'q') m_Queen.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'n') m_Knight.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
			}

			if (!whites) {
				if (figure == 'P') m_Pawn.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'P') m_pPawn.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'K') m_King.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'R') m_Rook.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'B') m_Bishop.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'Q') m_Queen.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'N') m_Knight.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
			}

		}
	}

	//returns true if any figure can move into kings destiny position->this means king is deadlocked
	if (pawn(m_Pawn, board))
		return true;
	else if (pPawn(m_pPawn, board))
		return true;
	else if (king(m_King, board))
		return true;
	else if (rook(m_Rook, board))
		return true;
	else if (bishop(m_Bishop, board))
		return true;
	else if (queen(m_Queen, board))
		return true;
	else if (knight(m_Knight, board))
		return true;

	return false;
}

bool king(const Move &m, char board[][BOARD_SIZE]) {

	//czy gra bia�y czy czarny

	//czy kr�l nale�y do w�a�ciwego gracza

	//czy pionek nie mo�e szachowa� kr�la przeciwnika

	//czy analizowany ruch jest dost�pny dla kr�la

	//kr�l mo�e si� porusza� o 1 pole, byle nie wyj�� za szachownic�, dowolny kierunek, nie mo�e przeskakiwa� w�asnych pion�w ani figur


	//step one- checking if the move is within king's range
	if (m.toCh == m.fromCh + 1 && m.toInt == m.fromInt) {
		if (valid(translateLetter(m.fromCh) + 1, translateInt(m.fromInt))) {
			if (!is_Deadlocked(m, board, whites)) return true; //step two- checking if king is deadlocked
		}
		return false;
	}

	if (m.toCh == m.fromCh  && m.toInt == m.fromInt + 1) {
		if (valid(translateLetter(m.fromCh), translateInt(m.fromInt) + 1)) {
			if (!is_Deadlocked(m, board, whites)) return true;
		}
		return false;
	}

	if (m.toCh == m.fromCh + 1 && m.toInt == m.fromInt + 1) {
		if (valid(translateLetter(m.fromCh) + 1, translateInt(m.fromInt) + 1)) {
			if (!is_Deadlocked(m, board, whites)) return true;
		}
		return false;
	}

	if (m.toCh == m.fromCh - 1 && m.toInt == m.fromInt) {
		if (valid(translateLetter(m.fromCh) - 1, translateInt(m.fromInt))) {
			if (!is_Deadlocked(m, board, whites)) return true;
		}
		return false;
	}

	if (m.toCh == m.fromCh  && m.toInt == m.fromInt - 1) {
		if (valid(translateLetter(m.fromCh), translateInt(m.fromInt) - 1)) {
			if (!is_Deadlocked(m, board, whites)) return true;
		}
		return false;
	}

	if (m.toCh == m.fromCh - 1 && m.toInt == m.fromInt - 1) {
		if (valid(translateLetter(m.fromCh) - 1, translateInt(m.fromInt) - 1)) {
			if (!is_Deadlocked(m, board, whites)) return true;
		}
		return false;
	}

	if (m.toCh == m.fromCh - 1 && m.toInt == m.fromInt + 1) {
		if (valid(translateLetter(m.fromCh) - 1, translateInt(m.fromInt) + 1)) {
			if (!is_Deadlocked(m, board, whites)) return true;
		}
		return false;
	}

	if (m.toCh == m.fromCh + 1 && m.toInt == m.fromInt - 1) {
		if (valid(translateLetter(m.fromCh) + 1, translateInt(m.fromInt) - 1)) {
			if (!is_Deadlocked(m, board, whites)) return true;
		}
		return false;
	}

	return false;
}



bool rook(const Move &m, char board[][BOARD_SIZE]) {

	int char_diff = abs(m.toCh - m.fromCh);
	int int_diff = abs(m.toInt - m.fromInt);

	if (m.fromCh != m.toCh && m.fromInt != m.toInt)
		return false;

	if (m.fromCh > m.toCh) {
		for (int i = 1; i < char_diff; ++i) {
			if (board[translateInt(m.fromInt)][translateLetter(m.fromCh) - i] != ' ')
				return false;
		}
	}
	if (m.fromCh < m.toCh) {
		for (int i = 1; i < char_diff; ++i) {
			if (board[translateInt(m.fromInt)][translateLetter(m.fromCh) + i] != ' ')
				return false;
		}
	}
	if (m.fromInt > m.toInt) {
		for (int i = 1; i < int_diff; ++i) {
			if (board[translateInt(m.fromInt) + i][translateLetter(m.fromCh)] != ' ')
				return false;
		}
	}
	if (m.fromInt < m.toInt) {
		for (int i = 1; i < int_diff; ++i) {
			//cout << (board[translateInt(m.fromInt) + i][translateLetter(m.fromCh)] != ' ' )<< endl;
			if (board[translateInt(m.fromInt) - i][translateLetter(m.fromCh)] != ' ')
				return false;
		}
	}

	return true;
}

bool bishop(const Move& m, char board[][BOARD_SIZE]) {

	int char_diff = (m.toCh - m.fromCh); //calculates the vertical shift
	int int_diff = (m.toInt - m.fromInt); //calculates the horizontal shift

										  //basically in case of bishop the absolute value of vertical and horizontal shifts must be equal(diagonal move)
	if (abs(char_diff) != abs(int_diff))
		return false;

	else if (int_diff>0 && char_diff>0) {
		for (int i = 1; i<abs(char_diff); i++) {
			if (board[translateInt(m.fromInt) - i][translateLetter(m.fromCh) + i] != ' ')
				return false;
		}
	}

	else if (int_diff<0 && char_diff<0) {
		for (int i = 1; i<abs(char_diff); i++) {
			if (board[translateInt(m.fromInt) + i][translateLetter(m.fromCh) - i] != ' ')
				return false;
		}
	}

	else if (int_diff<0 && char_diff>0) {
		for (int i = 1; i<abs(char_diff); i++) {
			if (board[translateInt(m.fromInt) + i][translateLetter(m.fromCh) + i] != ' ')
				return false;
		}
	}

	else if (int_diff>0 && char_diff<0) {
		for (int i = 1; i<abs(char_diff); i++) {
			if (board[translateInt(m.fromInt) - i][translateLetter(m.fromCh) - i] != ' ')
				return false;
		}
	}

	return true;
}


bool queen(const Move &m, char board[][BOARD_SIZE]) {
	if (rook(m, board) || bishop(m, board))
		return true;
	else
		return false;
}



bool knight(const Move &m, char board[][BOARD_SIZE]) {

	if ((translateLetter(m.fromCh) == translateLetter(m.toCh) + 1) || (translateLetter(m.fromCh) == translateLetter(m.toCh) - 1)) {
		if ((translateInt(m.fromInt) == translateInt(m.toInt) + 2) || (translateInt(m.fromInt) == translateInt(m.toInt) - 2)) {
			return true;
		}
	}
	if ((translateLetter(m.fromCh) == translateLetter(m.toCh) + 2) || (translateLetter(m.fromCh) == translateLetter(m.toCh) - 2)) {
		if ((translateInt(m.fromInt) == translateInt(m.toInt) + 1) || (translateInt(m.fromInt) == translateInt(m.toInt) - 1)) {
			return true;
		}
	}

	return false;
}



// Ta funkcja sprawdza czy ruch jest poprawny pod k�tem:
// - czy na polu startowym jest moja figura
// - czy pole docelowe jest wolne lub czy stoi na nim figura przeciwnika
// - czy ruch dla danej figury jest dopuszczalny (pomijamy roszad�, ale nalezy uwzgl�dni�, �e pierwszy ruch ka�dego piona mo�e by� o dwie pozycje do przodu)



bool valid(const Move& m, char board[][BOARD_SIZE], bool whites)
{
	char piece = board[translateInt(m.fromInt)][translateLetter(m.fromCh)];

	if (!(isPieceSelected(m, board, whites))) {
		return false;
	}

	if (!(isSquareAvailable(m, board, whites)))
		return false;

	switch (tolower(piece)) {

	case 'p':
		if (!(pawn(m, board))) {
			errorMessage(ErrorMessage::badPieceMovement);
			return false;
		}
		break;
	case 'r':
		if (!(rook(m, board))) {
			errorMessage(ErrorMessage::badPieceMovement);
			return false;
		}
		break;
	case 'n':
		if (!(knight(m, board))) {
			errorMessage(ErrorMessage::badPieceMovement);
			return false;
		}
		break;
	case 'b':
		if (!(bishop(m, board))) {
			errorMessage(ErrorMessage::badPieceMovement);
			return false;
		}
		break;
	case 'q':
		if (!(queen(m, board))) {
			errorMessage(ErrorMessage::badPieceMovement);
			return false;
		}
		break;
	case 'k':
		if (!(king(m, board))) {
			errorMessage(ErrorMessage::badPieceMovement);
			return false;
		}
		break;

	}

	return true;
}






// Sprawdza czy linia jest w postaci litera liczba litera liczba oraz zamienia litery ma�e na wielkie, ewentualnie usuwa tak�e spacje np. c    1    D 3 zmiania na C1D3
bool valid(char line[])
{
	int length = 0;
	int i = 0, i1 = 0;
	removeSpaces(line);

	//length of array with characters
	while (line[length] != '\0') {
		length++;
	}

	//replace small letters into capital letters, no verification yet as to whether it is within BOARD_SIZE
	for (int j = 0; j<length; j++) {
		if (line[j] >= 'a' && line[j] <= 'z') {
			line[j] = toupper(line[j]);
		}
	}

	while (line[i] >= 'A' && line[i] <= 'Z') {
		i++;
	}

	if (i == 0) {
		errorMessage(ErrorMessage::badFormat);
		return false;
	}
	else {
		i1 = i;
	}

	while (line[i] >= '0' && line[i] <= '9') {
		i++;
	}

	if (i == i1) {
		errorMessage(ErrorMessage::badFormat);
		return false;
	}
	else
	{
		i1 = i;
	}

	while (line[i] >= 'A' && line[i] <= 'Z') {
		i++;
	}

	if (i == i1) {
		errorMessage(ErrorMessage::badFormat);
		return false;
	}
	else {
		i1 = i;
	}

	while (line[i] >= '0' && line[i] <= '9') {
		i++;
	}

	if (i == i1) {
		errorMessage(ErrorMessage::badFormat);
		return false;
	}
	else
	{
		return true;
	}


}



// zamienia ciag znak�w w postaci litera liczba litera liczba na struktur� Move
Move readMove(const char line[])
{
	char fromChars[20] = { ' ' };
	char toChars[20] = { ' ' };
	int fromInt = 0;
	int toInt = 0;
	int counter = 0;
	int i = 0;


	//read first symbol (letters)
	while (line[i] >= 'A' && line[i]<'Z') {
		if (line[i] == ' ') {
			i++;
		}
		fromChars[counter] = line[i];
		counter++;
		line++;
	}

	//read second symbol (integer)
	while (line[i] >= '0' && line[i]<'9') {
		if (line[i] == ' ') {
			i++;
		}
		fromInt = fromInt * 10 + (line[i] - '0');
		i++;
	}

	counter = 0;
	//read third symbol (letters)
	while (line[i] >= 'A' && line[i]<'Z') {
		if (line[i] == ' ') {
			i++;
		}
		toChars[counter] = line[i];
		counter++;
		i++;
	}

	//read fourth symbol (integer)
	while (line[i] >= '0' && line[i]<'9') {
		if (line[i] == ' ') {
			i++;
		}
		toInt = toInt * 10 + (line[i] - '0');
		i++;
	}

	Move move;
	strcpy(&move.fromCh, fromChars);
	move.fromInt = fromInt;
	strcpy(&move.toCh, toChars);
	move.toInt = toInt;

	return move;
}

Move getMove()
{
	Move m;
	string line;
	char lineStr[1024];
	do {
		getline(cin, line);
		strcpy(lineStr, line.c_str());
	} while (!valid(lineStr) || !valid((m = readMove(lineStr))));
	return m;
}



void makeMove(Move m, char board[][BOARD_SIZE])
{
	char figure = board[translateInt(m.fromInt)][translateLetter(m.fromCh)];
	board[translateInt(m.fromInt)][translateLetter(m.fromCh)] = ' ';
	board[translateInt(m.toInt)][translateLetter(m.toCh)] = figure;
}


//displays board - takes array board[BOARD_SIZE][BOARD_SIZE]
// and reads its contents, and displays on the screen
void displayBoard(char board[][BOARD_SIZE])
{
	//variable letter is used in a loop to display letters representing columns
	//the loop automatically displays chars, simpler loops returned intergers instead of chars

	char letter;
	int i, j;
	char k;

	//row with letters that reprezenting headers of columns
	cout << "   ";
	for (letter = 'A'; letter < 'A' + BOARD_SIZE; letter++)
		cout << "   " << letter;
	cout << "      \n";

	//row with a delimited in a chessboard  "    +---+---+---+---+---+---+---+---+   \n";
	cout << "    ";
	for (i = 'A'; i<'A' + BOARD_SIZE; i++) {
		cout << "+---";
	}
	cout << "+   \n";

	//now we take the array that keeps actual positions of figures and display it on the chessboard

	for (i = 0; i < BOARD_SIZE; i++) {

		cout << " " << BOARD_SIZE - i << " ";

		for (j = 0; j < BOARD_SIZE; j++) {
			cout << " " << "|" << " " << board[i][j];
		}
		cout << " " << "|" << " " << BOARD_SIZE - i << " ";
		cout << "\n";


		//now we delimit each row with figures with a delimiter "    +---+---+---+---+---+---+---+---+   \n";
		cout << "    ";
		for (k = 'A'; k<'A' + BOARD_SIZE; k++) {
			cout << "+---";
		}
		cout << "+   \n";

	}

	//finally the bottom letters

	//row with letters that reprezenting headers of columns
	cout << "   ";
	for (letter = 'A'; letter < 'A' + BOARD_SIZE; letter++)
		cout << "   " << letter;
	cout << "      \n\n";

}


void initBoard(char board[][BOARD_SIZE])
{
	clearScreen();

	int i, j;
	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			board[i][j] = startup[i][j]; //setup starting position
		}
	}
}


void doMove(char board[][BOARD_SIZE], bool whites)
{
	cout << "Your move:" << endl << flush;

	Move m;
	do {
		do {
			m = getMove();
		} while (!valid(m));
	} while (!valid(m, board, whites));
	makeMove(m, board);

}

bool endOfGame(char board[][BOARD_SIZE])
{
	return false;
}

int main()
{
	initBoard(board);
	whites = true;
	do {
		displayBoard(board);
		doMove(board, whites);
		whites = !whites;
		clearScreen();
	} while (!endOfGame(board));

}
