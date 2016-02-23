 //Andrew Niklas
//Exercise 7
//Completed 2/24/2016


#include "Conway.h"

#include <iostream>
#include <fstream>
#include <sstream>

// add functions here
Conway::Conway(std::string seed){
	std::ifstream fin(seed);
	int cell;
	fin >> rows;
	fin >> cols;
	board = build(rows, cols);
	for(int i = 0; i < rows; ++i){
		for(int j = 0; j < cols; ++j){
			fin >> cell;
			if(cell == 1){
				board[i][j] = true;
			}else if(cell == 0){
				board[i][j] = false;
			}
		}
	}
}

Conway::Conway(const Conway& other)
	:board(build(other.rows, other.cols)), rows(other.rows), cols(other.cols)
{
	for(int i = 0; i < rows; ++i){
		for(int j = 0; j < cols; ++j){
			board[i][j] = other.board[i][j];
		}
	}
}

bool** Conway::build(int rows, int cols){
	bool** result = new bool*[rows];
	for(int i = 0; i < rows; ++i){
		result[i] = new bool[cols];
	}
	return result;
}

Conway::~Conway(){
	if(board != nullptr){
		for(int i = 0; i < rows; ++i){
			delete [] board[i];
		}
		delete [] board;
		board = nullptr;
	}
	rows = 0;
	cols = 0;
}

Conway& Conway::operator=(const Conway& right){
	if(this == &right){
		return *this;
	}
	for(int i = 0; i < rows; ++i){
			delete [] board[i];
	}
	delete [] board;
	board = build(right.rows, right.cols);
	for(int i = 0; i < rows; ++i){
		for(int j = 0; j < cols; ++j){
			board[i][j] = right.board[i][j];
		}
	}
	return *this;
}

bool Conway::alive(int row, int col) const{
	return board[row][col];
}

void Conway::flip(int row, int col){
	board[row][col] = !board[row][col];
}

std::string Conway::str() const{
	std::stringstream s;
	for(int i = 0; i < rows; ++i){
		for(int j = 0; j < cols; ++j){
			if(board[i][j]){
				s << " X ";
			}else{
				s << " . ";
			}
		}
		s << "\n";
	}
	return s.str();
}

void Conway::step(){
	int numAlive = 0;
	std::cout << "before:\n" << str();
	for(int i = 0; i < rows; ++i){
		for(int j = 0; j < cols; ++j){
			std::cout << "\n";
			std::cout << "@" << i << ", " << j << ": ";
			numAlive = getNeighbors(i, j);
			ruleChk(numAlive, i, j);
			std::cout << numAlive << std::endl;
		}
	}
	std::cout << str() << "\n\n" << std::endl;
}

int Conway::getNeighbors(int row, int col) const{
	int numAlive = 0;
	int sRow = row - 1;
	int eRow = row + 2;
	int sCol = col - 1;
	int eCol = col + 2;
	
	if(row == 0){
		//at top
		std::cout << "at top" << std::endl;
		sRow = row;
		eRow = row + 2;
	}else if(row == rows){
		//at bottom
		std::cout << "at bottom" << std::endl;
		sRow = row - 1;
		eRow = row;
	}
	
	if(col == 0){
		//at left
		std::cout << "at left" << std::endl;
		sCol = col;
		eCol = col + 2;
	}else if(col == cols){
		//at right
		std::cout << "at right" << std::endl;
		sCol = col - 1;
		eCol = col;
	}
	
	if(row == 0 && col == 0){
		//top left corner
		std::cout << "top left corner" << std::endl;
		sRow = row;
		eRow = row + 2;
		sCol = col;
		eCol = col + 2;
	}else if(row == 0 && col == cols){
		//top right corner
		std::cout << "top right corner" << std::endl;
		sRow = row;
		eRow = row + 2;
		sCol = col - 1;
		eCol = col;
	}else if(row == rows && col == 0){
		//botom left corner
		std::cout << "botom left corner" << std::endl;
		sRow = row - 1;
		eRow = row;
		sCol = col;
		eCol = col + 2;
	}else if(row == rows && col == cols){
		//bottom right corner
		std::cout << "bottom right corner" << std::endl;
		sRow = row - 1;
		eRow = row;
		sCol = col - 1;
		eCol = col;
	}
	
	for(int i = sRow; i < eRow && i < rows; ++i){
		for(int j = sCol; j < eCol && j < cols; ++j){
			// std::cout << "\t" << i << ", " << j << std::endl;
			if(alive(i, j)){
				++numAlive;
			}
		}
	}
	return numAlive;
}

void Conway::ruleChk(int numAlive, int row, int col){
	if(alive(row, col)){
		if(numAlive < 2){
			//rule 1
			flip(row, col);
		}else if(numAlive == 2 || numAlive == 3){
			//rule 2
			//stays alive
		}else if(numAlive > 3){
			//rule 3
			flip(row, col);
		}
	}else{
		//rule 4
		if(numAlive == 3){
			flip(row, col);
		}
	}
}

void Conway::play(int n){
	for(int i = 0; i < n; ++i){
		step();
	}
}


// add main function here or in separate main.cpp