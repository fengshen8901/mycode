#pragma once

#define MAX_ROW 9
#define MAX_COL 9

class Sudoku
{
public:
	Sudoku();
	~Sudoku();

	void Run();
private:
	void Input();
	void Output();
	bool Check(int n, int val);
	int Update(int n);

private:
	int data[MAX_ROW][MAX_COL] = {
		{ 0,3,0, 0,0,7, 0,0,4},
		{ 6,0,2, 0,4,1, 0,0,0},
		{ 0,5,0, 0,3,0, 9,6,7},

		{ 0,4,0, 0,0,3, 0,0,6},
		{ 0,8,7, 0,0,0, 3,5,0},
		{ 9,0,0, 7,0,0, 0,2,0},

		{ 7,1,8, 0,2,0, 0,4,0},
		{ 0,0,0, 1,6,0, 8,0,9},
		{ 4,0,0, 5,0,0, 0,3,0},
	};
	bool isDone;
};

