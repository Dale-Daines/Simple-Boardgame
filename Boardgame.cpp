//Game is similar to Hex
//Objective is to be the first player to link their sides (Top to Bottom or Left to Right)


#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>


using namespace std;

class Board {
	const static int WIDTH=3;
	const string RED="R";
	const string REDNAME="Red";
	const string BLUE="B";
	const string BLUENAME="Blue";
	const string BLANK="";
	const string ERROR="ERROR";
	int ROWS, COLS;
	int** table;
	bool** winTable;
	public:
		Board();
		~Board();
		void display();
		void displayWin(string x);
		void game();
		void player(int x);
	private:
		void playerVsPlayer();
		void playerVsRandom();
		int checkWin();
		void clearWin();
		bool checkBase(int x);
		void checkTop(int x);
		void checkLeft(int x);
		bool checkRed(int x);
		bool checkBlue(int x);
		bool pathCheck(int x);
		bool testLeft(int x, int y);
		bool testRight(int x, int y);
		bool testTopRight(int x, int y);
		bool testTopLeft(int x, int y);
		bool testBottomRight(int x, int y);
		bool testBottomLeft(int x, int y);
		bool victory(int x);
		void endGame(int x);
		void randomPlayer(int x);
		
};

//Constructor for Board - Takes input on board size
Board::Board(void) {
	srand(time(NULL));
	do {
		cout << "Please enter the number of columns for the game board ( 2 - 15 )" << endl;
		cin >> COLS;
		cout << "Please enter the number of rows for the game board ( 2 - 15 )" << endl;
		cin >> ROWS;
	}while ( COLS < 2 && ROWS < 2 && COLS > 15 && ROWS > 15 );
	//Create empty board
	table = new int*[ROWS];
	winTable = new bool*[ROWS];
	for (int i=0; i < ROWS; i++) {
		table[i] = new int[COLS];
		winTable[i] = new bool[COLS];
	}

	for (int i = 0; i < ROWS; i ++) {
		for (int j = 0; j < COLS; j++)   {
			table[i][j] = 0;
			winTable[i][j] = false;
		}
	}
}

//Destructor for the dynamic arrays
Board::~Board(void) {
	for (int i=0; i < ROWS; i++ ) {
		delete[] table[i];
		delete[] winTable[i];
		table[i] = NULL;
		winTable[i] = NULL;
	}
	delete table;
	delete winTable;
	table = NULL;
	winTable = NULL;
}


//Chooses Gametype
void Board::game() {
	int gameType = 0;
	do {
		cout << "Please enter your game preference." << endl << "1 - vs Players, 2 - vs random bot" << endl;
		cin >> gameType;
	}while ( gameType < 1 || gameType > 2 );
	
	if ( gameType == 1 ) {
		playerVsPlayer();
	}
	if ( gameType == 2 ) {
		playerVsRandom();
	}
		
}

//Runs player vs player functions
void Board::playerVsPlayer() {
	int turn = 1;
	while ( checkWin() == 0 ) {
		
		display();
		player(turn);
		if ( turn == 1 )
			turn = -1;
		else
			turn = 1;
	}
	if ( checkWin() == 1 ) {
		displayWin(RED);
		endGame(1);
	}	
	if ( checkWin() == -1 ) {
		displayWin(BLUE);
		endGame(-1);
	}
}

//Runs player vs random functions
void Board::playerVsRandom() {
	int colour, random, turn=1;
	while ( colour > 1 || colour < -1 || colour == 0 ) {
	cout << "Do you wish to be Red or Blue? (1 for red, -1 for blue)" << endl;
	cin >> colour;
	}
	if ( colour == 1) {
		random = -1;
	}
	else
	{
		random = 1;
	}
	while ( checkWin() == 0 ) {
		//Code for player as 2nd
		if ( colour == -1 ) {
			display();
			if ( turn == 1 ) {
				randomPlayer(random);	
				turn = -1;
			}
			else {
				player(colour);
				turn = 1;
			}
		}
		//Code for player as 1st
		if ( colour == 1 ) {
			display();
			if ( turn == -1 ) {
				randomPlayer(random);	
				turn = 1;
			}
			else {
				player(colour);
				turn = -1;
			}
		}
	}
	if ( checkWin() == 1 ) {
		displayWin(RED);
		endGame(1);
	}	
	if ( checkWin() == -1 ) {
		displayWin(BLUE);
		endGame(-1);
	}
}

