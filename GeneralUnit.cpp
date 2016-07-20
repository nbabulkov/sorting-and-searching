#include "GeneralUnit.h"

GeneralUnit::GeneralUnit()
{
	strings = nullptr;
	size = 0;
}

GeneralUnit::GeneralUnit(char** strings, const int strsCount)
{
	setStrings(strings, strsCount);
}

GeneralUnit::~GeneralUnit()
{
}

char ** GeneralUnit::getStrings() const
{
	return strings;
}

int GeneralUnit::getSize() const
{
	return size;
}

void GeneralUnit::setStrings(char** strings, const int strsCount)
{
	this->strings = strings;
	this->size = strsCount;
}

void GeneralUnit::zeroOutArr(int* arr, const int arrSize)
{
	for (int i = 0; i < arrSize; ++i)
	{
		arr[i] = 0;
	}
}