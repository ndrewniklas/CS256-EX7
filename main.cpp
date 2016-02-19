//Andrew Niklas
//Exercise 7
//Completed 2/24/2016


#include <iostream>
#include <string>
#include <sstream>

#include "Conway.h"

using std::string;


class ConwayTester
{
public:
	void printResult(string output, bool pass) const{
		std::cout << (pass ? "PASS\t" : "    FAIL\t")
			  << output << std::endl;
	}

	void testExistence() const{
		printResult("This should always pass.", true);
	}
};


string seedFile;
int iter = 0;

int main(int argc, char* argv[]){
	if(argc < 3){
		std::cout << "Invalid argument!  conway [filename.txt] [whole #]" << std::endl;
	}else{
		seedFile = argv[1];
		std::stringstream ss(argv[2]);
		ss >> iter;
	}
	
	Conway c(seedFile);
	std::cout << c.str();
	
	ConwayTester ct;
	ct.testExistence();
	
	return 0;
}