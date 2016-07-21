#include <iostream>
#include <assert.h>
#include "AlphabeticallySortingUnit.h"

const int SIZEOFALPH = 'z' - 'a' + 2;

AlphabeticallySortingUnit::AlphabeticallySortingUnit(char** strings, const int strsCount):
	GeneralUnit(strings, strsCount)
{
	countingArr = new int[SIZEOFALPH];
}

AlphabeticallySortingUnit::~AlphabeticallySortingUnit()
{
	delete[] countingArr;
}

AlphabeticallySortingUnit::AlphabeticallySortingUnit(const AlphabeticallySortingUnit& a):
	GeneralUnit(a)
{
	copy(a);
}

const AlphabeticallySortingUnit & AlphabeticallySortingUnit::operator=(const AlphabeticallySortingUnit& a)
{
	if (this != &a)
	{
		GeneralUnit::operator=(a);
		delete[] countingArr;
		copy(a);
	}
	return *this;
}

void AlphabeticallySortingUnit::copy(const AlphabeticallySortingUnit& a)
{
	countingArr = new int[SIZEOFALPH];
	for (int i = 0; i < SIZEOFALPH; ++i)
	{
		countingArr[i] = a.countingArr[i];
	}
}

///
/// Main functions:
///
void AlphabeticallySortingUnit::sort()
{
	sortGroup(0, size, 0);
}

//
// Sorts the strings by the n-th character
// and then executes itself on the groups of strings
// with the same n-th character
//
void AlphabeticallySortingUnit::sortGroup(const int start, const  int end, const int depth)
{
	GeneralUnit::zeroOutArr(countingArr, SIZEOFALPH);
	countingSort(start, end, depth);

	bool isRepeating = false;
	int currStart;
	for (int i = start; i < end - 1; ++i)
	{
		if (areTheSame(strings[i][depth], strings[i + 1][depth]) && !isRepeating)
		{
			isRepeating = true;
			currStart = i;
		}
		else if (isRepeating && strings[i][depth] != strings[i + 1][depth])
		{
			isRepeating = false;
			sortGroup(currStart, i + 1, depth + 1);
		}
	}
	if (isRepeating)
	{
		sortGroup(currStart, end, depth + 1);
	}
}

//
// Applies counting sort lexicographically
//
void AlphabeticallySortingUnit::countingSort(const int start, const int end, const int depth)
{
	bool allTheSame = assignToCntArr(start, end, depth);

	if (allTheSame)
		return;

	calculateEnds();

	int currSize = end - start;
	char** tempStr = new char*[currSize];

	for (int i = end - 1; i >= start; --i)
	{
		char letter = strings[i][depth];
		int tempPos = --countingArr[indexInCntArr(letter)];
		tempStr[tempPos] = strings[i];
	}

	shallowCopyToStrings(tempStr, currSize, start);
}

//
// Returns the index in the array where
// to put the string with n-th letter 
//
int AlphabeticallySortingUnit::indexInCntArr(char letter) const
{
	// '\0' == 0
	assert((letter >= 'a' && letter <= 'z') || letter == 0);
	return letter ? letter - 'a' + 1 : 0;
}

bool AlphabeticallySortingUnit::areTheSame(const char c1, const char c2) const
{
	// aren't both at end
	return c1 == c2 && c1 != '\0';
}

//
// Assigns the current characters in the array used by the counting sort
// 
bool AlphabeticallySortingUnit::assignToCntArr(const int start, const int end, const int depth)
{
	bool allTheSame = true;
	for (int i = start; i < end; ++i)
	{
		char letter = strings[i][depth];
		if (i != start && strings[i - 1][depth] != letter)
		{
			allTheSame = false;
		}
		++countingArr[indexInCntArr(letter)];
	}
	return allTheSame;
}

void AlphabeticallySortingUnit::calculateEnds()
{
	for (int i = 1; i < SIZEOFALPH; ++i)
	{
		countingArr[i] += countingArr[i - 1];
	}
}

void AlphabeticallySortingUnit::shallowCopyToStrings(char** tempStr, const int tempSize, const int start)
{
	for (int i = 0; i < tempSize; ++i)
	{
		strings[start + i] = tempStr[i];
	}
}


