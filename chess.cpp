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

/*
TODO:
Dostosować funkcję is_Deadlocked(), powinna się tym zająć osoba która sworzyła funkcję

Dostosować funkcję readMove(), w ten sposób że powinna przyjmować string i na nim operować. 
Zmienna Move powinna zostać stworzona przez konstruktor do którego podaje się string w formie: A2B4 (jedyna akceptowalna forma końcowa)

Przeciążyć operator () tak aby mógł załadować 2 zmienny int które będą odpowiadać zmiennym koordynatów Move

Zastiąpić wszystkie operatory dostępu do tablicy przez nowy operator

Dalej trzeba przetestować czy wszystko działa :D, pewnie nie
*/




//LIBRARIES --------------------------------------------------------------------------------------
// important for VS
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif


//NAMESPACES ----------------------------------------------------------------------------------------

using namespace std;


// Will be upgraded if necessary
namespace ErrorMessage {
	enum ErrorMessageTypes {
		badFormat,
		emptySpaceSelected,
		wrongColorSelected,
		badPieceMovement,
		movementOverFigure,
		squareIsOccupied
	};
}

//CONSTANTS ----------------------------------------------------------------------------------------
const int BOARD_SIZE = 8;


//GLOBAL VARIABLES ---------------------------------------------------------------------------------

//char board[BOARD_SIZE][BOARD_SIZE] = { ' ' };


struct Coord {
	int x;
	int y;
};

struct Move {
	Coord from;
	Coord to;
	Move() {
		from.x = 0;
		from.y = 0;
		to.x = 0;
		to.y = 0;
	}
	Move(string line) {
		from.x = line[0] - 'A';
		from.y = BOARD_SIZE - (line[1] - '1') - 1;
		to.x = line[2] - 'A';
		to.y = BOARD_SIZE - (line[3] - '1') - 1;
	}
};

class Board {

private:
	//char board[BOARD_SIZE][BOARD_SIZE] = { ' ' };
	char* board;
	
	
	void init(char(*board)[8]);
	void display(char(*board)[8]);

public:
	
	Board(int boardSize) { board = new char[boardSize * boardSize]; }
	void display();
	void init();
	void makeMove(const Move& m);
};

/*
struct Move {
	char fromCh;
	int from.y;
	char toCh;
	int toInt;

	void Fill(char fromCh, int from.y, char toCh, int toInt) {
		this->fromCh = fromCh;
		this->from.y = from.y;
		this->toCh = toCh;
		this->toInt = toInt;
	}

};
*/
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


void errorMessage(ErrorMessage::ErrorMessageTypes msg)
{
	switch (msg) {

	case ErrorMessage::badFormat:
		clearLine(20);
		cout << "Wrong coordinate format! Try: A2 F3" << endl;
		break;
	case ErrorMessage::emptySpaceSelected:
		clearLine(20);
		cout << "No pawn on this square!" << endl;
		break;
	case ErrorMessage::wrongColorSelected:
		clearLine(20);
		cout << "This is not your pawn!" << endl;
		break;
	case ErrorMessage::badPieceMovement:
		clearLine(20);
		cout << "This piece cannot do such movement!" << endl;
		break;
	case ErrorMessage::movementOverFigure:
		clearLine(20);
		cout << "This piece cannot move over other figure!" << endl;
		break;
	case ErrorMessage::squareIsOccupied:
		clearLine(20);
		cout << "Your pawn already occupies this field!" << endl;
		break;
	default:
		clearLine(20);
		cout << "Error!" << endl;

	}
}


/*
// translate chess letter value to board coord
int translateLetter(char letter) {
	int result = letter - 'A';
	if (result >= 0 && result < BOARD_SIZE) {
		return result;
	}
	return -1;

}


// translate chess number value to board coord
int translateInt(int number) {

	if (number < 1 && number > BOARD_SIZE) {
		return -1;
	}
	//change numbering of rows - in MOVE struct there was numbering from 1 to BOARD_SIZE
	//we change it initially to numbering from 0 to BOARD_SIZE - 1
	//reverse numbers of rows to correctly address the array board
	return BOARD_SIZE - number;
}
*/
int inverseTranslateInt(int x) {
	return BOARD_SIZE - x;
}

char inverseTranslateCh(int x) {
	return x + 'A';
}


//figure functions declarations
bool king(const Move &m, Board board, bool whites);
bool king(const Move &m, Board board);
bool queen(const Move &m, Board board);
bool bishop(const Move &m, Board board);
bool knight(const Move &m, Board board);
bool rook(const Move &m, Board board);
bool pawn(const Move &m, Board board, bool whites);

