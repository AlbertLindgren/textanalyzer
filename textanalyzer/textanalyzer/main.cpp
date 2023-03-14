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
		if (isupper(text[i]) && sentence.size() == 0 && start == 0)
		{
			std::cout << "Uppercase: " << text[i] << std::endl;
			start = i;
		}
		else if (text[i] == '.' && end == 0 && 
			(text[i-1] != 'e' && text[i+1] != 'g') && (text[i-1] != 'g' && text[i-2] != '.') && (text[i - 1] != 'i' && text[i + 1] != 'e') && (text[i - 1] != 'e' && text[i - 2] != '.'))
		{
			end = i;
			for (int j = start; j <= end; j++)
			{
				sentence.push_back(text[j]);
			}
			std::cout << "Incremented!" << std::endl;
			incrementMap(sentence, sentences);
			sentence.clear();
			start = 0;
			end = 0;
		}
		/*else if (isupper(text[i]) && sentence.size() != 0)
		{
			sentence.clear();
		}
		*/
	}

}

bool searchWordcount(int wordcount, std::string text)
{
	std::string sentence = "";
	int start = 0;
	int end = 0;

	for (int i = 0; i < text.size(); i++)
	{
		if (isupper(text[i]) && sentence.size() == 0 && start == 0)
		{
			start = i;
		}
		else if (text[i] == '.' &&
			(text[i - 1] != 'e' && text[i + 1] != 'g') && (text[i - 1] != 'g' && text[i - 2] != '.') && 
			(text[i - 1] != 'i' && text[i + 1] != 'e') && (text[i - 1] != 'e' && text[i - 2] != '.'))
		{
			end = i;
			for (int j = start; j <= end; j++)
			{
				sentence.push_back(text[j]);
			}
			start = 0;
			end = 0;

			// if wordcount == words 
			// Count words:
			int words = 0;
			for (int c = 0; c < sentence.size(); c++)
			{
				if (sentence[c] == ' ')
				{
					words += 1;
				}
				else if (c == sentence.size() - 1)
				{
					words += 1;
				}
			}
			if (wordcount == words)
			{
				std::cout << "Matching sentence: \n";
				std::cout << sentence << std::endl;
			}
			else if (i == (text.size() - 1) && wordcount != words)
			{
				std::cout << "No matches\n";
				return false;
			}


			sentence.clear();
		}
		else if (isupper(text[i]) && sentence.size() != 0)
		{
			sentence.clear();
		}
	}
	return true;
}

bool searchFrequency(int frequency, std::string text, std::map<int, int>(&sentences))
{
	std::string sentence = "";
	std::vector<int> sentenceLengths;
	int start = 0;
	int end = 0;

	// Extract sentence length with chosen frequency from map
	for (auto const& imap : sentences)
	{
		if (frequency == imap.second)
		{
			sentenceLengths.push_back(imap.first);
		}
	}

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

			// if wordcount == words 
			// Count words:
			int words = 0;
			for (int c = 0; c < sentence.size(); c++)
			{
				if (sentence[c] == ' ')
				{
					words += 1;
				}
				else if (c == sentence.size() - 1)
				{
					words += 1;
				}
			}
			

			for (int z = 0; z < sentenceLengths.size(); z++)
			{
				if (sentenceLengths[z] == words)
				{
					std::cout << "Matching frequency: \n";
					std::cout << "Sentence length: " << sentenceLengths[z] << std::endl;
					std::cout << sentence << std::endl;
				}
				else if (i == (text.size() - 1) && sentenceLengths[z] != words)
				{
					std::cout << "No matches\n";
					return false;
				}
			}

			sentence.clear();
		}
		else if (isupper(text[i]) && sentence.size() != 0)
		{
			sentence.clear();
		}
	}
	return true;
}

void searchHighestFrequency(std::map<int,int> (&sentences))
{
	int highestFrequency = 0;

	// Extract sentence length with chosen frequency from map
	for (auto const& imap : sentences)
	{
		if (imap.second > highestFrequency)
		{
			highestFrequency = imap.second;
		}
	}

	for (auto const& imap : sentences)
	{
		if (imap.second == highestFrequency)
		{
			std::cout << "Highest frequency: " << imap.first << " words" << std::endl;
		}
	}
}

std::stringstream readFile(std::string filename)
{
	std::stringstream buf;
	std::ifstream t(filename);
	buf << t.rdbuf();
	bool run = true;

	while (buf.str().size() == 0 && run == true)
	{
		std::string input;
		std::cout << "Exception opening / reading file" << std::endl;
		std::cout << "Try again? y/n" << std::endl;
		std::cin >> input;
		if (input == "y")
		{
			buf.clear();
			std::cout << "Input filename: ";
			std::cin >> input;
			std::ifstream t(input);
			buf << t.rdbuf();
		}
		else
		{
			run = false;
		}
	}

	return buf;
}



std::stringstream enterText()
{
	// Input file name
	std::string input;
	std::cout << "Input filename: ";
	std::cin >> input;
	std::cout << "\n";
	std::stringstream buf1 = readFile(input);
	return buf1;
}

int main()
{
	// Variables
	std::map<int, int> sentences;
	bool running = true;
	int totalWords = 0;

	// Initialize map
	for (int i = 1; i <= 100; i++)
	{
		sentences.insert({ i, 0 });
	}

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

		for (auto const& imap : sentences) {
			totalWords += imap.first * imap.second;
			std::cout << "Words: " << imap.first << " | " << "Count: " << imap.second << std::endl;
		}
		std::cout << "Wordtotal (excluding non-sentences): " << totalWords << std::endl;
	}
	
	// Program loop
	// while cond
	while (running)
	{
			
			std::cout << "------------------------------------------------------------\n";
			int choice;
			int input2 = 0;
			std::cout << "Choose action: \n";
			std::cout << "1. Search for sentences matching the chosen wordcount\n";
			std::cout << "2. Search for the chosen frequency\n";
			std::cout << "3. Search for wordcount with highest frequency\n";
			std::cout << "4. Analyze another text\n";
			std::cout << "5. Exit\n";
			std::cin >> choice;
			switch (choice)
			{
				case 1:
					std::cout << "Enter word count: \n";
					std::cin >> input2;
					searchWordcount(input2, buf1.str());
					break;
				case 2:
					std::cout << "Enter frequency: \n";
					std::cin >> input2;
					searchFrequency(input2, buf1.str(), sentences);
					break;				
				case 3:
					searchHighestFrequency(sentences);
					break;
				case 4:
						// Reset map
						sentences.clear();
						for (int i = 1; i <= 100; i++)
						{
							sentences.insert({ i, 0 });
						}
						buf1 = enterText();
						if (buf1.str().size() == 0)
						{
							running = false;
						}
						if (running)
						{
							iterateText(buf1, sentences);
							totalWords = 0;
							for (auto const& imap : sentences) {
								std::cout << "Words: " << imap.first << " | " << "Count: " << imap.second << std::endl;
								totalWords += imap.first * imap.second;
							}
							std::cout << "Wordtotal (excluding non-sentences): " << totalWords << std::endl;
						}
					break;
				case 5:
					running = false;
					break;
				default:
					std::cout << "Wrong input\n";
					break;
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
