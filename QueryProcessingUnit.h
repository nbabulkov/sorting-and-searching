#pragma once
#include "GeneralUnit.h"

class QueryProcessingUnit:
	public GeneralUnit
{
private:
	int beg, fin, last;

public:
	QueryProcessingUnit(char**, const int);
	~QueryProcessingUnit();

public:
	int process(char*);

private:
	int searchFor(char*) const;
	int binarySearch(char*, int, int, const int) const;
	void widenSearchArea(int, int&, int&, const int) const;

private:
	int takeInt(char*&) const;
	void skipAfterSpace(char*&) const;
};

