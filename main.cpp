//******************************************************************************************************
//*                               PROJEKT GRUPOWY ESS DZIEN 9                                          *
//*               skompilowano komendą:       g++ -Wall -std=c++11   main.cpp                          *
//*                                                                                                    *
//*                                         wykonawcy:                                                 *
//*                       Michał Więckowski                                                            *
//*                       Mateusz Kaleta                                                               *
//*                       Dariusz Markowicz                                                            *
//*                       Joanna Wyrobek                                                               *
//******************************************************************************************************



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
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif


//NAMESPACES ----------------------------------------------------------------------------------------

using namespace std;


namespace ErrorMessage {

	static string playerInputLine;

	enum ErrorMessageTypes {
		badFormat,
		coordBeyondBoard,
		emptySpaceSelected,
		wrongColorSelected,
		badPieceMovement,
		movementOverFigure,
		squareIsOccupied,
		isDeadlock
	};
}

//CONSTANTS ----------------------------------------------------------------------------------------
const int BOARD_SIZE = 8;

//CLASS DECLARATIONS -----------------------------------------------------------------------------

class Board;

struct Move;

class FigureFactory;

class Figure;

class King;

class Queen;

class Bishop;

class Knight;

class Rook;

class Pawn;

class Player;

enum class BoardOps {
	CLEAR_BOARD,
	INIT_BOARD,
};

//GLOBAL FUNCTION DECLARATIONS -------------------------------------------------------------------
void gotoXY(short x, short y);

void clearLine(short y);

void clearScreen();

void clearLinesFrom(short y, short count);

void errorMessage(ErrorMessage::ErrorMessageTypes msg);


//STRUCTURES AND CLASSES --------------------------------------------------------------------------
struct Coord {
	int row;
	int col;

	Coord() :row(0), col(0) {};

	Coord(int _row, int _col) {
		row = _row;
		col = _col;
	}
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

	explicit Move(string line) {
		from.col = line[0] - 'A';
		from.row = BOARD_SIZE - (line[1] - '1') - 1;
		to.col = line[2] - 'A';
		to.row = BOARD_SIZE - (line[3] - '1') - 1;
	}

	void Fill(char fromCol, int fromRow, char toCol, int toRow) {
		from.col = fromCol;
		from.row = fromRow;
		to.col = toCol;
		to.row = toRow;
	}

	bool valid(bool errorMessagesOn = true);
};


bool Move::valid(bool errorMessagesOn) {

	if (from.col < 0 || from.col >= BOARD_SIZE) {
		if (errorMessagesOn) { errorMessage(ErrorMessage::coordBeyondBoard); }
		return false;
	}
	else if (to.col < 0 || to.col >= BOARD_SIZE) {
		if (errorMessagesOn) { errorMessage(ErrorMessage::coordBeyondBoard); }
		return false;
	}
	else if (from.row < 0 || from.row > BOARD_SIZE) {
		if (errorMessagesOn) { errorMessage(ErrorMessage::coordBeyondBoard); }
		return false;
	}
	else if (to.row < 0 || to.row > BOARD_SIZE) {
		if (errorMessagesOn) { errorMessage(ErrorMessage::coordBeyondBoard); }
		return false;
	}
	return true;
}


class Figure {
private:
	char name = ' ';
protected:
	bool white = true;
public:

	virtual bool isWhite() {
		cout << "This message should not be displayed - empty square holds neither black of white piece" << endl;
		return false;
	}

	Figure() = default;

	virtual ~Figure() {};

	virtual bool valid(const Move &m, vector<Coord> &list, bool errorMessagesOn) {
		return false;
	};

	char &operator*() { return name; }


	Figure &operator=(const char name) {
		this->name = name;
		return *this;
	}

	void set(char _name) {
		name = _name;
	}

	char get() {
		return name;
	}

	friend ostream &operator<<(ostream &os, Figure &figure);

};

ostream &operator<<(ostream &os, Figure &figure) {
	os << figure.get();
	return os;
}



class Board {

public:
	Figure *board[BOARD_SIZE][BOARD_SIZE];

	void display(ostream &os) const;

	void init();

public:

	Board() {
		init();
		display(cout);
	}

	Board &operator=(const BoardOps boardOps);

