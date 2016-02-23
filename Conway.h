//Andrew Niklas
//Exercise 7
//Completed 2/24/2016


#ifndef CONWAY_H
#define CONWAY_H

#include <string>

class ConwayTester;

class Conway
{
	friend class ConwayTester;
	
private:
    // add private members here
	bool** board;
	int rows;
	int cols;
	bool** build(int rows, int cols);
	int getNeighbors(int row, int col) const;
	void ruleChk(int numAlive, int row, int col, bool** toFlip);
	void update(bool** toFlip);
public:
    // add public menbers here
	Conway(std::string seed);
	Conway(const Conway& other);
	~Conway();
	
	Conway& operator=(const Conway& right);
	bool alive(int row, int col) const;
	void flip(int row, int col);
	std::string str() const;
	void step();
	void play(int n);
	
};

#endif