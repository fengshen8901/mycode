#pragma once

//�������� QuickSort
//ð������ BubbleSort
//�������� InsertSort
//ϣ������ ShellSort

//���ֲ��� BinarySearch

//MyString
// strcamp strcat substring ....

namespace Tool
{

	//�ݹ���ֲ���
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

	//ѭ�����ֲ���
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

