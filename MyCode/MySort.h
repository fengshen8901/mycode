#pragma once

class MySort
{
public:
	/*
		冒泡排序: 遍历两个相邻,大的往后; 再次遍历找第二大的
		时间: O(n2)
		空间: O(1)
		int arr[] = { 3,4,2,2,6,1,8,2,7 };
		MySort::BubbleSort(arr, sizeof(arr) / sizeof(arr[0]));
		std::initializer_list<int> b(std::begin(arr), std::end(arr));
		MyPrint(b);
	*/
	static void BubbleSort(int* h, int len);

	/*
	快速排序, 随机找一个,放到该在的位置(冒泡的改进)
	时间: O(n*log2n)
	空间: O(n*log2n)
	int arr[] = { 3,4,2,2,6,1,8,2,7 };
	MySort::QuickSort(arr, 0, sizeof(arr) / sizeof(arr[0])-1);
	std::initializer_list<int> b(std::begin(arr), std::end(arr));
	MyPrint(b);
*/
	static void QuickSort(int* h, int left, int right);

	/*
		选择排序: **
		初始时在序列中找到最小（大）元素，放到序列的起始位置作为已排序序列；
		然后，再从剩余未排序元素中继续寻找最小（大）元素，放到已排序序列的末尾。以此类推
		时间: O(n2)
		空间: O(1)
		int arr[] = { 3,4,2,2,6,1,8,2,7 };
		MySort::SelectionSort(arr, sizeof(arr) / sizeof(arr[0]));
		std::initializer_list<int> b(std::begin(arr), std::end(arr));
		MyPrint(b);
	*/
	static void SelectionSort(int* h, int len);

	/*
		插入排序: 直接插入排序
		对于一个数组A[0,n]的排序问题，假设认为数组在A[0,n-1]排序的问题已经解决了。
		考虑A[n]的值，从右向左扫描有序数组A[0,n-1]，直到第一个小于等于A[n]的元素，将A[n]插在这个元素的后面。
		然后，再从剩余未排序元素中继续寻找最小（大）元素，放到已排序序列的末尾。以此类推
		时间: O(n2)
		空间: O(1)
		int arr[] = { 3,4,2,2,6,1,8,2,7 };
		MySort::InsertSort(arr, sizeof(arr) / sizeof(arr[0]));
		std::initializer_list<int> b(std::begin(arr), std::end(arr));
		MyPrint(b);
	*/
	static void InsertSort(int* h, int len);

	/*
		希尔排序:  用到了插入排序		
		时间: O(n1.3)
		空间: O(1)
		增量len/2
		int arr[] = { 3,4,2,2,6,1,8,2,7 };
		MySort::ShellSort(arr, sizeof(arr) / sizeof(arr[0]));
		std::initializer_list<int> b(std::begin(arr), std::end(arr));
		MyPrint(b);
	*/
	static void ShellSort(int* h, int len);
};