void strcpy_s(char str[1024], const char *c_str, int i);

//this function checks if the king is deadlocked(to be used in king's move validation[king])
bool is_Deadlocked(const Move &m, Board board, bool whites) {

	int toInt = m.to.y;
	char toCh = m.to.x;


	Move m_King;
	Move m_Queen;
	Move m_Bishop;
	Move m_Knight;
	Move m_Rook;
	Move m_Pawn;

	char figure;

	//setting up the Move structures for each enemy figure
	for (int i = 0; i<BOARD_SIZE; i++) {
		for (int j = 0; j<BOARD_SIZE; j++) {
			figure = board[i][j];

			if (whites) {

				if (figure == 'k') m_King.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'q') m_Queen.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'b') m_Bishop.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'n') m_Knight.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'r') m_Rook.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'p') m_Pawn.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
			}

			if (!whites) {

				if (figure == 'K') m_King.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'Q') m_Queen.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'B') m_Bishop.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'N') m_Knight.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'R') m_Rook.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
				if (figure == 'P') m_Pawn.Fill(inverseTranslateCh(j), inverseTranslateInt(i), toCh, toInt);
			}

		}
	}

	//returns true if any figure can move into kings destiny position->this means king is deadlocked

	if (king(m_King, board))
		return true;
	else if (queen(m_Queen, board))
		return true;
	else if (bishop(m_Bishop, board))
		return true;
	else if (knight(m_Knight, board))
		return true;
	else if (rook(m_Rook, board))
		return true;
	else if (pawn(m_Pawn, board, whites))
		return true;

	return false;
}

bool king(const Move &m, Board board, bool whites) {

	//step one- checking if the move is within king's range
	if (m.to.x == m.from.x + 1 && m.to.y == m.from.y) {
		//step two- checking if king is deadlocked
		return !is_Deadlocked(m, board, whites);
	}

	if (m.to.x == m.from.x  && m.to.y == m.from.y + 1) {
		return !is_Deadlocked(m, board, whites);
	}

	if (m.to.x == m.from.x + 1 && m.to.y == m.from.y + 1) {
		return !is_Deadlocked(m, board, whites);
	}

	if (m.to.x == m.from.x - 1 && m.to.y == m.from.y) {
		return !is_Deadlocked(m, board, whites);
	}

	if (m.to.x == m.from.x  && m.to.y == m.from.y - 1) {
		return !is_Deadlocked(m, board, whites);
	}

	if (m.to.x == m.from.x - 1 && m.to.y == m.from.y - 1) {
		return !is_Deadlocked(m, board, whites);
	}

	if (m.to.x == m.from.x - 1 && m.to.y == m.from.y + 1) {
		return !is_Deadlocked(m, board, whites);
	}

	if (m.to.x == m.from.x + 1 && m.to.y == m.from.y - 1) {
		return !is_Deadlocked(m, board, whites);
	}

	errorMessage(ErrorMessage::badPieceMovement);
	return false;
}

bool king(const Move &m, Board board) {

	if (m.to.x == m.from.x + 1 && m.to.y == m.from.y) {
		return true;
	}

	if (m.to.x == m.from.x  && m.to.y == m.from.y + 1) {
		return true;
	}

	if (m.to.x == m.from.x + 1 && m.to.y == m.from.y + 1) {
		return true;
	}

	if (m.to.x == m.from.x - 1 && m.to.y == m.from.y) {
		return true;
	}

	if (m.to.x == m.from.x  && m.to.y == m.from.y - 1) {
		return true;
	}

	if (m.to.x == m.from.x - 1 && m.to.y == m.from.y - 1) {
		return true;
	}

	if (m.to.x == m.from.x - 1 && m.to.y == m.from.y + 1) {
		return true;
	}

	if (m.to.x == m.from.x + 1 && m.to.y == m.from.y - 1) {
		return true;
	}

	return false;
}

bool queen(const Move &m, Board board) {
	if (rook(m, board) || bishop(m, board))
		return true;
	else
		return false;
}