	friend ostream &operator<<(ostream &os, const Board &board);

	Figure &operator()(int x, int y);

	Figure operator()(int x, int y) const;

	void makeMove(const Move &m);

	Board &operator+=(const Move &m);
};

Board &Board::operator=(const BoardOps boardOps) {
	switch (boardOps) {
	case BoardOps::CLEAR_BOARD:
		break;
	case BoardOps::INIT_BOARD:
		init();
		break;
	}
	return *this;
}


ostream &operator<<(ostream &os, const Board &board) {
	clearScreen();
	board.display(os);
	return os;
}

Figure &Board::operator()(int row, int col) {
	if (row>BOARD_SIZE || col > BOARD_SIZE || row<0 || row < 0) {
		cout << "Operator () for Board is out of scope" << endl;
		throw 5;
	}
	return *(board[col][row]);
}


Figure Board::operator()(int row, int col) const {
	if (row>BOARD_SIZE || col > BOARD_SIZE || row<0 || row < 0) {
		cout << "Operator () for Board is out of scope" << endl;
		throw 5;
	}
	return *(board[col][row]);
}


void Board::makeMove(const Move &m) {
	delete board[m.to.row][m.to.col];
	board[m.to.row][m.to.col] = board[m.from.row][m.from.col];
	board[m.from.row][m.from.col] = new Figure();

}

Board &Board::operator+=(const Move &m) {
	makeMove(m);
	return *this;
}


class King : public Figure {
public:

	explicit King(bool _white) {
		white = _white;
		_white ? set('K') : set('k');
	}

	bool isWhite() override {
		return white;
	}

	bool valid(const Move &m, vector<Coord> &list, bool errorMessagesOn = true) override {

		if (m.to.col == m.from.col + 1 && m.to.row == m.from.row) {
			return true;
		}

		if (m.to.col == m.from.col && m.to.row == m.from.row + 1) {
			return true;
		}

		if (m.to.col == m.from.col + 1 && m.to.row == m.from.row + 1) {
			return true;
		}
		if (m.to.col == m.from.col - 1 && m.to.row == m.from.row) {
			return true;
		}

		if (m.to.col == m.from.col && m.to.row == m.from.row - 1) {
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

		if (errorMessagesOn) { errorMessage(ErrorMessage::badPieceMovement); }
		return false;
	}
};

class Bishop : public Figure {
public:
	explicit Bishop(bool _white) {
		white = _white;
		_white ? set('B') : set('b');
	}

	bool isWhite() override {
		return white;
	}

	bool valid(const Move &m, vector<Coord> &list, bool errorMessagesOn = true) override {
		int col_diff = (m.to.col - m.from.col);
		int row_diff = (m.to.row - m.from.row);

		//basically in case of bishop the absolute value of vertical and horizontal shifts must be equal(diagonal move)
		if (abs(col_diff) != abs(row_diff)) {
			if (errorMessagesOn) { errorMessage(ErrorMessage::badPieceMovement); }
			return false;
		}
		else if (row_diff > 0 && col_diff > 0) {
			for (int i = 1; i < abs(col_diff); i++) {
				list.push_back(Coord(m.from.row + i, m.from.col + i));
			}
		}
		else if (row_diff < 0 && col_diff < 0) {
			for (int i = 1; i < abs(col_diff); i++) {
				list.push_back(Coord(m.from.row - i, m.from.col - i));
			}
		}
		else if (row_diff < 0 && col_diff > 0) {
			for (int i = 1; i < abs(col_diff); i++) {
				list.push_back(Coord(m.from.row - i, m.from.col + i));
			}
		}
		else if (row_diff > 0 && col_diff < 0) {
			for (int i = 1; i < abs(col_diff); i++) {
				list.push_back(Coord(m.from.row + i, m.from.col - i));
			}
		}
		return true;
	}
};

class Queen : public Bishop {
public:

	explicit Queen(bool _white) : Bishop(_white) { _white ? set('Q') : set('q'); }

