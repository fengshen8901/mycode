#pragma once

class MySort
{
public:
	/*
		ð������: ������������,�������; �ٴα����ҵڶ����
		ʱ��: O(n2)
		�ռ�: O(1)
		int arr[] = { 3,4,2,2,6,1,8,2,7 };
		MySort::BubbleSort(arr, sizeof(arr) / sizeof(arr[0]));
		std::initializer_list<int> b(std::begin(arr), std::end(arr));
		MyPrint(b);
	*/
	static void BubbleSort(int* h, int len);

	/*
	��������, �����һ��,�ŵ����ڵ�λ��(ð�ݵĸĽ�)
	ʱ��: O(n*log2n)
	�ռ�: O(n*log2n)
	int arr[] = { 3,4,2,2,6,1,8,2,7 };
	MySort::QuickSort(arr, 0, sizeof(arr) / sizeof(arr[0])-1);
	std::initializer_list<int> b(std::begin(arr), std::end(arr));
	MyPrint(b);
*/
	static void QuickSort(int* h, int left, int right);

	/*
		ѡ������: **
		��ʼʱ���������ҵ���С����Ԫ�أ��ŵ����е���ʼλ����Ϊ���������У�
		Ȼ���ٴ�ʣ��δ����Ԫ���м���Ѱ����С����Ԫ�أ��ŵ����������е�ĩβ���Դ�����
		ʱ��: O(n2)
		�ռ�: O(1)
		int arr[] = { 3,4,2,2,6,1,8,2,7 };
		MySort::SelectionSort(arr, sizeof(arr) / sizeof(arr[0]));
		std::initializer_list<int> b(std::begin(arr), std::end(arr));
		MyPrint(b);
	*/
	static void SelectionSort(int* h, int len);

	/*
		��������: ֱ�Ӳ�������
		����һ������A[0,n]���������⣬������Ϊ������A[0,n-1]����������Ѿ�����ˡ�
		����A[n]��ֵ����������ɨ����������A[0,n-1]��ֱ����һ��С�ڵ���A[n]��Ԫ�أ���A[n]�������Ԫ�صĺ��档
		Ȼ���ٴ�ʣ��δ����Ԫ���м���Ѱ����С����Ԫ�أ��ŵ����������е�ĩβ���Դ�����
		ʱ��: O(n2)
		�ռ�: O(1)
		int arr[] = { 3,4,2,2,6,1,8,2,7 };
		MySort::InsertSort(arr, sizeof(arr) / sizeof(arr[0]));
		std::initializer_list<int> b(std::begin(arr), std::end(arr));
		MyPrint(b);
	*/
	static void InsertSort(int* h, int len);

	/*
		ϣ������:  �õ��˲�������		
		ʱ��: O(n1.3)
		�ռ�: O(1)
		����len/2
		int arr[] = { 3,4,2,2,6,1,8,2,7 };
		MySort::ShellSort(arr, sizeof(arr) / sizeof(arr[0]));
		std::initializer_list<int> b(std::begin(arr), std::end(arr));
		MyPrint(b);
	*/
	static void ShellSort(int* h, int len);
};