bool bishop(const Move& m, Board board) {

	int char_diff = (m.to.x - m.from.x);
	int int_diff = (m.to.y - m.from.y);

	//basically in case of bishop the absolute value of vertical and horizontal shifts must be equal(diagonal move)
	if (abs(char_diff) != abs(int_diff)) {
		errorMessage(ErrorMessage::badPieceMovement);
		return false;
	}

	else if (int_diff>0 && char_diff>0) {
		for (int i = 1; i < abs(char_diff); i++) {
			if (board[m.from.y - i][m.from.x + i] != ' '){
				errorMessage(ErrorMessage::movementOverFigure);
				return false;
			}
		}
	}

	else if (int_diff<0 && char_diff<0) {
		for (int i = 1; i < abs(char_diff); i++) {
			if (board[m.from.y) + i][m.from.x - i] != ' '){
				errorMessage(ErrorMessage::movementOverFigure);
				return false;
			}
		}
	}

	else if (int_diff<0 && char_diff>0) {
		for (int i = 1; i<abs(char_diff); i++) {
			if (board[m.from.y + i][m.from.x + i] != ' ') {
				errorMessage(ErrorMessage::movementOverFigure);
				return false;
			}
		}
	}

	else if (int_diff>0 && char_diff<0) {
		for (int i = 1; i < abs(char_diff); i++) {
			if (board[m.from.y - i][m.from.x - i] != ' '){
				errorMessage(ErrorMessage::movementOverFigure);
				return false;
			}
		}
	}

	return true;
}

bool knight(const Move &m, Board board) {

	if (abs(m.from.x - m.to.x) == 1 && abs(m.from.y - m.to.y == 2))
		return true;

	if (abs(m.from.x - m.to.x) == 2 && abs(m.from.y - m.to.y == 1))
		return true;

	errorMessage(ErrorMessage::badPieceMovement);
	return false;
}

bool rook(const Move &m, Board board) {

	int char_diff = abs(m.to.x - m.from.x);
	int int_diff = abs(m.to.y - m.from.y);

	if (m.from.x != m.to.x && m.from.y != m.to.y) {
		errorMessage(ErrorMessage::badPieceMovement);
		return false;
	}

	if (m.from.x > m.to.x) {
		for (int i = 1; i < char_diff; ++i) {
			if (board[m.from.y][m.from.x - i] != ' ') {
				errorMessage(ErrorMessage::movementOverFigure);
				return false;
			}
		}
	}
	if (m.from.x < m.to.x) {
		for (int i = 1; i < char_diff; ++i) {
			if (board[m.from.y][m.from.x + i] != ' ') {
				errorMessage(ErrorMessage::movementOverFigure);
				return false;
			}
		}
	}
	if (m.from.y > m.to.y) {
		for (int i = 1; i < int_diff; ++i) {
			if (board[m.from.y + i][m.from.x] != ' ') {
				errorMessage(ErrorMessage::movementOverFigure);
				return false;
			}
		}
	}
	if (m.from.y < m.to.y) {
		for (int i = 1; i < int_diff; ++i) {
			if (board[m.from.y - i][m.from.x] != ' ') {
				errorMessage(ErrorMessage::movementOverFigure);
				return false;
			}
		}
	}

	return true;
}



bool pawn(const Move &m, Board board, bool whites) {

	int chFrom = m.from.x;
	int intFrom = m.from.y;
	int chTo = m.to.x;
	int intTo = m.to.y;

	int pawnColor = 1;
	if (whites) pawnColor = -1;


		// pawn moves 1 square forwards
		if (intTo == intFrom + pawnColor && chTo == chFrom && board[intFrom + pawnColor][chTo] == ' ') {
			return true;
		}
		// pawn moves crosswise and makes a kill
		else if (intTo == intFrom + pawnColor && chTo == chFrom + pawnColor && board[intFrom + pawnColor][chFrom + pawnColor] != ' ') {
			return true;
		}
		else if (intTo == intFrom + pawnColor && chTo == chFrom - pawnColor && board[intFrom + pawnColor][chFrom - pawnColor] != ' ') {
			return true;
		}

		//is pawn located in its initial row on the chessboard
		else if (intFrom == 2 || intFrom == BOARD_SIZE - 1) {
			//first movement of a pawn, allowed movement by 1 or 2 fields, moves only forwards and kills crosswise
			//movement by 2 fields allowed for a pawn
			if (intTo == intFrom + 2* pawnColor && chTo == chFrom && board[intFrom + pawnColor][chFrom] == ' ' &&
				board[intFrom + 2* pawnColor][chFrom] == ' ') {
				return true;
			}
		}
		errorMessage(ErrorMessage::badPieceMovement);
		return false;
}



