#include <iostream>
#include <string>
#include <ostream>
#include <strstream>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <map>

int countSentenceLength(std::string sentence, std::map<int, int> sentences[])
{
	
}

int main()
{
	// Variables
	std::map<int, int> sentences;
	// Program loop
	// while cond
		// Input file name
	std::ifstream t("file2.txt");
	std::stringstream buffer;
	buffer << t.rdbuf();

	std::cout << buffer.str() << std::endl;
	
	return 0;
}


// Notes
/*
//c++0x too
std::map<int,int> mapints;
std::vector<int> vints;
for(auto const& imap: mapints)
	vints.push_back(imap.first);
*/