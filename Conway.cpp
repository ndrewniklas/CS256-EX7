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
			while(fin >> cell){
				if(cell == 1){
					board[i][j] = true;
				}else if(cell == 0){
					board[i][j] = false;
				}
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

bool Conway::alive(int row, int col){
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
	
}

void Conway::play(int n){
	for(int i = 0; i < n; ++i){
		step();
	}
}


// add main function here or in separate main.cpp