// Check if proper pawn is selected or space is empty
bool isPieceSelected(const Move &m, Board board, bool whites) {

	char piece = board[m.from.y][m.from.x];

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
bool isSquareAvailable(const Move &m, Board board, bool whites) {

	char piece = board[m.from.y][m.from.x];

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



// Check if move of figure is valid according to chess rules
bool valid(const Move& m, Board board, bool whites)
{
	char piece = board[m.from.y][m.from.x];

	if (!(isPieceSelected(m, board, whites))) {
		return false;
	}

	if (!(isSquareAvailable(m, board, whites)))
		return false;

	switch (tolower(piece)) {

	case 'p':
		if (!(pawn(m, board, whites))) {
			return false;
		}
		break;
	case 'r':
		if (!(rook(m, board))) {
			return false;
		}
		break;
	case 'n':
		if (!(knight(m, board))) {
			return false;
		}
		break;
	case 'b':
		if (!(bishop(m, board))) {
			return false;
		}
		break;
	case 'q':
		if (!(queen(m, board))) {
			return false;
		}
		break;
	case 'k':
		if (!(king(m, board, whites))) {
			errorMessage(ErrorMessage::badPieceMovement);
			return false;
		}
		break;

	}

	return true;
}


bool valid(Move m) {

	if (m.from.x < 'A' || m.from.x >= 'A' + BOARD_SIZE) {
		return false;
	}
	else if (m.to.x < 'A' || m.to.x >= 'A' + BOARD_SIZE) {
		return false;
	}
	else if (m.from.y < 1 || m.from.y > BOARD_SIZE) {
		return false;
	}
	else if (m.to.y < 1 || m.to.y > BOARD_SIZE) {
		return false;
	}
	return true;
}


//removes spaces from char*
void removeSpaces(char* s)
{
	char* s2 = s;
	do {
		if (*s2 != ' ')
			*s++ = *s2;
	} while (*s2++);
}


// check if user input is in proper format
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



// change user imput into format: 'A2H5' and return structure variable with move informations
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

	Move move();
	move.from.x = fromChars[0];
	move.from.y = from.y;
	move.to.x = toChars[0];
	move.to.y = toInt;

	return move;
}

Move getMove(bool whites)
{
	Move m;
	string line;
	char lineStr[1024];
	do {
		clearLine(21);
		if (whites)
			cout << "White turn:" << endl;
		else
			cout << "Black turn:" << endl;
		
		getline(cin, line);
		clearLine(22);
		strcpy_s(lineStr, line.c_str(), 1024);
	} while (!valid(lineStr) || !valid((m = readMove(lineStr))));
	return m;
}

void strcpy_s(char str[1024], const char *c_str, int i) {
	for (int p = 0; p<1023; p++) {
		str[p] = c_str[p];
	}
	str[1023] = '\0';
}


void Board::makeMove(const Move& m)
{
	char figure = board[m.from.y][m.from.x];
	board[m.from.y][m.from.x] = ' ';
	board[m.to.y][m.to.x] = figure;
}

void doMove(Board board, bool whites)
{
	Move m;
	do {
		do {
			m = getMove(whites);
		} while (!valid(m));
	} while (!valid(m, board, whites));
	board.makeMove(m);

}


//displays board - takes array board[BOARD_SIZE][BOARD_SIZE]
// and reads its contents, and displays on the screen
void Board::display(char(*board)[8])
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

void Board::display() 
{
	display((char(*)[8])board);
}

void Board::init(char(*board)[8])
{
	clearScreen();
	const char figuresRow[BOARD_SIZE] = { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' };

	memset(board, ' ', sizeof(char) * BOARD_SIZE * BOARD_SIZE);

	for (unsigned i = 0; i < BOARD_SIZE; i++)
		board[0][i] = figuresRow[i];

	for (unsigned i = 0; i < BOARD_SIZE; i++)
		board[1][i] = 'p';

	for (unsigned i = 0; i < BOARD_SIZE; i++)
		board[BOARD_SIZE - 2][i] = 'P';

	for (unsigned i = 0; i < BOARD_SIZE; i++)
		board[BOARD_SIZE - 1][i] = toupper(figuresRow[i]);
}

void Board::init() {
	init((char(*)[8])board);
}

bool endOfGame(Board board)
{
	return false;
}

int main()
{
	Board board = Board(8);
	board.init();
	bool whites = true;
	do {
		board.display();
		doMove(board, whites);
		whites = !whites;
		clearScreen();
	} while (!endOfGame(board));

}