	bool valid(const Move &m, vector<Coord> &list, bool errorMessagesOn = true) override {
		if (Bishop::valid(m, list,
			false)) //errorMessagesOff bo interesuje nas tylko czy ruch bylby akceptowalny przez Bishopa, to ze ruch nie jest akceptowalny przez bishopa nie oznacza ze krolowka go nie moze wykonac, wiec wylaczam komunikaty o bledach
			return true;

		int col_diff = abs(m.to.col - m.from.col);
		int row_diff = abs(m.to.row - m.from.row);

		if (m.from.col != m.to.col && m.from.row != m.to.row) {
			if (errorMessagesOn) { errorMessage(ErrorMessage::badPieceMovement); }
			return false;
		}

		if (m.from.col > m.to.col) {
			for (int i = 1; i < col_diff; ++i) {
				list.push_back(Coord(m.from.row, m.from.col - i));
			}
		}
		if (m.from.col < m.to.col) {
			for (int i = 1; i < col_diff; ++i) {
				list.push_back(Coord(m.from.row, m.from.col + i));
			}
		}
		if (m.from.row > m.to.row) {
			for (int i = 1; i < row_diff; ++i) {
				list.push_back(Coord(m.from.row - i, m.from.col));
			}
		}
		if (m.from.row < m.to.row) {
			for (int i = 1; i < row_diff; ++i) {
				list.push_back(Coord(m.from.row + i, m.from.col));
			}
		}

		return true;

	}
};

class Knight : public Figure {
public:

	explicit Knight(bool _white) {
		white = _white;
		_white ? set('N') : set('n');
	}

	bool isWhite() override {
		return white;
	}

	bool valid(const Move &m, vector<Coord> &list, bool errorMessagesOn = true) override {

		if (abs(m.from.col - m.to.col) == 1 && abs(m.from.row - m.to.row) == 2)
			return true;

		if (abs(m.from.col - m.to.col) == 2 && abs(m.from.row - m.to.row) == 1)
			return true;
		if (errorMessagesOn) { errorMessage(ErrorMessage::badPieceMovement); }
		return false;
	}
};

class Rook : public Figure {
public:

	explicit Rook(bool _white) {
		white = _white;
		_white ? set('R') : set('r');
	}

	bool isWhite() override {
		return white;
	}

