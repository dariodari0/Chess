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

*/




//LIBRARIES --------------------------------------------------------------------------------------
// important for VS
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif


//NAMESPACES ----------------------------------------------------------------------------------------

using namespace std;


// Will be upgraded if necessary
namespace ErrorMessage {

	static string playerInputLine;

	enum ErrorMessageTypes {
		badFormat,
		coordBeyondBoard,
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
	int row;
	int col;
};

struct Move {
	Coord from;
	Coord to;
	Move() {
		from.col = 0;
		from.row = 0;
		to.col = 0;
		to.row = 0;
	}
	Move(string line) {
		from.col = line[0] - 'A';
		from.row = BOARD_SIZE - (line[1] - '1') - 1;
		to.col = line[2] - 'A';
		to.row = BOARD_SIZE - (line[3] - '1') - 1;
	}
};

class Board {

private:
	//char board[BOARD_SIZE][BOARD_SIZE] = { ' ' };
	char* board;

public:
	Board(int boardSize) { board = new char[boardSize * boardSize]; }

	void display();
	void init();
	void makeMove(const Move& m);

	char& operator()(int x, int y);
	char operator()(int x, int y) const;
};

char& Board::operator()(int row, int col) {
	return *(board + (col + row * BOARD_SIZE));
}

char Board::operator()(int row, int col) const {
	return *(board + (col + row * BOARD_SIZE));
}

/*
struct Move {
	char fromCh;
	int from.row;
	char toCh;
	int toInt;

	void Fill(char fromCh, int from.row, char toCh, int toInt) {
		this->fromCh = fromCh;
		this->from.row = from.row;
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



void clearLinesFrom(short y, short count)
{
for (short i = 0; i < count; i++)
clearLine(y + i);
}



void errorMessage(ErrorMessage::ErrorMessageTypes msg)
{
	switch (msg) {

	case ErrorMessage::badFormat:
		clearLine(20);
		cout << "Wrong coordinate format! Try: A2 F3" << endl;
		break;
	case ErrorMessage::coordBeyondBoard:
		clearLine(20);
		cout << "Coordinates are outside the board! Try between A-H and 1-8" << endl;
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
	clearLine(21);
	cout << "Your input: " << ErrorMessage::playerInputLine << endl;
	cout << endl << "Press Enter to Continue";
	cin.ignore();
	clearLinesFrom(20, 3);
	gotoXY(0, 20);
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



//this function checks if the king is deadlocked(to be used in king's move validation[king])
bool is_Deadlocked(const Move &m, Board board, bool whites) {

	int toInt = m.to.row;
	char toCh = m.to.col;


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
	if (m.to.col == m.from.col + 1 && m.to.row == m.from.row) {
		//step two- checking if king is deadlocked
		return !is_Deadlocked(m, board, whites);
	}

	if (m.to.col == m.from.col  && m.to.row == m.from.row + 1) {
		return !is_Deadlocked(m, board, whites);
	}

	if (m.to.col == m.from.col + 1 && m.to.row == m.from.row + 1) {
		return !is_Deadlocked(m, board, whites);
	}

	if (m.to.col == m.from.col - 1 && m.to.row == m.from.row) {
		return !is_Deadlocked(m, board, whites);
	}

	if (m.to.col == m.from.col  && m.to.row == m.from.row - 1) {
		return !is_Deadlocked(m, board, whites);
	}

	if (m.to.col == m.from.col - 1 && m.to.row == m.from.row - 1) {
		return !is_Deadlocked(m, board, whites);
	}

	if (m.to.col == m.from.col - 1 && m.to.row == m.from.row + 1) {
		return !is_Deadlocked(m, board, whites);
	}

	if (m.to.col == m.from.col + 1 && m.to.row == m.from.row - 1) {
		return !is_Deadlocked(m, board, whites);
	}

	errorMessage(ErrorMessage::badPieceMovement);
	return false;
}

bool king(const Move &m, Board board) {

	if (m.to.col == m.from.col + 1 && m.to.row == m.from.row) {
		return true;
	}

	if (m.to.col == m.from.col  && m.to.row == m.from.row + 1) {
		return true;
	}

	if (m.to.col == m.from.col + 1 && m.to.row == m.from.row + 1) {
		return true;
	}

	if (m.to.col == m.from.col - 1 && m.to.row == m.from.row) {
		return true;
	}

	if (m.to.col == m.from.col  && m.to.row == m.from.row - 1) {
		return true;
	}

	if (m.to.col == m.from.col - 1 && m.to.row == m.from.row - 1) {
		return true;
	}

	if (m.to.col == m.from.col - 1 && m.to.row == m.from.row + 1) {
		return true;
	}

	if (m.to.col == m.from.col + 1 && m.to.row == m.from.row - 1) {
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

	int col_diff = (m.to.col - m.from.col);
	int row_diff = (m.to.row - m.from.row);

	//basically in case of bishop the absolute value of vertical and horizontal shifts must be equal(diagonal move)
	if (abs(col_diff) != abs(row_diff)) {
		errorMessage(ErrorMessage::badPieceMovement);
		return false;
	}

	else if (row_diff > 0 && col_diff > 0) {
		for (int i = 1; i < abs(col_diff); i++) {
			if (board(m.from.row + i, m.from.col + i) != ' '){
				errorMessage(ErrorMessage::movementOverFigure);
				return false;
			}
		}
	}

	else if (row_diff < 0 && col_diff < 0) {
		for (int i = 1; i < abs(col_diff); i++) {
			if (board(m.from.row - i, m.from.col - i) != ' '){
				errorMessage(ErrorMessage::movementOverFigure);
				return false;
			}
		}
	}

	else if (row_diff < 0 && col_diff > 0) {
		for (int i = 1; i<abs(col_diff); i++) {
			if (board(m.from.row - i, m.from.col + i) != ' ') {
				errorMessage(ErrorMessage::movementOverFigure);
				return false;
			}
		}
	}

	else if (row_diff > 0 && col_diff < 0) {
		for (int i = 1; i < abs(col_diff); i++) {
			if (board(m.from.row + i, m.from.col - i) != ' '){
				errorMessage(ErrorMessage::movementOverFigure);
				return false;
			}
		}
	}

	return true;
}

bool knight(const Move &m, Board board) {

	if (abs(m.from.col - m.to.col) == 1 && abs(m.from.row - m.to.row ) == 2)
		return true;

	if (abs(m.from.col - m.to.col) == 2 && abs(m.from.row - m.to.row ) == 1)
		return true;

	errorMessage(ErrorMessage::badPieceMovement);
	return false;
}

bool rook(const Move &m, Board board) {

	int col_diff = abs(m.to.col - m.from.col);
	int row_diff = abs(m.to.row - m.from.row);

	if (m.from.col != m.to.col && m.from.row != m.to.row) {
		errorMessage(ErrorMessage::badPieceMovement);
		return false;
	}

	if (m.from.col > m.to.col) {
		for (int i = 1; i < col_diff; ++i) {
			if (board(m.from.row, m.from.col - i) != ' ') {
				errorMessage(ErrorMessage::movementOverFigure);
				return false;
			}
		}
	}
	if (m.from.col < m.to.col) {
		for (int i = 1; i < col_diff; ++i) {
			if (board(m.from.row, m.from.col + i) != ' ') {
				errorMessage(ErrorMessage::movementOverFigure);
				return false;
			}
		}
	}
	if (m.from.row > m.to.row) {
		for (int i = 1; i < row_diff; ++i) {
			if (board(m.from.row - i, m.from.col) != ' ') {
				errorMessage(ErrorMessage::movementOverFigure);
				return false;
			}
		}
	}
	if (m.from.row < m.to.row) {
		for (int i = 1; i < row_diff; ++i) {
			if (board(m.from.row + i, m.from.col) != ' ') {
				errorMessage(ErrorMessage::movementOverFigure);
				return false;
			}
		}
	}

	return true;
}

bool pawn(const Move &m, Board board, bool whites) {

	int pawnColor = 1;
	if (whites) pawnColor = -1;

		// pawn moves 1 square forwards
		if (m.to.row == m.from.row + pawnColor && m.to.col == m.from.col && board(m.from.row + pawnColor, m.to.col) == ' ') {
			return true;
		}
		// pawn moves crosswise and makes a kill
		else if (m.to.row == m.from.row + pawnColor && m.to.col == m.from.col + pawnColor && board(m.from.row + pawnColor, m.from.col + pawnColor) != ' ') {
			return true;
		}
		else if (m.to.row == m.from.row + pawnColor && m.to.col == m.from.col - pawnColor && board(m.from.row + pawnColor, m.from.col - pawnColor) != ' ') {
			return true;
		}

		//is pawn located in its initial row on the chessboard
		else if (m.from.row == 1 || m.from.row == BOARD_SIZE - 2) {
			//first movement of a pawn, allowed movement by 1 or 2 fields, moves only forwards and kills crosswise
			//movement by 2 fields allowed for a pawn
			if (m.to.row == m.from.row + 2* pawnColor && m.to.col == m.from.col && board(m.from.row + pawnColor, m.from.col) == ' ' &&
				board(m.from.row + 2* pawnColor, m.from.col) == ' ') {
				return true;
			}
		}
		errorMessage(ErrorMessage::badPieceMovement);
		return false;
}



// Check if proper pawn is selected or space is empty
bool isPieceSelected(const Move &m, Board board, bool whites) {

	char piece = board(m.from.row, m.from.col);

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

// Check if pawn can enter selected square
bool isSquareAvailable(const Move &m, Board board, bool whites) {

	char piece = board(m.to.row, m.to.col);

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
	char piece = board(m.from.row, m.from.col);

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

	if (m.from.col < 0 || m.from.col >= BOARD_SIZE) {
		errorMessage(ErrorMessage::coordBeyondBoard);
		return false;
	}
	else if (m.to.col < 0 || m.to.col >= BOARD_SIZE) {
		errorMessage(ErrorMessage::coordBeyondBoard);
		return false;
	}
	else if (m.from.row < 0 || m.from.row > BOARD_SIZE) {
		errorMessage(ErrorMessage::coordBeyondBoard);
		return false;
	}
	else if (m.to.row < 0 || m.to.row > BOARD_SIZE) {
		errorMessage(ErrorMessage::coordBeyondBoard);
		return false;
	}
	return true;
}

// check if user input is in proper format
bool valid(string& line)
{
	line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
	transform(line.begin(), line.end(), line.begin(), ::toupper);

	// send player input to ErrorMessage as interpreted by application
	ErrorMessage::playerInputLine = line;

	if (line.size() != 4) {
		errorMessage(ErrorMessage::badFormat);
		return false;
	}
	return true;
}


Move getMove(bool whites)
{
	Move m;
	string line = "";
	do {
		if (whites)
			cout << "White turn:" << endl;
		else
			cout << "Black turn:" << endl;
		
		getline(cin, line);
	} while (!valid(line));

	return m = Move(line);
}

void Board::makeMove(const Move& m)
{
	Board board = *this;
	char figure = board(m.from.row, m.from.col);
	board(m.from.row, m.from.col) = ' ';
	board(m.to.row, m.to.col) = figure;
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
void Board::display() 
{
	Board board = *this;
	char letter = 0;
	int i = 0;
	int j = 0;
	char k = 0;
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

	// take the array that keeps actual positions of figures and display it on the chessboard

	for (i = 0; i < BOARD_SIZE; i++) {

		cout << " " << BOARD_SIZE - i << " ";

		for (j = 0; j < BOARD_SIZE; j++) {
			cout << " " << "|" << " " << board(i, j);
		}
		cout << " " << "|" << " " << BOARD_SIZE - i << " ";
		cout << "\n";


		// delimit each row with figures with a delimiter "    +---+---+---+---+---+---+---+---+   \n";
		cout << "    ";
		for (k = 'A'; k<'A' + BOARD_SIZE; k++) {
			cout << "+---";
		}
		cout << "+   \n";

	}

	// row with letters that reprezenting headers of columns
	cout << "   ";
	for (letter = 'A'; letter < 'A' + BOARD_SIZE; letter++)
		cout << "   " << letter;
	cout << "      \n\n";

}

void Board::init()
{
	Board board = *this;
	const char figuresRow[BOARD_SIZE] = { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' };

	memset(this->board, ' ', sizeof(char) * BOARD_SIZE * BOARD_SIZE);
	for (unsigned i = 0; i < BOARD_SIZE; i++)
		board(0, i) = figuresRow[i];

	for (unsigned i = 0; i < BOARD_SIZE; i++)
		board(1, i) = 'p';

	for (unsigned i = 0; i < BOARD_SIZE; i++)
		board(BOARD_SIZE - 2, i) = 'P';

	for (unsigned i = 0; i < BOARD_SIZE; i++)
		board(BOARD_SIZE - 1, i) = toupper(figuresRow[i]);
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