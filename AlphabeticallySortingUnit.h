#pragma once
#include "GeneralUnit.h"

class AlphabeticallySortingUnit:
	public GeneralUnit
{
private:
	int* countingArr;

public:
	AlphabeticallySortingUnit(char**, const int);
	~AlphabeticallySortingUnit();
	AlphabeticallySortingUnit(const AlphabeticallySortingUnit&);
	const AlphabeticallySortingUnit& operator=(const AlphabeticallySortingUnit&);
	
private:
	void copy(const AlphabeticallySortingUnit&);

public:
	void sort();

private:
	void sortGroup(const int, const int, const int);
	void countingSort(const int, const int, const int);

private:
	int indexInCntArr(char) const;
	bool areTheSame(const char, const char) const;
	bool assignToCntArr(const int, const int, const int);
	void calculateEnds();
	void shallowCopyToStrings(char**, const int, const int);
};