	bool valid(const Move &m, vector<Coord> &list, bool errorMessagesOn = true) override {

		int col_diff = abs(m.to.col - m.from.col);
		int row_diff = abs(m.to.row - m.from.row);

		if (m.from.col != m.to.col && m.from.row != m.to.row) {
			if (errorMessagesOn) { errorMessage(ErrorMessage::badPieceMovement); }
			return false;
		}

		if (m.from.col > m.to.col) {
			for (int i = 1; i < col_diff; ++i) {
				list.push_back(Coord(m.from.row, m.from.col - i));
			}
		}
		if (m.from.col < m.to.col) {
			for (int i = 1; i < col_diff; ++i) {
				list.push_back(Coord(m.from.row, m.from.col + i));
			}
		}
		if (m.from.row > m.to.row) {
			for (int i = 1; i < row_diff; ++i) {
				list.push_back(Coord(m.from.row - i, m.from.col));
			}
		}
		if (m.from.row < m.to.row) {
			for (int i = 1; i < row_diff; ++i) {
				list.push_back(Coord(m.from.row + i, m.from.col));
			}
		}

		return true;
	}
};




//displays board - takes array board[BOARD_SIZE][BOARD_SIZE]
// and reads its contents, and displays on the screen
void Board::display(ostream &os) const {
	clearScreen();
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
	for (i = 'A'; i < 'A' + BOARD_SIZE; i++) {
		cout << "+---";
	}
	cout << "+   \n";

	// take the array that keeps actual positions of figures and display it on the chessboard
	for (i = 0; i < BOARD_SIZE; i++) {

		cout << " " << BOARD_SIZE - i << " ";
		for (j = 0; j < BOARD_SIZE; j++) {

			cout << " " << "|" << " " << (*board[i][j]).get();
		}
		cout << " " << "|" << " " << BOARD_SIZE - i << " ";
		cout << "\n";

		// delimit each row with figures with a delimiter "    +---+---+---+---+---+---+---+---+   \n";
		cout << "    ";
		for (k = 'A'; k < 'A' + BOARD_SIZE; k++) {
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


class Player {
	static Board b;
	Move m;
	static bool whites;

public:
	Player() = default;

	explicit Player(Board _board) { b = _board; }

	void changeTurn() { whites = !whites; }

	//true = whites, false = blacks
	static bool getTurn() { return whites; }

	Move getMove();

	bool isPieceSelected(const Move &m, bool errorMessagesOn);

	bool isSquareAvailable(const Move &m, bool errorMessagesOn);

	bool valid(string &line);

	bool is_Deadlocked(const Move &m);

	bool valid(const Move &m, bool errorMessagesOn = true, bool isDeadlockMode = false);

	bool blackKing();

	bool whiteKing();

	bool endOfGame();

	void isPromotion();

	bool move();
};

Board Player::b; // = Board::Board();

bool Player::whites = true;


Move Player::getMove() {
	string line;
	do {
		if (getTurn())
			cout << "White turn:" << endl;
		else
			cout << "Black turn:" << endl;
		getline(cin, line);
	} while (!valid(line));
	return Move(line);
}

bool Player::valid(string &line)
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

// Check if piece can enter selected square
bool Player::isSquareAvailable(const Move &m, bool errorMessagesOn)
{
	char piece = b.board[m.to.row][m.to.col]->get();
	if (piece >= 'a' && piece <= 'z') {
		if (!getTurn()) {
			if (errorMessagesOn) { errorMessage(ErrorMessage::squareIsOccupied); }
			return false;
		}
	}
	else if (piece >= 'A' && piece <= 'Z' && getTurn()) {
		if (errorMessagesOn) { errorMessage(ErrorMessage::squareIsOccupied); }
		return false;
	}
	return true;
}

bool Player::isPieceSelected(const Move &m, bool errorMessagesOn) {
	Figure *fig = b.board[m.from.row][m.from.col];
	if ((fig->get()) == ' ') {
		if (errorMessagesOn) {
			errorMessage(ErrorMessage::emptySpaceSelected);
		}
		return false;
	}
	if ((fig->isWhite()) != (getTurn())) {
		if (errorMessagesOn) {
			errorMessage(ErrorMessage::wrongColorSelected);
		}
		return false;
	}
	return true;
}


bool Player::is_Deadlocked(const Move &m) {

	int toInt = m.to.row;
	int toCh = m.to.col;
	int fromInt = m.from.row;
	int fromCh = m.from.col;
	Move reverse;
	reverse.Fill(toCh, toInt, fromCh, fromInt);

	Move tempMove;
	changeTurn(); //we want to check the other player's pieces
	b.makeMove(m);
	//setting up the Move structures for each enemy figure
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {

			tempMove.Fill(i, j, toCh, toInt);
			//is a movement of any figure of an enemy to the king destination possible?
			//if it is possible, return true - killing of a king is possible
			//valid function is run in no errors mode and is deadlocked mode
			if (valid(tempMove, false, true)) {
				errorMessage(ErrorMessage::isDeadlock);
				changeTurn(); //revert previous change of players
				b.makeMove(reverse); //revert king's move
				return true;
			}
		}
	}
	//if the board was empty, killing a king is not possible
	//if there is no piece that can kill a king, then killing of a king is not possible
	changeTurn(); //revert previous change of players
	b.makeMove(reverse); //revert king's move
	return false;
}


bool Player::valid(const Move &m, bool errorMessagesOn, bool isDeadlockMode) {
	vector<Coord> list;
	//check whether on the start field is any figure
	if (!(isPieceSelected(m, errorMessagesOn))) {
		return false;
	}

	//check whether the end field is either empty or has other player's figure
	if (!(isSquareAvailable(m, errorMessagesOn))) {
		return false;
	}

	//check whether the move itself is correct for the chosen figure - we do not check whether
	//all the fields that a figure passes are empty here
	if (!(b.board[m.from.row][m.from.col]->valid(m, list, errorMessagesOn))) {
		return false;
	}

	vector<Coord>::iterator it;

	//is our piece a pawn?
	//if so, does it move across - all other end field situations are checked by other validation functions
	//only in this case the end field is added to the list and has to be checked

	if (b.board[m.from.row][m.from.col]->get() == 'p' || b.board[m.from.row][m.from.col]->get() == 'P') {

		//checks whether the pawn moves horizontally
		if ((m.to.col - m.from.col) != 0) {

			//pawn moves sideways - then its final field has to be occupied by other player's piece
			if (b.board[m.to.row][m.to.col]->get() == ' ') {

				if (errorMessagesOn) { errorMessage(ErrorMessage::badPieceMovement); }
				return false;
			}
			return true;
		}
	}

	//if we are not dealing with a pawn that moves across, we do not have final fields in the list
	//and we only check whether intermediary fields are empty
	//if it is a knight, no fields are added to the list and then we do not check them
	for (it = list.begin(); it != list.end(); ++it) {

		if ((b.board[it->row][it->col]->get() != ' ')) {
			if (errorMessagesOn) { errorMessage(ErrorMessage::movementOverFigure); }
			return false;
		}
	}

	if ((b.board[m.from.row][m.from.col]->get() == 'k' || b.board[m.from.row][m.from.col]->get() == 'K') &&
		(!isDeadlockMode)) {
		return !is_Deadlocked(m);
	}

	return true;
}


bool Player::blackKing() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (b.board[i][j]->get() == 'k') {
				return false;
			}
		}
	}
	return true;
}