//Displays game board
void Board::display() {
	int offset = 0;
	cout << setw(WIDTH) << " ";
	for (int i = 1; i <= COLS; i++){
		cout << setw(WIDTH) << i << " ";
	}
	cout << endl;
	for (int i = 0; i <= COLS; i++){
		cout << setw(WIDTH) << "-" << "-";
	}
	cout << endl;
	for (int i = 0; i < ROWS; i ++) {
		for (int k = 0; k < offset; k++) {
			cout << setw(WIDTH/2) << "";
		}
		cout << setw(WIDTH) << i+1 << "|";
		for (int j = 0; j < COLS; j++)   {
			if (table[i][j] == 1) {
				cout << setw(WIDTH) << RED;
			}
			else
			{
				if (table[i][j] == -1) {
					cout << setw(WIDTH) << BLUE;
				}
				else
				{
					cout << setw(WIDTH) << BLANK;
				}
			}
			cout << "|";
		}
	cout << endl;
	offset = offset + 2;
	}
}

//Displays winning players positions
void Board::displayWin(string x) {
	int offset = 0;
	string winner = x;
	cout << setw(WIDTH) << " ";
	for (int i = 1; i <= COLS; i++){
		cout << setw(WIDTH) << i << " ";
	}
	cout << endl;
	for (int i = 0; i <= COLS; i++){
		cout << setw(WIDTH) << "-" << "-";
	}
	cout << endl;
	for (int i = 0; i < ROWS; i ++) {
		for (int k = 0; k < offset; k++) {
			cout << setw(WIDTH/2) << "";
		}
		cout << setw(WIDTH) << i+1 << "|";
		for (int j = 0; j < COLS; j++)   {
			if (winTable[i][j] == true) {
				cout << setw(WIDTH) << winner;
			}
			else
			{
				cout << setw(WIDTH) << BLANK;
			}
			cout << "|";
		}
	cout << endl;
	offset = offset + 2;
	}
}


//Takes input from player and places on the board
void Board::player(int x) {
	int col, row, occupied;
	string name = ERROR;
	if ( x == 1 ) {
		name = REDNAME;
	}
	if ( x == -1) {
		name = BLUENAME;
	}
	do{
		cout << name << " player. Please insert the column of your move." << endl;
		cin >> col;
		col--;
		cout << "Please insert the row of your move." << endl;
		cin >> row;
		row--;

		if ( row < ROWS && col < COLS && row > -1 && col > -1 ) {
			if (table[row][col] == 0)
			{
				table[row][col] = x;
				occupied = 0;
			}
			else
			{
				cout << "That move is taken, please insert another." << endl;
				occupied = 1;
			}
		}
		else
		{
			cout << "Please play a move in the range of the board." << endl;
			occupied = 1;
		}

	}while (occupied == 1);
}

//Checks for victory conditions
int Board::checkWin() {
	if ( checkBase(1) ) {
		if ( pathCheck(1) ) {
		    return 1;   
		}
	}
	if ( checkBase(-1) ) {
		if ( pathCheck(-1) ) {
			return -1;
		}
	}
	return 0;
}

//Empties winTable
void Board::clearWin() {
	for (int i = 0; i < ROWS; i ++) {
		for (int j = 0; j < COLS; j++)   {
			winTable[i][j] = false;
		}
	}
}

//Checks colours touching top and bottom - requirement to win
bool Board::checkBase(int x) {
	if ( x == 1 ) {
		if ( checkRed(x) ) {
			return true;
		}
	}
	if ( x == -1 ) {
		if ( checkBlue(x) ) {
			return true;
		}
	}
	return false;
}

//Checks for red presence on top and bottom
bool Board::checkRed(int x) {
	bool top = false;
	bool bottom = false;
	for (int i=0; i < COLS; i++) {
		if (table[0][i] == x) {
			top = true;
		}
	}
	for (int i=0; i < COLS; i++) {
		if (table[ROWS-1][i] == x) {
			bottom = true;
		}
	}
	if (top == true && bottom == true ) {
		return true;
	}
	else
	{
		return false;
	}
}

//Checks for blue presence on left and right
bool Board::checkBlue(int x) {
	bool left = false;
	bool right = false;
	for (int i=0; i < ROWS; i++) {
		if (table[i][0] == x) {
			left = true;
		}
	}
	for (int i=0; i < ROWS; i++) {
		if (table[i][COLS-1] == x) {
			right = true;
		}
	}
	if (left == true && right == true ) {
		return true;
	}
	else
	{
		return false;
	}
}


//Creates the baseline for the win table (Top to Bottom)
void Board::checkTop(int x) {
	for (int i=0; i < COLS; i++) {
		if (table[0][i] == x) {
			winTable[0][i] = true;
		}
	}
}

//Creates the baseline for the win table (Left to Right)
void Board::checkLeft(int x) {
	for (int i=ROWS-1; i > -1; i--) {
		if (table[i][COLS-1] == x) {
			winTable[i][COLS-1] = true;
		}
	}
}


