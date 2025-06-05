#pragma once
#include <iostream>
#ifdef _WIN32
#endif
#include <string>
#define CR_NO_PIECE         11 
#define CR_WRONG_TURN       12  
#define CR_SAME_COLOR       13 
#define CR_INVALID_MOVE     21  
#define CR_SELF_CHECK       31  
#define CR_OPPONENT_CHECK   41  
#define CR_MOVE_OK          42

using std::cout;
using std::cin; 
using std::endl;
using std::string; 

const int _SIZE = 21;

class Chess {
	unsigned char m_board[_SIZE][_SIZE] = { 0 };
	bool m_turn = true;
	string m_boardString;
	string m_input;
	string m_msg = "\n";
	string m_errorMsg = "\n";
	int m_codeResponse;
	string m_best;

	void clear() const;
	void setFrames();
	void setPieces();
	void show() const;
	void showAskInput() const;
	bool isSame() const;
	bool isValid() const;
	bool isExit() const;
	void excute();
	void doTurn();
	
	

public:
	Chess(const string& start = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr");
	Chess(const Chess&)=delete;
	Chess& operator=(const Chess&) = delete;
	string getInput();
	void setCodeResponse(int codeResponse);
	void displayBoard() const;
	void bestMove(const string& recommendations);
};