bool Player::whiteKing() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (b.board[i][j]->get() == 'K') {
				return false;
			}
		}
	}
	return true;
}


bool Player::endOfGame() {
	return (blackKing() || whiteKing());
}

void Player::isPromotion() {
	if (whites) {
		for (int i = 0; i<BOARD_SIZE; i++) {
			if (b.board[0][i]->get() == 'P') {
				std::string answer;
				do {
					cout << "Promotion to: R, B, N, Q ->" << endl;
					std::getline(std::cin, answer);
				} while (answer[0] != 'R' && answer[0] != 'B' && answer[0] != 'N' && answer[0] != 'Q');
				b.board[0][i]->set(answer[0]);
				cout << b;
			}
		}
	}
	else {
		for (int i = 0; i<BOARD_SIZE; i++) {
			if (b.board[BOARD_SIZE - 1][i]->get() == 'p') {
				std::string answer;
				do {
					cout << "Promotion to: r, b, n, q ->" << endl;
					cin >> answer;
				} while (answer[0] != 'r' && answer[0] != 'b' && answer[0] != 'n' && answer[0] != 'q');
				b.board[BOARD_SIZE - 1][i]->set(answer[0]);
				cout << b;
			}
		}
	}
}

bool Player::move() {
	do {
		do {
			m = getMove();
		} while (!m.valid());
	} while (!valid(m));
	b += m;
	cout << b;
	isPromotion();
	changeTurn();
	return endOfGame();
}


class Pawn : public Figure {
public:

	explicit Pawn(bool _white) {
		white = _white;
		_white ? set('P') : set('p');
	}

	bool isWhite() override {
		return white;
	}

	bool valid(const Move &m, vector<Coord> &list, bool errorMessagesOn = true) override {

		int pawnColor = 1;
		if (Player::getTurn()) { pawnColor = -1; }
		// pawn moves 1 square forwards
		if (m.to.row == m.from.row + pawnColor && m.to.col == m.from.col) {
			list.push_back(Coord(m.from.row + pawnColor, m.from.col));
			return true;
		}
		// pawn moves across and makes a kill
		else if (m.to.row == m.from.row + pawnColor && m.to.col == m.from.col + 1) {
			list.push_back(Coord(m.from.row + pawnColor, m.from.col + 1));
			return true;
		}
		else if (m.to.row == m.from.row + pawnColor && m.to.col == m.from.col - 1) {
			list.push_back(Coord(m.from.row + pawnColor, m.from.col - 1));
			return true;
		}
		//is pawn located in its initial row on the chessboard
		else if (m.from.row == 1 || m.from.row == BOARD_SIZE - 2) {
			//first movement of a pawn, allowed movement by 1 or 2 fields, moves only forwards and kills crosswise
			//movement by 2 fields allowed for a pawn
			if (m.to.row == m.from.row + 2 * pawnColor && m.to.col == m.from.col) {
				list.push_back(Coord(m.from.row + pawnColor, m.from.col));
				list.push_back(Coord(m.from.row + 2 * pawnColor, m.from.col));
				return true;
			}
		}
		if (errorMessagesOn) { errorMessage(ErrorMessage::badPieceMovement); }
		return false;
	}
};