//Checks for path from top to bottom
bool Board::pathCheck(int x) {
	clearWin();
	if ( x == 1 ) {
		checkTop(x);
	}
	if ( x == -1 ) {
		checkLeft(x);
	}
	
	//Runs tests enough times so wins don't slip through
	for (int k=0; k < ROWS + COLS; k++ ) {
		//Tests from top to bottom
		for (int i = 0; i < ROWS; i ++) {
			for (int j = 0; j < COLS; j++)   {
				if ( table[i][j] == x ) {
					if ( testLeft(i, j) )
						winTable[i][j] = true;
					if ( testRight(i, j) )
						winTable[i][j] = true;
					if ( testTopRight(i, j) )
						winTable[i][j] = true;
					if ( testTopLeft(i, j) )
						winTable[i][j] = true;
					if ( testBottomLeft(i, j) )
						winTable[i][j] = true;
					if ( testBottomRight(i, j) )
						winTable[i][j] = true;
				}
			}
		}
		//Tests from right to left
		for (int i = COLS-1; i >= 0; i--) {
			for (int j = ROWS-1; j >= 0; j--)   {
				if ( table[j][i] == x ) {
					if ( testLeft(j, i) )
						winTable[j][i] = true;
					if ( testRight(j, i) )
						winTable[j][i] = true;
					if ( testTopRight(j, i) )
						winTable[j][i] = true;
					if ( testTopLeft(j, i) )
						winTable[j][i] = true;
					if ( testBottomLeft(j, i) )
						winTable[j][i] = true;
					if ( testBottomRight(j, i) )
						winTable[j][i] = true;
				}
			}
		}
	}
	
	if ( victory(x) ) {
		return true;
	}
	return false;
	
}

//Tests cell to the left for links
bool Board::testLeft(int x, int y) {
	if ( y < 1 )
		return false;
	if ( winTable[x][y-1] == true ) {
		return true;
	}
	else
	{
		return false;
	}
}

//Tests cell to the right for links
bool Board::testRight(int x, int y) {
	if ( y >= COLS-1 )
		return false;
	if ( winTable[x][y+1] == true ) {
		return true;
	}
	else
	{
		return false;
	}
}

//Tests cell to the top left for links
bool Board::testTopLeft(int x, int y) {
	if ( x < 1 )
		return false;
	if ( winTable[x-1][y] == true ) {
		return true;
	}
	else
	{
		return false;
	}
}

//Tests cell to the top right for links
bool Board::testTopRight(int x, int y) {
	if ( x < 1 || y >= COLS-1 )
		return false;
	if ( winTable[x-1][y+1] == true ) {
		return true;
	}
	else
	{
		return false;
	}
}

//Tests cell to the bottom left for links
bool Board::testBottomLeft(int x, int y) {
	if ( x >= ROWS-1 || y < 1 )
		return false;
	if ( winTable[x+1][y-1] == true ) {
		return true;
	}
	else
	{
		return false;
	}
}

//Tests cell to the bottom right for links
bool Board::testBottomRight(int x, int y) {
	if ( x >= ROWS-1 )
		return false;
	if ( winTable[x+1][y] == true ) {
		return true;
	}
	else
	{
		return false;
	}
}

//Checks for token presence on all levels, then decides win.
bool Board::victory(int x) {
	bool rowCheck = false;
	int connections = 0;
	//Test top to bottom
	if ( x == 1 ) {
		for (int i = 0; i < ROWS; i ++) {
			rowCheck = false;
			for (int j = 0; j < COLS; j++)   {
				if ( winTable[i][j] == true && rowCheck == false ) {
					rowCheck = true;
					connections++;
				}
			}
		}
	}
	//Test left to right
	if ( x == -1 ) {
		for (int i = 0; i < COLS; i ++) {
			rowCheck = false;
			for (int j = 0; j < ROWS; j++)   {
				if ( winTable[j][i] == true && rowCheck == false ) {
					rowCheck = true;
					connections++;
				}
			}
		}
	}
	if ( connections == ROWS )
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Prints the correct winner at the end of the game
void Board::endGame(int x) {
	string name = ERROR;
	if ( x == 1 ) {
		name = REDNAME;
	}
	if ( x == -1) {
		name = BLUENAME;
	}
	
	cout << name << " Wins" << endl;
}

//Code that makes the random Player work - chooses a random unoccupied square
void Board::randomPlayer(int x) {
	int col, row, occupied;
	do{
		col = rand() % COLS;
		row = rand() % ROWS;

		if ( row < ROWS && col < COLS && row > -1 && col > -1 ) {
			if (table[row][col] == 0)
			{
				table[row][col] = x;
				occupied = 0;
			}
			else
			{
				occupied = 1;
			}
		}
		else
		{
			occupied = 1;
		}

	}while (occupied == 1);
	cout << "Computer plays " << col+1 << ", " << row+1 << endl;
}



int main() {
	Board Board;
	Board.game();
	return 0;
}
