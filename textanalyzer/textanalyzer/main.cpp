#include <iostream>
#include <string>
#include <ostream>
#include <strstream>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <map>
#include <vector>

void incrementMap(std::string sentence, std::map<int, int> (&sentences))
{
	// Definitions
	std::vector<int> keys;
	int sentenceLength = sentence.size();

	// Get keys
	for (auto const& imap : sentences)
		keys.push_back(imap.first);

	// Loop through keys and compare
	for (int i = 0; i < keys.size(); i++)
	{
		if (sentenceLength == keys[i])
		{
			std::map<int,int>::iterator it = sentences.find(keys[i]);
			if (it != sentences.end())
				it->second += 1;
		}
	}
}

void countSentences(std::stringstream& buffer, std::map<int, int> (&sentences))
{
	std::string text = buffer.str();
	std::string sentence = "";
	int start = 0;
	int end = 0;

	for (int i = 0; i < text.size(); i++)
	{
		if (isupper(text[i]) && sentence.size() == 0)
		{
			start = i;
		}
		else if (text[i] == '.')
		{
			end = i;
			for (int j = start; j <= end; j++)
			{
				sentence.push_back(text[j]);
			}
			incrementMap(sentence, sentences);
			sentence.clear();
		}
		else if (isupper(text[i]) && sentence.size() != 0)
		{
			sentence.clear();
		}
	}

}

int main()
{
	// Variables
	std::map<int, int> sentences;
	
	// Initialize map
	for (int i = 1; i <= 100; i++)
	{
		sentences.insert({ i, 0 });
	}

	printf("Print keys!!!!!\n");
	for (auto const& imap : sentences)
		std::cout << imap.first << std::endl;

	// Program loop
	// while cond
		// Input file name
	std::ifstream t("file2.txt");
	std::stringstream buf1;
	buf1 << t.rdbuf();

	countSentences(buf1, sentences);

	// Print sentence lengths
	for (int i = 0; i < sentences.size(); i++)
	{
		std::map<int, int>::iterator it = sentences.find(sentences[i]);
		if (it != sentences.end())
		std::cout << "Length: " << it->first << " | " << "Count: " << it->second << std::endl;
	}

	//std::cout << buf1.str() << std::endl;
	

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
// sentences[i] = value, NOT KEY!