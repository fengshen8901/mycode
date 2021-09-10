#pragma once

//快速排序 QuickSort
//冒泡排序 BubbleSort
//插入排序 InsertSort
//希尔排序 ShellSort

//二分查找 BinarySearch

//MyString
// strcamp strcat substring ....

namespace Tool
{

	//递归二分查找
	template<typename T>
	int BinarySearch(T* h, size_t len, T val)
	{
		if (!h) return -1;

		size_t mid = len / 2;
		if (h[mid] == val)
			return mid;
		else if (h[mid] < val)
			return BinarySearch(&h[mid + 1], len - mid, val);
		else
			return BinarySearch(h, len - mid, val);
		return -1;
	}

	//循环二分查找
	template<typename T>
	int BinarySearch1(T* h, int len, T val)
	{
		if (!h) return -1;

		int mid = 0, low = 0, high = len - 1;
		while (low <= high)
		{
			mid = (low + high) / 2;
			if (h[mid] == val)
				return mid;
			else if (h[mid] > val)
				high = mid - 1;
			else
				low = mid + 1;
		}
		return -1;
	}
}
class MyAlgorithm
{
};

