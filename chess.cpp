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
 2. Dokończyć funkcje validującą Board, tak aby uwzględniała walidacje figur oraz walidacje pól pomiędzy ruchem
 3. Zrobić walidacje pól pomiędzy ruchem, należy wykorzystać listę vector<Coord> list która jest uzupełniona polami do sprawdzenia.
	Dla większości figur jeśli pole nie jest puste to oznacza błąd, za wyjątkiem pionka: jeśli pionek wykona ruch na ukos to musi być tam pionek przeciwnika, jeśli 2 do przodu to sprawdza tak jak reszte figur.
 4. Dostosowac funkcję sprawdzającą szachowanie
 5. Dostosować zwracanie błędów dla gracza (w tej chwili zostały usunięte z funkcji walidująych figury)
 
 */




//LIBRARIES --------------------------------------------------------------------------------------
// important for VS
//#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>

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


//CLASS DECLARATIONS -----------------------------------------------------------------------------

class Board;
class Move;
class FigureFactory;
class Figure;
class King;
class Queen;
class Bishop;
class Knight;
class Rook;
class Pawn;

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
bool king(const Move &m, Board board, bool whites);
bool king(const Move &m, Board board);
bool queen(const Move &m, Board board);
bool bishop(const Move &m, Board board);
bool knight(const Move &m, Board board);
bool rook(const Move &m, Board board);
bool pawn(const Move &m, Board board, bool whites);
bool is_Deadlocked(const Move &m, Board board, bool whites);


//STRUCTURES AND CLASSES --------------------------------------------------------------------------
struct Coord {
    int row;
    int col;
    Coord() {}
    Coord(int row, int col){
        Coord::row = row;
        Coord::col = col;
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
    Move(string line) {
        from.col = line[0] - 'A';
        from.row = BOARD_SIZE - (line[1] - '1') - 1;
        to.col = line[2] - 'A';
        to.row = BOARD_SIZE - (line[3] - '1') - 1;
    }
    
    bool valid();
};

bool Move::valid() {
    
    if (from.col < 0 || from.col >= BOARD_SIZE) {
        errorMessage(ErrorMessage::coordBeyondBoard);
        return false;
    }
    else if (to.col < 0 || to.col >= BOARD_SIZE) {
        errorMessage(ErrorMessage::coordBeyondBoard);
        return false;
    }
    else if (from.row < 0 || from.row > BOARD_SIZE) {
        errorMessage(ErrorMessage::coordBeyondBoard);
        return false;
    }
    else if (to.row < 0 || to.row > BOARD_SIZE) {
        errorMessage(ErrorMessage::coordBeyondBoard);
        return false;
    }
    return true;
}



class Figure {
    char name;
public:
    
    virtual bool valid(const Move &m, vector<Coord>& list) {
        cout << "Something went wrong..." << endl;
        return false;
    };
    
    char& operator*() { return name; }
    
    
    Figure& operator=(const char name) {
        this->name = name;
        return *this;
    }
    
