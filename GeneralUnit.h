#pragma once
class GeneralUnit
{
protected:
	int size;
	char** strings;

public:
	GeneralUnit();
	GeneralUnit(char**, const int);
	~GeneralUnit();

public:
	char** getStrings() const;
	int getSize() const;

public:
	void setStrings(char**, const int);

protected:
	void zeroOutArr(int*, const int);
};