class FigureFactory {
public:
	static Figure *getFigure(char name) {
		switch (name) {
		case 'k':
			return new King(false);
		case 'K':
			return new King(true);
		case 'q':
			return new Queen(false);
		case 'Q':
			return new Queen(true);
		case 'b':
			return new Bishop(false);
		case 'B':
			return new Bishop(true);
		case 'n':
			return new Knight(false);
		case 'N':
			return new Knight(true);
		case 'r':
			return new Rook(false);
		case 'R':
			return new Rook(true);
		case 'p':
			return new Pawn(false);
		case 'P':
			return new Pawn(true);
		default:
			return new Figure();
		}
	}
};


void Board::init() {

	board[0][0] = FigureFactory::getFigure('r');
	board[0][1] = FigureFactory::getFigure('n');
	board[0][2] = FigureFactory::getFigure('b');
	board[0][3] = FigureFactory::getFigure('q');
	board[0][4] = FigureFactory::getFigure('k');
	board[0][5] = FigureFactory::getFigure('b');
	board[0][6] = FigureFactory::getFigure('n');
	board[0][7] = FigureFactory::getFigure('r');


	for (int i = 0; i < BOARD_SIZE; i++) {
		board[1][i] = FigureFactory::getFigure('p');
	}

	for (int i = 2; i < BOARD_SIZE - 2; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			board[i][j] = FigureFactory::getFigure(' ');
		}
	}


	for (int i = 0; i < BOARD_SIZE; i++) {
		board[BOARD_SIZE - 2][i] = FigureFactory::getFigure('P');
	}

	board[BOARD_SIZE - 1][0] = FigureFactory::getFigure('R');
	board[BOARD_SIZE - 1][1] = FigureFactory::getFigure('N');
	board[BOARD_SIZE - 1][2] = FigureFactory::getFigure('B');
	board[BOARD_SIZE - 1][3] = FigureFactory::getFigure('Q');
	board[BOARD_SIZE - 1][4] = FigureFactory::getFigure('K');
	board[BOARD_SIZE - 1][5] = FigureFactory::getFigure('B');
	board[BOARD_SIZE - 1][6] = FigureFactory::getFigure('N');
	board[BOARD_SIZE - 1][7] = FigureFactory::getFigure('R');

	if (BOARD_SIZE > 8) {
		for (int i = 8; i < BOARD_SIZE; i++) {
			board[0][i] = FigureFactory::getFigure(' ');
			board[BOARD_SIZE - 1][i] = FigureFactory::getFigure(' ');
		}
	}
}




//GLOBAL FUNCTIONS ---------------------------------------------------------------------------------

#ifdef _WIN32
void gotoXY(short x, short y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#else

void gotoXY(short x, short y) {
	cout << "\033[" << y << ";" << x << "f" << flush;
}

#endif


void clearLine(short y) {
	gotoXY(0, y);
	cout << setw(128) << " ";
	gotoXY(0, y);
}


void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}


void clearLinesFrom(short y, short count) {
	for (short i = 0; i < count; i++)
		clearLine(y + i);
}


void errorMessage(ErrorMessage::ErrorMessageTypes msg) {
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
		cout << "No piece on this square!" << endl;
		break;
	case ErrorMessage::wrongColorSelected:
		clearLine(20);
		cout << "This is not your piece!" << endl;
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
		cout << "One of yours pieces already occupies this field!" << endl;
		break;
	case ErrorMessage::isDeadlock:
		clearLine(20);
		cout << "Such a move would have made the king's check!" << endl;
		break;
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


int main() {
	Board b;
	Player whitePlayer(b);
	Player blackPlayer(b);
	bool endOfGame = false;
	do {
		endOfGame = whitePlayer.move();
		if (!endOfGame)
			endOfGame = blackPlayer.move();
	} while (!endOfGame);
	cout << "End of the game!" << endl;
	if (Player::getTurn()) {
		cout << "Black chess win!" << endl;
	}
	else {
		cout << "White chess win!" << endl;
	}
}