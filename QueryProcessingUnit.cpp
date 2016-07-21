#include <iostream>
#include <assert.h>
#include "QueryProcessingUnit.h"

const char *enter = "ENTER", *query = "QUERY";
const int SIZEOFQUERY = 5;

QueryProcessingUnit::QueryProcessingUnit(char ** strings, const int strsCount):
	GeneralUnit(strings, strsCount)
{
	beg = last = 0;
	fin = size - 1;
}

QueryProcessingUnit::~QueryProcessingUnit()
{
}


///
/// Main functions
///
int QueryProcessingUnit::process(char* line)
{
	char* parameters = line + SIZEOFQUERY + 1;
	if (!strncmp(line, query, SIZEOFQUERY))
	{
		return searchFor(parameters);;
	}
	else if (!strncmp(line, enter, SIZEOFQUERY))
	{
		beg = takeInt(parameters);
		fin = takeInt(parameters);
		return -1;
	}
	throw std::invalid_argument("Wrong command!");
}

int QueryProcessingUnit::searchFor(char* str) const
{
	return binarySearch(str, beg, fin, 0);
}

int QueryProcessingUnit::binarySearch(char* searchStr, int start, int end, const int depth) const
{
	assert(end - start >= 0);
	int searchStrSize = strlen(searchStr);
	if (start == end && strncmp(strings[start], searchStr, searchStrSize))
		return 0;
	if (searchStrSize == depth)
		return end - start;

	int middle = (end - start) / 2 + start;
	if (strings[middle][depth] > searchStr[depth])
	{
		return binarySearch(searchStr, start, middle, depth);
	}
	else if (strings[middle][depth] < searchStr[depth])
	{
		return binarySearch(searchStr, middle + 1, end, depth);
	}
	else
	{
		widenSearchArea(middle, start, end, depth);
		return binarySearch(searchStr, start, end + 1, depth + 1);
	}
}

void QueryProcessingUnit::widenSearchArea(int pos, int& start, int& end, const int depth) const
{
	start = end = pos;
	while (start > beg && !strncmp(strings[start - 1], strings[pos], depth + 1))
	{
		--start;
	}
	while (end < fin && !strncmp(strings[end + 1], strings[pos], depth + 1))
	{
		++end;
	}
}

int QueryProcessingUnit::takeInt(char*& str) const
{
	int currInt = atoi(str);
	skipAfterSpace(str);
	return currInt;
}

void QueryProcessingUnit::skipAfterSpace(char*& str) const
{
	while (* str != '\0' && *(str++) != ' ')
	{
	}
}