    friend ostream& operator<<(ostream& os, const Figure& figure);
};


ostream& operator<<(ostream& os, const Figure& figure) {
    os << figure.name;
    return os;
}



class King : public Figure {
public:
    bool valid(const Move &m, vector<Coord>& list) {
        
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
};


class Bishop : public Figure {
public:
    bool valid(const Move &m, vector<Coord>& list)
    {
        int col_diff = (m.to.col - m.from.col);
        int row_diff = (m.to.row - m.from.row);
        
        //basically in case of bishop the absolute value of vertical and horizontal shifts must be equal(diagonal move)
        if (abs(col_diff) != abs(row_diff)) {
            return false;
        }
        
        else if (row_diff > 0 && col_diff > 0) {
            for (int i = 1; i < abs(col_diff); i++) {
                list.push_back( Coord(m.from.row + i, m.from.col + i) );
            }
        }
        
        else if (row_diff < 0 && col_diff < 0) {
            for (int i = 1; i < abs(col_diff); i++) {
                list.push_back( Coord(m.from.row - i, m.from.col - i) );
            }
        }
        
        else if (row_diff < 0 && col_diff > 0) {
            for (int i = 1; i<abs(col_diff); i++) {
                list.push_back (Coord(m.from.row - i, m.from.col + i) );
            }
        }
        
        else if (row_diff > 0 && col_diff < 0) {
            for (int i = 1; i < abs(col_diff); i++) {
                list.push_back( Coord(m.from.row + i, m.from.col - i) );
            }
        }
        
        return true;
    }
};

class Queen : public Bishop{
public:
    bool valid(const Move &m, vector<Coord>& list)
    {
        if (Bishop::valid(m, list))
            return true;
        
        int col_diff = abs(m.to.col - m.from.col);
        int row_diff = abs(m.to.row - m.from.row);
        
        if (m.from.col != m.to.col && m.from.row != m.to.row) {
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
    bool valid(const Move &m, vector<Coord>& list) {
        
        if (abs(m.from.col - m.to.col) == 1 && abs(m.from.row - m.to.row) == 2)
            return true;
        
        if (abs(m.from.col - m.to.col) == 2 && abs(m.from.row - m.to.row) == 1)
            return true;
        return false;
    }
};

class Rook : public Figure {
public:
    bool valid(const Move &m, vector<Coord>& list) {
        
        int col_diff = abs(m.to.col - m.from.col);
        int row_diff = abs(m.to.row - m.from.row);
        
        if (m.from.col != m.to.col && m.from.row != m.to.row) {
            return false;
        }
        
        if (m.from.col > m.to.col) {
            for (int i = 1; i < col_diff; ++i) {
                list.push_back( Coord(m.from.row, m.from.col - i) );
            }
        }
        if (m.from.col < m.to.col) {
            for (int i = 1; i < col_diff; ++i) {
                list.push_back( Coord(m.from.row, m.from.col + i) );
            }
        }
        if (m.from.row > m.to.row) {
            for (int i = 1; i < row_diff; ++i) {
                list.push_back( Coord(m.from.row - i, m.from.col) );
            }
        }
        if (m.from.row < m.to.row) {
            for (int i = 1; i < row_diff; ++i) {
                list.push_back( Coord(m.from.row + i, m.from.col) );
            }
        }
        
        return true;
    }
};




class Board {
    
private:
    Figure* board;
    
    void display(ostream& os) const;
    bool reverse();
    void init();
    void makeMove(const Move& m);
    bool isPieceSelected(const Move &m, bool errorMessagesOn = true);
    bool isSquareAvailable(const Move &m, bool errorMessagesOn = true);
    bool valid(string& line);
    static bool whites;
public:
    
    Board(int boardSize) { board = new Figure[boardSize * boardSize]; whites = true; }
    void changeTurn() { whites = !whites; }
    Move getMove();
    // true = whites, false = blacks
    static bool getTurn() { return whites; }
    bool valid(const Move& m, bool errorMessagesOn);
    Board& operator=(const BoardOps boardOps);
    friend ostream& operator<<(ostream& os, const Board& board);
    Board& operator!();
    Board& operator+=(const Move&);
    Figure& operator()(int x, int y);
    Figure operator()(int x, int y) const;
};


bool Board::whites=true;


// Check if proper pawn is selected or space is empty
bool Board::isPieceSelected(const Move &m, bool errorMessagesOn)
{
    Board board = *this;
    char piece = *board(m.from.row, m.from.col);
    
    if (piece >= 'a' && piece <= 'z') {
        if (Board::getTurn() == true) {
            if(errorMessagesOn){errorMessage(ErrorMessage::wrongColorSelected);}
            return false;
        }
    }
    
    if (piece >= 'A' && piece <= 'Z') {
        if (Board::getTurn() == false) {
            if(errorMessagesOn){errorMessage(ErrorMessage::wrongColorSelected);}
            return false;
        }
    }
    
    if (piece == ' ') {
        if(errorMessagesOn){errorMessage(ErrorMessage::emptySpaceSelected);}
        return false;
    }
    
    return true;
}



// Check if pawn can enter selected square
bool Board::isSquareAvailable(const Move &m, bool errorMessagesOn)
{
    Board board = *this;
    char piece = *board(m.to.row, m.to.col);
    
    if (piece >= 'a' && piece <= 'z') {
        if (!Board::getTurn()) {
            if(errorMessagesOn){errorMessage(ErrorMessage::squareIsOccupied);}
            return false;
        }
    }
    else if (piece >= 'A' && piece <= 'Z' && Board::getTurn()) {
        if(errorMessagesOn){errorMessage(ErrorMessage::squareIsOccupied);}
        return false;
    }
    
    return true;
}



Board& Board::operator=(const BoardOps boardOps) {
    switch (boardOps) {
        case BoardOps::CLEAR_BOARD:
            break;
        case BoardOps::INIT_BOARD:
            init();
            break;
    }
    return *this;
}


ostream& operator<<(ostream& os, const Board& board) {
    clearScreen();
    board.display(os);
    return os;
}


Board& Board::operator!() {
    reverse();
    return *this;
}


Board& Board::operator+=(const Move& m) {
    makeMove(m);
    return *this;
}


Figure& Board::operator()(int row, int col) {
    return *(board + (col + row * BOARD_SIZE));
}


Figure Board::operator()(int row, int col) const {
    return *(board + (col + row * BOARD_SIZE));
}


// check if user input is in proper format
bool Board::valid(string& line)
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


Move Board::getMove()
{
    Move m;
    string line = "";
    do {
        if (Board::getTurn())
            cout << "White turn:" << endl;
        else
            cout << "Black turn:" << endl;
        
        getline(cin, line);
    } while (!valid(line));
    
    return m = Move(line);
}

bool Board::reverse()
{
    Board board = *this;
    const char figuresRowLow[BOARD_SIZE] = { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' };
    const char figuresRowUp[BOARD_SIZE] = { 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' };
    
    for (unsigned i = 0; i < BOARD_SIZE; i++) {
        if (tolower(*board(0, i)) != figuresRowLow[i] || tolower(*board(BOARD_SIZE - 1, i)) != figuresRowLow[i])
            return false;
        if (tolower(*board(1, i)) != 'p' || tolower(*board(BOARD_SIZE - 2, i)) != 'p')
            return false;
    }
    
    if (*board(0, 0) == 'r') {
        for (unsigned i = 0; i < BOARD_SIZE; i++)
            board(0, i) = figuresRowUp[i];
        for (unsigned i = 0; i < BOARD_SIZE; i++)
            board(1, i) = 'P';
        
        for (unsigned i = 0; i < BOARD_SIZE; i++)
            board(BOARD_SIZE - 1, i) = figuresRowLow[i];
        for (unsigned i = 0; i < BOARD_SIZE; i++)
            board(BOARD_SIZE - 2, i) = 'p';
    }
    else {
        for (unsigned i = 0; i < BOARD_SIZE; i++)
            board(0, i) = figuresRowLow[i];
        for (unsigned i = 0; i < BOARD_SIZE; i++)
            board(1, i) = 'p';
        
        for (unsigned i = 0; i < BOARD_SIZE; i++)
            board(BOARD_SIZE - 1, i) = figuresRowUp[i];
        for (unsigned i = 0; i < BOARD_SIZE; i++)
            board(BOARD_SIZE - 2, i) = 'P';
    }
    
    return true;
}

void Board::makeMove(const Move& m)
{
    Board board = *this;
    char figure = *board(m.from.row, m.from.col);
    board(m.from.row, m.from.col) = ' ';
    board(m.to.row, m.to.col) = figure;
}

//displays board - takes array board[BOARD_SIZE][BOARD_SIZE]
// and reads its contents, and displays on the screen
void Board::display(ostream& os) const
{
    clearScreen();
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
    
    //memset(this->board, ' ', sizeof(char) * BOARD_SIZE * BOARD_SIZE);
    for (unsigned i = 0; i < BOARD_SIZE; i++) {
        board(0, i) = figuresRow[i];
    }
    
    for (unsigned i = 0; i < BOARD_SIZE; i++) {
        board(1, i) = 'p';
    }
    
    for(unsigned i=0; i<BOARD_SIZE; i++){
        for(unsigned j=2; j<BOARD_SIZE-2; j++){
            board(j,i) = ' ';
        }
    }
    
    
    for (unsigned i = 0; i < BOARD_SIZE; i++) {
        board(BOARD_SIZE - 2, i) = 'P';
    }
    
    for (unsigned i = 0; i < BOARD_SIZE; i++) {
        board(BOARD_SIZE - 1, i) = toupper(figuresRow[i]);
    }
}

class Pawn : public Figure {
public:
    bool valid(const Move &m, vector<Coord>& list) {
        
        int pawnColor = 1;
        if (Board::getTurn()) pawnColor = -1;
        
        // pawn moves 1 square forwards
        if (m.to.row == m.from.row + pawnColor && m.to.col == m.from.col) {
            list.push_back( Coord(m.from.row + pawnColor, m.from.col) );
            return true;
        }
        // pawn moves crosswise and makes a kill
        else if (m.to.row == m.from.row + pawnColor && m.to.col == m.from.col + 1) {
            list.push_back( Coord(m.from.row + pawnColor, m.from.col + 1) );
            return true;
        }
        else if (m.to.row == m.from.row + pawnColor && m.to.col == m.from.col - 1) {
            list.push_back( Coord(m.from.row + pawnColor, m.from.col - 1) );
            return true;
        }
        
        //is pawn located in its initial row on the chessboard
        else if (m.from.row == 1 || m.from.row == BOARD_SIZE - 2) {
            //first movement of a pawn, allowed movement by 1 or 2 fields, moves only forwards and kills crosswise
            //movement by 2 fields allowed for a pawn
            if (m.to.row == m.from.row + 2 * pawnColor && m.to.col == m.from.col) {
                list.push_back( Coord(m.from.row + pawnColor, m.from.col) );
                list.push_back( Coord(m.from.row + 2 * pawnColor, m.from.col) );
                return true;
            }
        }
        
        return false;
    }
};



class FigureFactory {
public:
    static Figure* getFigure(char name)
    {
        switch (name) {
            case 'K': return new King();
            case 'Q': return new Queen();
            case 'B': return new Bishop();
            case 'N': return new Knight();
            case 'R': return new Rook();
            case 'P': return new Pawn();
        }
        return new Figure();
    }
};


// Check if move of figure is valid according to chess rules
bool Board::valid(const Move& m, bool errorMessagesOn=true) {
    
    Board board = *this;
    vector<Coord> list;
    Figure* figure = FigureFactory::getFigure(*board(m.from.row, m.from.col));
    
    if (!(isPieceSelected(m, errorMessagesOn))) {
        return false;
    }
    
    if (!(isSquareAvailable(m, errorMessagesOn)))
        return false;
    
    if (!figure->valid(m, list)) //TODO ?dolozyc wylaczanie errorMessages?
        return false;
    
    
    //początek dopisywania kodu walidującego pola na szachownicy
    int pion = m.to.row - m.from.row; //jakie przemieszczenie w pionie o ile pol
    int poziom = m.to.col - m.from.col; //jakie przemieszczenie w poziomie o ile pol
    //czy na koncowym polu ruchu nie stoi bierka swojego koloru
    if(*board(m.to.row,m.to.col)!=' ' && islower(*board(m.to.row, m.to.col)) == islower(*board(m.from.row, m.from.col))){
        if(errorMessagesOn){errorMessage(ErrorMessage::squareIsOccupied);}
        return false;
    }
    
    
    int stepH = 0;
    if(m.from.col-m.to.col){stepH = (m.to.col - m.from.col)/abs(m.from.col - m.to.col);}
    int stepV = 0;
    if(m.from.row-m.to.row){stepV = (m.to.row - m.from.row)/abs(m.from.row - m.to.row);}
    
    
    //jezeli na koncowym polu ruchu nie stoi bierka swojego koloru to testujemy pola na sciezce ruchu figury
    //jezeli tylko ruch w pionie
    if(poziom==0){ //jezeli nie ma przemieszczenia w poziomie => tzn tylko jest w pionie
        cout << "Ruch w pionie" << endl;
        //czy nic nie stoi na drodze bierki
        int i = m.from.row+stepV;
        while(i!=m.to.row){
            cout << "Analizowane pole ->" << i << ' ' << m.to.col<< endl;
            cout << "Zawartosc pola" << *board(i, m.to.col) << endl;
            cout << "Licznik petli" << i - (m.from.row+1) << endl;
            if(*board(i,m.to.col)!=' '){
                if(errorMessagesOn){errorMessage(ErrorMessage::movementOverFigure);}
                return false;
            }
            i+=stepV;
        }
    }
    //jezeli ruch tylko w poziomie
    else if(pion==0){
        int i = m.from.col+stepH;
        while(i!=m.to.row){
            if(*board(m.to.row, i)){
                if(errorMessagesOn){errorMessage(ErrorMessage::movementOverFigure);}
                return false;
            }
            i+=stepH;
        }
    }
    //ruch jest w pionie i w poziomie
    else{
        //czy ruch wykonuje skoczek? jezeli tak, to nie sprawdzamy czy na jego drodze cos stoi bo moze stac
        if(*board(m.from.row, m.from.col)=='n' || *board(m.from.row,m.from.col)=='N'){
            return true;
        } else{
            //jak nie skoczek to musimy sprawdzac
            //ruch jest tylko po przekatnej
            int i = m.from.row+stepV;
            int j = m.from.col+stepH;
            while(i!=m.to.row && j!=m.to.col){
                if(*board(i,j)==' '){
                    if(errorMessagesOn){errorMessage(ErrorMessage::movementOverFigure);}
                    return false;
                }
                i+=stepV;
                j+=stepH;
            }
        }
    }
    
    
    return true;
}



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
 figure = board[i*BOARD_SIZE+j];
 
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
 */


bool endOfGame(Board board)
{
    return false;
}

int main()
{
    Board b(8);
    b = BoardOps::INIT_BOARD;
    cout << b;
    
    Move m;
    while (true) {
        do {
            do {
                m = b.getMove();
            } while (!m.valid());
        } while (!b.valid(m));
        
        b += m;
        cout << b;
        b.changeTurn();
    }
    cout << "Press Enter to Continue";
    cin.ignore();
    
}
