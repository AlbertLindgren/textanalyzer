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

	// Get keys
	for (auto const& imap : sentences)
		keys.push_back(imap.first);

	// Count words:
	int words = 0;
	for (int i = 0; i < sentence.size(); i++)
	{
		if (sentence[i] == ' ')
		{
			words += 1;
		}
		else if (i == sentence.size() - 1)
		{
			words += 1;
		}
	}

	// Loop through keys and compare
	for (int i = 0; i < keys.size(); i++)
	{
		if (words == keys[i])
		{
			std::map<int,int>::iterator it = sentences.find(keys[i]);
			if (it != sentences.end())
				it->second += 1;
		}
	}

	std::cout << "Sentence: " << sentence << std::endl;
	std::cout << "Nbr words: " << words << std::endl;
	
}

void iterateText(std::stringstream& buffer, std::map<int, int> (&sentences))
{
	std::string text = buffer.str();
	std::string sentence = "";
	int start = 0;
	int end = 0;

	for (int i = 0; i < text.size(); i++)
	{
		if (isupper(text[i]) && sentence.size() == 0)
		{
			std::cout << "Uppercase: " << text[i] << std::endl;
			start = i;
		}
		else if (text[i] == '.')
		{
			end = i;
			for (int j = start; j <= end; j++)
			{
				sentence.push_back(text[j]);
			}
			std::cout << "Incremented!" << std::endl;
			incrementMap(sentence, sentences);
			sentence.clear();
		}
		else if (isupper(text[i]) && sentence.size() != 0)
		{
			sentence.clear();
		}
	}

}

void searchWordcount(int wordcount, std::string text)
{
	std::string sentence = "";
	int start = 0;
	int end = 0;

	for (int i = 0; i < text.size(); i++)
	{
		if (isupper(text[i]) && sentence.size() == 0)
		{
			std::cout << "Uppercase: " << text[i] << std::endl;
			start = i;
		}
		else if (text[i] == '.')
		{
			end = i;
			for (int j = start; j <= end; j++)
			{
				sentence.push_back(text[j]);
			}

			sentence.clear();
		}
		else if (isupper(text[i]) && sentence.size() != 0)
		{
			sentence.clear();
		}
	}
}

void searchHighestFrequency(int frequency, std::string text, std::map<int,int> (&sentences))
{
	// Use searchWordcount() to get sentence(s)
}

std::stringstream readFile(std::string filename)
{
	std::stringstream buf;
	std::ifstream t(filename);
	buf << t.rdbuf();
	if (buf.str().size() == 0)
	{
		std::string input;
		std::cout << "Exception opening / reading file" << std::endl;
		std::cout << "Try again? y/n" << std::endl;
		std::cin >> input;
		if (input == "y")
		{
			std::cout << "Input filename: ";
			std::cin >> input;
			readFile(input);
		}
		else
		{
			return buf;
		}
	}


	return buf;
}

int main()
{
	// Variables
	std::map<int, int> sentences;
	bool running = true;
	std::stringstream buf1;

	// Initialize map
	for (int i = 1; i <= 100; i++)
	{
		sentences.insert({ i, 0 });
	}
	// Program loop
	// while cond
	while (running)
	{
		// Input file name
		std::string input;
		std::cout << "Input filename: ";
		std::cin >> input;
		std::cout << "\n";
		std::stringstream buf1 = readFile(input);
		if (buf1.str().size() == 0)
		{
			running = false;
		}
		
		if (running)
		{
			iterateText(buf1, sentences);

			for (auto const& imap : sentences)
				std::cout << "Words: " << imap.first << " | " << "Count: " << imap.second << std::endl;

			std::cout << "------------------------------------------------------------\n";
			int choice;
			std::cout << "Choose action: \n";
			std::cout << "1. Search for sentences matching the chosen wordcount\n";
			std::cout << "2. Search for wordcount with highest frequency\n";
			std::cout << "3. Analyze another text\n";
			std::cout << "4. Exit\n";
			std::cin >> choice;
			switch (choice)
			{
				case 1:

					break;
				case 2:

					break;				
				case 3:
					running = true;
					break;
				case 4:
					running = false;
					break;
			}
		}
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
