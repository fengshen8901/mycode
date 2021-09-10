#pragma once

class STLAlgorithm
{
public:
	static void StringTest();
	static void VectorTest();

	static void AlgorithmTest();
	static int compa(int a, int b)
	{
		if (a == b) return 'c';
		return a > b ? 'a' : 'b';
	}
};