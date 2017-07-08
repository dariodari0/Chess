//     A   B   C   D   E   F   G   H
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
//     A   B   C   D   E   F   G   H


//LIBRARIES --------------------------------------------------------------------------------------
// important for VS
//#include "stdafx.h"
#include <iostream>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

//CONSTANTS ----------------------------------------------------------------------------------------
const int BOARD_SIZE = 8;
bool white;

//GLOBAL VARIABLES ---------------------------------------------------------------------------------

char board[BOARD_SIZE][BOARD_SIZE] = {' '};
const char startup[8][8] = { 'r', 'b', 'n', 'q', 'k', 'n', 'b', 'r', 'p', 'p','p','p','p','p','p', 'p', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'R', 'B', 'N', 'Q', 'K', 'N', 'B', 'R'};

struct Move {
    char fromCh;
    int fromInt;
    char toCh;
    int toInt;
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

bool pawn(const Move &m, char board[][BOARD_SIZE], bool whites){
    //board[m.fromCh][m.fromInt]
    //czy gra biały czy czarny

    //czy pionek należy do odpowiedniego gracza

    //czy pionek nie może szachować króla przeciwnika

    //czy pionek wykonuje swój pierwszy ruch w grze, wtedy moze iść do przodu o 2 pola lub 1 pole - do przodu lub po skosie

    //jeżeli pionek już nie jest na swojej pozycji startowej to rusza się o 1 pole

    //jeżeli pionek doszedł do końca szachownicy to staje się pp albo PP - pionkiem który może chodzić do tyłu

    //pionek nie może przeskakiwać własnych figur ani pionów

    return true;
}

bool pPawn(const Move &m, char board[][BOARD_SIZE], bool whites){

    //czy gra bialy czy czarny

    //czy pionek nalezy do wlasciwego gracza

    //czy pionek nie może szachować króla przeciwnika

    //pionek może robić ruch tylko o 1 pole ale może chodzić też do tyłu, nie może przeskakiwać własnych figur ani pionów

    return true;
}

bool king(const Move&m, char board[][BOARD_SIZE], bool whites){

    //czy gra biały czy czarny

    //czy król należy do właściwego gracza

    //czy pionek nie może szachować króla przeciwnika

    //czy analizowany ruch jest dostępny dla króla

    //król może się poruszać o 1 pole, byle nie wyjść za szachownicę, dowolny kierunek, nie może przeskakiwać własnych pionów ani figur

    return true;
}

bool queen(const Move&m, char board[][BOARD_SIZE], bool whites){
    //czy gra biały czy czarny

    //czy hetman/królówka należy właściwego gracza

    //czy nie może szachować króla przeciwnika

    //WYKORZYSTAC KOD DLA GONCA I WIEZY, KROLOWKA JEST JEDNOCZESNIE GONCEM I WIEZA

    //Hetman może poruszać się w dowolnym kierunku (poziomo, pionowo oraz na ukos) o dowolną liczbę wolnych pól,

    // jest więc jakby jednocześnie i gońcem i wieżą. Hetman bije bierkę przeciwnika, zajmując jej pole.

    //czy planowany ruch jest na liście dostępnych ruchów królówki

    //królówka rusza się na wszystkie strony ale tylko po liniach prostych, nie może przeskakiwać własnych figur ani pionów

    return true;
}

bool rook(const Move&m, char board[][BOARD_SIZE], bool whites){
    //czy gra biały czy czarny

    //czy wieża należy do właściwego gracza

    //czy nie może szachować króla przeciwnika

    //Wieża porusza się po liniach pionowych i poziomych, w dowolnym kierunku, o dowolną liczbę niezajętych pól.

    // Wieża bije bierkę przeciwnika, zajmując jej pole.

    //Król może poruszać się o jedno pole w dowolnym kierunku (pionowo, poziomo lub na ukos), nie może jednak wejść na pole
    // atakowane przez bierkę przeciwnika. Jak wszystkie inne bierki, król bije bierkę przeciwnika wchodząc na pole przez
    // nią zajmowane (z zastrzeżeniem, że nie może to pole być atakowane przez inną bierkę przeciwnika).
    // Król może również wykonać specyficzne posunięcie, zwane roszadą.
    //Jeśli król jest atakowany przez bierkę (bierki) przeciwnika, mówi się, że jest w szachu lub jest szachowany.
    //OSOBNA FUNKCJA SPRAWDZAJĄCA CZY JAKAŚ BIERKA NIE ATAKUJE KRÓLA, WTEDY POPRAWNY JEST TYLKO RUCH RATUJĄCY KRÓLA
    // W takiej sytuacji gracz ma obowiązek bronić króla (nie może wykonać innego ruchu) przez przesunięcie go na inne pole,
    // zbicie atakującej bierki przeciwnika lub przesłonięcie ataku własną bierką.
    // W odróżnieniu od innych bierek król nie może szachować króla przeciwnika.
    // Na pustej szachownicy niezależnie od miejsca wieża atakuje zawsze 14 pól.


    //czy analizowany ruch jest dopuszczalny dla wieży

    //wieża nie może przeskakiwać własnych figur ani pionów

    return true;
}

bool bishop(const Move&m, char board[][BOARD_SIZE], bool whites){
    //goniec
    //Goniec porusza się wyłącznie po przekątnych pól, w dowolnym kierunku, o dowolną liczbę niezajętych pól.
    // Gońce nie mogą przeskakiwać nad innymi bierkami. Goniec bije bierkę przeciwnika, zajmując jej pole.
    //ma dostęp tylko do 32 pól, wieża jest silniejsza bo ma dostęp do wszystkich

    //czy gra biały czy czarny

    //czy goniec należy do właściwego gracza

    //czy goniec nie może szachować króla przeciwnika

    //czy analizowany ruch jest dozwolony dla gońca

    return true;
}


bool knight(const Move&m, char board[][BOARD_SIZE], bool whites){
    //Ruch skoczka można opisać jako krok o jedno pole w pionie lub poziomie, a następnie drugi krok na ukos,
    // w kierunku oddalającym go od pola startowego. Niekiedy mówi się, że porusza się on „po literze L”.
    // Przemieszcza się zawsze na pole przeciwnego koloru, pole to jest dodatkowo najbliższym polem o przeciwnym do
    // wyjściowego kolorze, z wyłączeniem z nim sąsiadujących. Skoczek, tak jak każda inna figura, bije bierkę
    // przeciwnika zajmując jej pole i porusza się przy biciu według tejże reguły, co i przy zwykłym ruchu.

    //Skoczek jest niezwykły w porównaniu z innymi bierkami szachowymi.
    // W przeciwieństwie do innych figur szachowych skoczek może zignorować bierki stojące mu na drodze i przeskakiwać przez nie.
    // Poza tym jest jedyną figurą, która może rozpocząć partię (inną bierką o tej możliwości jest pion).

    //czy gra biały czy czarny

    //czy skoczek należy do właściwego gracza

    //czy skoczek może zaszachować króla

    //czy analizowny ruch jest dozwolony dla skoczka

    return true;
}



// Ta funkcja sprawdza czy ruch jest poprawny pod kątem:
// - czy na polu startowym jest moja figura
// - czy pole docelowe jest wolne lub czy stoi na nim figura przeciwnika
// - czy ruch dla danej figury jest dopuszczalny (pomijamy roszadę, ale nalezy uwzględnić, że pierwszy ruch każdego piona może być o dwie pozycje do przodu)
bool valid(const Move& m, char board[][BOARD_SIZE], bool whites)
{
    //sprawdzanie jaka figura jest przewidziana do ruchu
    //w zależności od figury uruchomiona odpowiednia funkcja weryfikująca
    return true;
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

    if(m.fromCh < 'A' || m.fromCh >= 'A' + BOARD_SIZE){
        return false;
    }
    else if(m.toCh < 'A' || m.toCh >= 'A' + BOARD_SIZE ){
        return false;
    }
    else if(m.fromInt < 1 || m.fromInt > BOARD_SIZE){
        return false;
    }
    else if(m.toInt < 1 || m.toInt > BOARD_SIZE){
        return false;
    }
    return true;
}



// Sprawdza czy linia jest w postaci litera liczba litera liczba oraz zamienia litery małe na wielkie, ewentualnie usuwa także spacje np. c    1    D 3 zmiania na C1D3
bool valid(char line[])
{
    int length = 0;
    int i=0, i1 = 0;
    removeSpaces(line);

    //length of array with characters
    while(line[length]!='\0'){
        length++;
    }

    //replace small letters into capital letters, no verification yet as to whether it is within BOARD_SIZE
    for(int j=0; j<length; j++){
        if(line[j]>='a' && line[j]<='z'){
            line[j] = toupper(line[j]);
        }
    }

    while(line[i]>='A' && line[i]<='Z'){
        i++;
    }

    if(i==0){
        cout << "Zly format wspolrzednych ruchu" << endl << flush;
        return false;
    }
    else{
        i1 = i;
    }

    while(line[i]>='0' && line[i]<='9'){
        i++;
    }

    if(i==i1){
        cout << "Zly format wspolrzednych ruchu" << endl << flush;
        return false;
    }
    else
    {
        i1 = i;
    }

    while(line[i]>='A' && line[i]<='Z'){
        i++;
    }

    if(i==i1){
        cout << "Zly format wspolrzednych ruchu" << endl << flush;
        return false;
    }
    else{
        i1 = i;
    }

    while(line[i]>='0' && line[i]<='9'){
        i++;
    }

    if(i==i1){
        cout << "Zly format wspolrzednych ruchu" << endl << flush;
        return false;
    }
    else
    {
        return true;
    }


}



//jawna translacja litery ze struktury Move do współrzędnych używanych na szachownicy
int translateLetter(char letter) {
    int result = letter - 'A';
    if (result >= 0 && result < BOARD_SIZE) {
        return result;
    }
    return -1;

}



//jawna transalcja cyfry ze struktury Move do współrzędnych używanych na szachownicy
int translateInt(int number) {

    if (number < 1 && number > BOARD_SIZE) {
        cout <<  "Nie ma takiego numeru wiersza na szachownicy!" << endl << flush;
        return -1;
    }
    //change numbering of rows - in MOVE struct there was numbering from 1 to BOARD_SIZE
    //we change it initially to numbering from 0 to BOARD_SIZE - 1
    //reverse numbers of rows to correctly address the array board
    return BOARD_SIZE - number;
}



// zamienia ciag znaków w postaci litera liczba litera liczba na strukturę Move
Move readMove(const char line[])
{
    char fromChars[20] = {' '};
    char toChars[20] = {' '};
    int fromInt = 0;
    int toInt = 0;
    int counter = 0;
    int i = 0;


    //read first symbol (letters)
    while(line[i]>='A' && line[i]<'Z'){
        if(line[i]==' '){
            i++;
        }
        fromChars[counter] = line[i];
        counter++;
        line++;
    }

    //read second symbol (integer)
    while(line[i]>='0' && line[i]<'9'){
        if(line[i]==' '){
            i++;
        }
        fromInt = fromInt*10 + (line[i]-'0');
        i++;
    }

    counter = 0;
    //read third symbol (letters)
    while(line[i]>='A' && line[i]<'Z'){
        if(line[i]==' '){
            i++;
        }
        toChars[counter] = line[i];
        counter++;
        i++;
    }

    //read fourth symbol (integer)
    while(line[i]>='0' && line[i]<'9'){
        if(line[i]==' '){
            i++;
        }
        toInt = toInt*10 + (line[i]-'0');
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
    int columnFrom = translateLetter(m.fromCh);
    int columnTo = translateLetter(m.toCh);
    int rowFrom = translateInt(m.fromInt);
    int rowTo = translateInt(m.toInt);
    char figure = board[rowFrom][columnFrom];
    board[rowFrom][columnFrom] = ' ';
    board[rowTo][columnTo] = figure;
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
    for(letter = 'A'; letter < 'A'+ BOARD_SIZE; letter++)
        cout << "   " <<  letter;
    cout << "      \n";

    //row with a delimited in a chessboard  "    +---+---+---+---+---+---+---+---+   \n";
    cout << "    ";
    for( i='A'; i<'A'+ BOARD_SIZE; i++){
        cout << "+---";
    }
    cout << "+   \n";

    //now we take the array that keeps actual positions of figures and display it on the chessboard

    for( i=0; i < BOARD_SIZE; i++) {

        cout << " " << BOARD_SIZE - i << " ";

        for (j = 0; j < BOARD_SIZE; j++) {
            cout << " " << "|" << " " << board[i][j];
        }
        cout << " " << "|" << " " << BOARD_SIZE - i << " ";
        cout << "\n";


        //now we delimit each row with figures with a delimiter "    +---+---+---+---+---+---+---+---+   \n";
        cout << "    ";
        for(k='A'; k<'A'+ BOARD_SIZE; k++){
            cout << "+---";
        }
        cout << "+   \n";

    }

    //finally the bottom letters

    //row with letters that reprezenting headers of columns
    cout << "   ";
    for(letter = 'A'; letter < 'A'+ BOARD_SIZE; letter++)
        cout << "   " <<  letter;
    cout << "      \n";

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


void doMove(char board[][BOARD_SIZE])
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

bool endOfGame(char board[][BOARD_SIZE])
{
	return false;
}

int main() 
{
	initBoard(board);

	do {
		displayBoard(board);
		doMove(board);
        !white;
    } while (!endOfGame(board));

}