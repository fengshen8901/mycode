#include "Sudoku.h"
#include <iostream>

using namespace std;

Sudoku::Sudoku()
{
	isDone = false;
	//memset(&data, 0, sizeof(data));
}

Sudoku::~Sudoku()
{

}

void Sudoku::Run()
{
	//Input();
	cout << "before-------------" << endl;
	Output();
	cout << "---------------------" << endl;
	if (Update(0) != 0)
	{
		cout << "sudoku fail!" << endl;
	}
	Output();
}

void Sudoku::Input()
{
	char tmp;
	for (int i = 0; i < MAX_ROW; ++i)
	{
		for (int j = 0; j < MAX_COL; ++j)
		{
			cin >> tmp;
			data[i][j] = tmp - '0';
		}
	}
}

void Sudoku::Output()
{
	for (int i = 0; i < MAX_ROW; ++i)
	{
		for (int j = 0; j < MAX_COL; ++j)
		{			
			cout << data[i][j] << "  ";
			if (j % 3 == 2)
				cout << '\t';
		}
		cout << endl;
		if (i % 3 == 2)
			cout << endl;
	}
}

bool Sudoku::Check(int n, int val)
{
	int row = n / MAX_ROW;
	int col = n % MAX_COL;

	for (int i = 0; i < MAX_ROW; ++i)
	{
		if (data[i][col] == val)
			return false;
	}

	for (int j = 0; j < MAX_COL; ++j)
	{
		if (data[row][j] == val)
			return false;
	}

	int pointRow = row / 3 * 3;
	int pointCol = col / 3 * 3;

	for (int i = pointRow; i < pointRow + 3; ++i)
	{
		for (int j = pointCol; j < pointCol + 3; ++j)
		{
			if (data[i][j] == val)
				return false;
		}
	}
	return true;
}

int Sudoku::Update(int n)
{
	if (n > 80)  //超过最后一个
	{
		isDone = true;
		return 0;
	}

	int row = n / MAX_ROW;
	int col = n % MAX_COL;
	if (data[row][col] != 0)
	{		
		return Update(n + 1);
	}
	else
	{
		for (int i = 1; i <= 9; ++i)
		{
			if (Check(n, i))
			{
				data[row][col] = i;
				Update(n + 1);
				if (isDone) return 0;
				data[row][col] = 0;
			}
		}
	}
	return 1;
}