#include "MySort.h"
#include <stdlib.h>
#include <time.h>
#include "Tool.h"

using Tool::Swap;
using Tool::MyPrintArr;

void MySort::QuickSort(int *h, int left, int right)
{
	if (!h || left >= right) return;	
	srand((unsigned int)time(nullptr));

	int len = right - left + 1;
	int baseIndex = rand() % len + left;
	int base = h[baseIndex], i = left, j = right;
	//MyPrintArr(h+left, len);
	//MyPrint("QuickSort Start baseIndex: ", baseIndex, ",base:", base, ",i:", i, ",j:", j);
	if (baseIndex != i)
	{
		Swap(h[baseIndex], h[i]);
		//MyPrintArr(h + left, len);
	}
	while (i < j)
	{
		while (h[j] >= base && i < j)
			--j;
		if (i < j)
		{
			h[i] = h[j];			
			//MyPrintArr(h + left, len);
		}
		
		while (h[i] < base && i < j)
			++i;
		if (i < j)
		{
			h[j] = h[i];
			//MyPrintArr(h + left, len);
		}
	}
	h[i] = base;
	//MyPrintArr(h + left, len);

	QuickSort(h, left, i - 1);
	QuickSort(h, j + 1, right);
}

void MySort::BubbleSort(int *h, int len)
{
	if (!h || len <= 1) return;
	//MyPrintArr(h, len);
	for (int i = 0; i < len - 1; ++i)// 次数; n-1次
	{
		bool isSort = true;
		for (int j = 0; j < len-i-1; ++j) // 下标,从前往后找第i+1大的
		{
			if (h[j] > h[j + 1])
			{
				isSort = false;
				Swap(h[j], h[j + 1]);				
				//MyPrintArr(h, len);
			}
		}
		if(isSort) break;
	}
}

void MySort::SelectionSort(int *h, int len)
{
	if (!h || len <= 1) return;
	//MyPrintArr(h, len);
	for (int i = 0; i < len - 1; ++i) //次数
	{
		int minIndex = i;
		for (int j = i+1; j < len; ++j) //下标,在余下的里面找最小数的下标
		{
			if (h[j] < h[minIndex])
				minIndex = j;
		}
		Swap(h[minIndex], h[i]);
		//MyPrintArr(h, len);
	}
}

void MySort::InsertSort(int *h, int len)
{
	if (!h || len <= 1) return;
	MyPrintArr(h, len);
	for (int i = 1; i < len; ++i)
	{
		for (int j = i; j > 0; --j)
		{
			if (h[j] < h[j - 1])
			{
				Swap(h[j], h[j - 1]);
				MyPrintArr(h, len);
			}
			else
				break;
		}
	}
}

void MySort::ShellSort(int *h, int len)
{
	if (!h || len <= 1) return;

	for (int m = len/2; m >=1; m/=2)
	{
		for (int n = 0; n < m; ++n)
		{
			for (int i = n+m; i < len; i += m)
			{
				for (int j = i; i > 0; j -= m)
				{
					if (h[j] < h[j - m])
						Swap(h[j], h[j - m]);
					else
						break;
				}
			}
		}
	}
}
