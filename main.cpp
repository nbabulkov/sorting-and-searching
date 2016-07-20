// Date: 26.12.2015
// Author: Nikolay Babulkov FN-45088
// Group IV, Informatics, FMI 
// Assignment 3, SDP
// 
// Sorting and Searching practice
// 
// 1) Enter strings which are saved in an array.
// 2) ENTER <a> <b> - enters a search interval from the a-th word to the b-th 
// 3) QUERY <str> - gives how much words with prefix "str" are found in 
//    the interval, set by ENTER
//

#include <iostream>
#include <vector>
#include "AlphabeticallySortingUnit.h"
#include "QueryProcessingUnit.h"

const int BUFFSIZE = 512;


char* skipToSpace(char* str)
{
	if (*str == ' ')
	{
		return str;
	}

	while (*(++str) != ' ' && *(str) != '\0')
	{
	}

	return str;
}

char* getLine(const int size)
{
	char* buff = new char[size];
	std::cin.getline(buff, size);
	return buff;
}

void inputInt(int& num)
{
	std::cin >> num;
	std::cin.ignore();
	if (num < 0)
	{
		inputInt(num);
	}
}

void inputInt(int& num1, int& num2)
{
	char* buff = getLine(BUFFSIZE);

	num1 = atoi(buff);

	char* secondNum = skipToSpace(buff) + 1;
	num2 = atoi(secondNum);

	if (num1 < 0 || num2 < 0)
	{
		inputInt(num1, num2);
	}
	
	delete[] buff;
}

void correctString(char* str)
{
	while (*str != '\0')
	{
		if (*str >= 'A' && *str <= 'Z')
		{
			*str += 'a' - 'A';
		}
		else if (*str < 'a' || *str >= 'z')
		{
			throw std::invalid_argument("Invalid character in the string!");
		}
		str++;
	}
}

char** inputStrs(const int strsCnt)
{
	char** str = new char*[strsCnt];
	char* buff = getLine(BUFFSIZE);

	int i = 0;
	for (char* curr = buff; *curr != '\0'; ++curr)
	{
		if (i == strsCnt)
			break;

		char* wordStart = curr;
		curr = skipToSpace(curr);
		
		int currSize = curr - wordStart;
		str[i] = new char[currSize];
		strncpy(str[i], wordStart, currSize);
		str[i][currSize] = '\0';

		try
		{
			correctString(str[i++]);
		}
		catch (std::invalid_argument& in)
		{
			std::cout << in.what() << std::endl;
			std::cout << "Enter again:" << std::endl;
			return inputStrs(strsCnt);
		}
	}
	delete[] buff;

	return str;
}

void print(char** strings, const int strsCnt)
{
	for (int i = 0; i < strsCnt; ++i)
		printf("%d) %s\n", i ,strings[i]);
}

void printIntVector(const std::vector<int>& qResp)
{
	std::vector<int>::const_iterator it;
	for (it = qResp.cbegin(); it < qResp.cend(); ++it)
	{
		std::cout << *it << std::endl;
	}
}

void randomStrs(char** strings, const int strsCnt)
{
	if (strings == nullptr)
		strings = new char*[strsCnt];

	for (int row = 0; row < strsCnt; ++row)
	{
		int size = rand() % 8 + 1;
		strings[row] = new char[size + 1];
		for (int i = 0; i < size; ++i)
		{
			strings[row][i] = (char)('a' + rand() % ('z' - 'a'));
		}
		strings[row][size] = '\0';
	}
}

void processQueries(QueryProcessingUnit& q, std::vector<int>& qResp, const int queriesCount)
{
	int i = 0;
	while (i < queriesCount)
	{
		char* line = getLine(BUFFSIZE);
		try
		{
			int response = q.process(line);
			if (response >= 0)
			{
				qResp.push_back(response);
				++i;
			}
		}
		catch (std::invalid_argument& in)
		{
			std::cout << in.what() << std::endl;
		}
		delete[] line;
	}
}

int main()
{
	int instructions;
	inputInt(instructions);
	
	std::vector<int> queriesResponses;
	for (int i = 0; i < instructions; ++i)
	{
		int stringsCount, queriesCount;
		inputInt(stringsCount, queriesCount);

		char** strings = inputStrs(stringsCount);
	//	randomStrs(strings, stringsCount);
		
		AlphabeticallySortingUnit s(strings, stringsCount);
		s.sort();
		
		std::cout << std::endl;
		print(strings, stringsCount);
		std::cout << std::endl;

		QueryProcessingUnit q(strings, stringsCount);
		processQueries(q, queriesResponses, queriesCount);
		std::cout << std::endl;
	}
	printIntVector(queriesResponses);
	std::cout << std::endl;
	return 0;
}