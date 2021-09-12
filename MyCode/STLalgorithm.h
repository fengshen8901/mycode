#pragma once
#include <string>

class Element
{
public:
	Element() {}
	Element(const char* s):str(s){}
	

	std::string str;
};

class STLAlgorithm
{
public:
	static void VectorTest();
	static void MapTest();
	static void StringTest();
	

	static void AlgorithmTest();
	static int compa(int a, int b)
	{
		if (a == b) return 'c';
		return a > b ? 'a' : 'b';
	}
};