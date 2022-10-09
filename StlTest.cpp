#include "StlTest.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <numeric>

using namespace std;

void StlTest::FindTest()
{
	//adjacent_find, binary_search, count, count_if, equal_range, find, find_end, find_first_of, find_if, lower_bound, upper_bound, search, search_n

	//iter = adjacent_find(first, last[, pred]); ��������������������ȵ�Ԫ��, ��==��������Ƚ�������һ��Ԫ��, ���صĵ�����ָ��ǰ�������Ԫ���еĵ�һ��, û�з��ؽ���������
	string saying{ "Children should be seen and not heard." };
	auto cIter = adjacent_find(begin(saying), end(saying)); 
	if (cIter != std::end(saying))
		cout << "adjacent_find 1 pos: " << distance(std::begin(saying), cIter) << ", " << *cIter << endl;  //"seen" e
	vector<long> numbers{ 64L, 46L, -65L, -128L, 121L, 17L, 35L, 9L, 91L, 5L };
	auto iIter = std::adjacent_find(std::begin(numbers), std::end(numbers), [](long n1, long n2) { return n1 % 2 && n2 % 2; }); //��һ�Զ�Ϊ�������������� 
	if (iIter != std::end(numbers))
		cout << "adjacent_find 2 pos: " << distance(std::begin(numbers), iIter) << ", " << *iIter << endl;  //121L, 17L

	//bool binary_search(first, last, val[, pred])���ֲ����㷨���������������������������Ԫ�ر������ʹ�� < ��������Ƚ�, ������Ԫ�ر�������
	vector<int> vNums = { 5, 7, 11, 16, 33, 45 };
	cout << "binary_search 1 has 11, " << std::binary_search(begin(vNums), end(vNums), 11) << endl;
	cout << "binary_search 2 has 11, " << std::binary_search(begin(vNums), end(vNums), 11, [](int a, int b) { return a == b; }) << endl;	//a�Ǳ�����b��11
	//���ö��ֲ��ҵ��㷨��
	//iter = lower_bound(first, last, val[, pred])��������ĵ�һ�����ڵ���x�ĵ�����(��С��)��
	//iter = upper_bound(first, last, val[, pred])��������ĵ�һ������x�ĵ�������
	//pair = equal_range(first, last, val[, pred])������pair����ʽ�����߶�����
	//ע�� end�ж�
	cout << "lower_bound 1, " << *std::lower_bound(vNums.begin(), vNums.end(), 16) << endl;;
	cout << "lower_bound 2, " << *std::lower_bound(vNums.begin(), vNums.end(), 16, [](int a, int b) { return a == b; }) << endl;		//a�Ǳ�����b��16
	auto iPair = std::equal_range(vNums.begin(), vNums.end(), 16);	//[)
	cout << "equal_range 1, " << *iPair.first << ", " << *iPair.second << endl;

	//��������ͳ��ĳ��ֵ���ֵĴ���
	cout << "count " << saying << ", e, " << std::count(begin(saying), end(saying), 'e') << endl;	//����==������ж�
	cout << "count_if " << saying << ", e, " << std::count_if(begin(saying), end(saying), [](char c) { return c == 'e'; }) << endl; //ν���ж�

	//�ж�һ�������Ƿ�����һ�����е�������
	//���������ƥ��ʱ��find_end() �������������һ�������У�search() ���������ص�һ��������
	//(first1, last1, first2, last2[,pred])
	//first1��last1����Ϊ����������������[first1, last1) ����ָ�����ҷ�Χ�������� 1����
	//first2��last2����Ϊ����������������[first2, last2) ����ָ��Ҫ���ҵ����У������� 2����
	//pred���Զ�����ҹ��򡣸ù���ʵ������һ������ 2 �������ҷ���ֵ����Ϊ bool �ĺ���
	//����һ����������[first1, last1) ��Χ�ڵ�Ԫ�أ��ڶ�����������[first2, last2) ��Χ�ڵ�Ԫ�أ��������������ʽ��������ͨ������Ҳ�����Ǻ�������
	string tmpStr = "en";
	cout << "search 1 " << saying << ", " << tmpStr << ", " << std::search(begin(saying), end(saying), begin(tmpStr), end(tmpStr)) - begin(saying)<< endl;
	cout << "find_end 1 " << saying << ", " << tmpStr << ", " << std::find_end(begin(saying), end(saying), begin(tmpStr), end(tmpStr)) - begin(saying) << endl;
	//search_n �ظ�Ԫ������������
	//(first, last, count, val[, pred])
	cout << "search_n 1 " << saying << ", " << std::search_n(begin(saying), end(saying), 2, 'e') - begin(saying) << endl;
	cout << "search_n 2 " << saying << ", " << std::search_n(begin(saying), end(saying), 2, 'e', [](char a, char b) { return toupper(a) == toupper(b); }) - begin(saying) << endl;

	//std::find(first, last, val)
	//std::find_if(first, last, pred)
	//std::find_first_of(first1, last1, first2, last2[, pred])��һ�η�Χ�ڲ�����ڶ��η�Χ������Ԫ��ƥ���Ԫ��(����ƥ��)

}

void StlTest::SortAndCommon()
{
	//merge, inplace_merge, random_shuffle, nth_element
	//sort, stable_sort
	//partition, stable_partition
	//partial_sort, partial_sort_copy
	//reverse, reverse_copy
	//rotate, rotate_copy


	//merge  �ϲ���������ͬ˳��������е�Ԫ��, ���غϲ�����ĩβ�ĺ�һ��λ��
	//(first1, last1, first2, last2, resultFirst[, pred])
	//Ŀ�������е�Ԫ�ر������Ѿ����ڵ�,���Է���һ��Դ���������У���Դ���к�Ŀ�����в����ص�
	std::vector<int> these{ 2, 15, 4, 11, 6, 7 };
	std::vector<int> those{ 5, 2, 3, 2, 14, 11, 6 }; 
	std::stable_sort(std::begin(these), std::end(these), std::greater<>()); //����Ĭ��less����
	std::stable_sort(std::begin(those), std::end(those), std::greater<>()); 
	std::vector<int> result(these.size() + those.size() + 10);
	auto end_iter = std::merge(std::begin(these), std::end(these), std::begin(those), std::end(those), std::begin(result), std::greater<>());
	std::copy(std::begin(result), end_iter, std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	//inplace_mergeԭ�غϲ����ϲ�ͬһ���������������������Ԫ������
	//void (first, second, last[, pred])		ͬһ��������,[first, second), [second, last)�ϲ�
	std::vector<int> vec{ 1,3,5,7,2,4,6,8 };
	std::inplace_merge(vec.begin(), vec.begin() + 4, vec.end());
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	//void random_shuffle(first, last)	  �������
	std::random_shuffle(vec.begin(), vec.end());
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	//nth_element, void, ��ĳ���������ҵ��� n С��Ԫ�� K������ K �ƶ��������е� n ��λ�ô�,�����ڴ����������λ�� K ֮ǰ��Ԫ�ض��� K С������λ�� K ֮���Ԫ�ض��� K ��
	//(first, nth, last[, pred])
	std::vector<int> vec1{ 0, 3, 8, 1, 7, 2, 9 };
	auto it = vec1.begin() + 5;
	nth_element(vec1.begin(), it, vec1.end());
	std::copy(vec1.begin(), vec1.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	//void sort(first, last[, pred])
	std::vector<int> vec2{ 0, 3, 8, 1, 7, 2, 9 };
	std::sort(vec2.begin(), vec2.end());
	//void stable_sort(first, last[, pred]) �ȶ�����ֵ��ͬ��Ԫ�أ�����ı����ǵ����λ��
	std::stable_sort(vec2.begin(), vec2.end());
	std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	//partition(first, last, pred), ����������pred��Ų��ǰ�棬���ص�һ��������predԪ�����ڵĵ�����
	//stable_partition(first, last, pred)  �������λ��
	it = std::partition(vec2.begin(), vec2.end(), [](int a) { return a % 2 == 0; });
	cout << "partition 1 pos " << it - vec2.begin() << endl;
	std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;
	
	//void partial_sort(first, second, last[, pred])  ��������--[first��second) ������ [first��last) ��(pred)���� second-first ��Ԫ��
	std::partial_sort(vec2.begin(), vec2.begin() + 4, vec2.end());
	std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;
	//partial_sort_copy(first, last, resFirst, resLast[, pred])  --���Ƶ��������У�Ŀ��λ�õ�Ԫ�ظ�������������Ԫ�ض��б�����Ԫ�صĸ���(resLast-resFirst),
	//����Ŀ���������һ�������Ƶ�Ԫ�ص���һ��λ��
	std::random_shuffle(vec2.begin(), vec2.end());
	vector<int> resVec(4); //vec2.size(); / vec2.size + 10 �����㹻�ռ�
	auto endIter = std::partial_sort_copy(vec2.begin(), vec2.end(), resVec.begin(), resVec.end());
	std::copy(resVec.begin(), resVec.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;	
	cout << "partial_sort_copy count " << endIter - resVec.begin() << endl;

	//void reverse(first, last)  �ߵ�����
	//iter = reverse_copy(first, last, first2) ����Ŀ�����������һ��������Ԫ�ص���һλ��
	std::random_shuffle(vec2.begin(), vec2.end());
	std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;
	std::reverse(vec2.begin(), vec2.end());
	std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;
	
	//void rotate(first, second, last)  ��ָ����Χ��Ԫ���Ƶ�����ĩβ����secondָ���Ԫ�س�Ϊ������һ��Ԫ��(�������е�Ԫ������������ϵ�����, secondת����λ)
	//rotate_copy(first, second, last, resFirst)  ����Ŀ�����������һ��������Ԫ�ص���һλ��
	std::sort(vec2.begin(), vec2.end());
	std::rotate(vec2.begin(), vec2.begin() + 3, vec2.end());
	std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;
}

void StlTest::RemoveAndReplace()
{
	// copy, copy_backward
	// swap, iter_swap, swap_ranges
	// replace, replace_if, replace_copy, replace_copy_if
	// remove, remove_if, remove_copy, remove_copy_if
	// unique, unique_copy

	//	iter = copy(first, last, resFirst)   ����Ŀ�����������һ��������Ԫ�ص���һλ��
	// res��С���� >= ��last - first)
	// copy_backward(first, last, resFirst)  ����һ������ĳ���
	vector<int> vec{ 2, 6, 4, 7, 5, 8, 0, 1};
	vector<int> vec1(vec.size());
	auto iter = std::copy(vec.begin(), vec.end(), vec1.begin());
	std::copy(vec1.begin(), vec1.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	//void std::iter_swap(first, last);
	//void std::swap(left, right);
	//iter = std::swap_ranges(first1, last1, first2); ���صڶ������е����һ��������Ԫ�ص���һλ��
	//		�ڶ������д�С���� >= ��last - first)
	std::random_shuffle(vec1.begin(), vec1.end());
	vec1.resize(4);
	std::swap_ranges(vec1.begin(), vec1.end(), vec.begin());
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;
	std::copy(vec1.begin(), vec1.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	//void replace(first, last, oldVal, newVal)
	//void replace_if(first, last, pred, newVal)
	//void replace_copy(first, last, resFirst, oldVal, newVal)
	//void replace_copy_if(first, last, resFirst, pred, newVal)
	std::replace(vec1.begin(), vec1.end(), 0, 9);

	//iter = remove(first, last, val)  ɾ��ָ����Χ�����е���ָ��Ԫ�ص�Ԫ��
	//iter = remove_if(first, last, pred)
	//��������ɾ������, ֻ�ǽ�Ԫ�ص�ֵ��ǰŲ,����һ��ָ���µĳ�βֵ�ĵ�����
	vector<int> vec2{ 2, 6, 4, 7, 6, 5, 8, 0, 1, 6, 6 };
	auto it = std::remove(vec2.begin(), vec2.end(), 6);
	std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;
	cout << *it << endl;
	//remove_copy(first, last, first2, val)
	//remove_copy_if(first, last, first2, pred)
	//����[first, last)����ȣ���������������Ԫ�أ����Ƶ�first2, ���صڶ������е����һ��������Ԫ�ص���һλ��
	vector<int> vec3(8);
	vector<int> vec4{ 2, 6, 4, 7, 6, 5, 8, 0, 1, 6, 2, 6 };
	it = std::remove_copy(vec4.begin(), vec4.end(), vec3.begin(), 6);
	std::copy(vec3.begin(), vec3.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	//iter = unique(first, last[, pred])  ����������ظ�(����������)��Ԫ��
	//iter = unique_copy(first, last, resFirst[, pred])
	//��������ɾ������, ֻ�ǽ�Ԫ�ص�ֵ��ǰŲ,����һ��ָ���µĳ�βֵ�ĵ�����
	std::sort(vec4.begin(), vec4.end());
	std::copy(vec4.begin(), vec4.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;
	it = std::unique(vec4.begin(), vec4.end());
	std::copy(vec4.begin(), vec4.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;
}

void StlTest::PermutationTest()
{
	//abcȫ����, abc��acb��bac��bca��cab��cba
	// bool prev_permutation(first, last[, pred]) ����һ���������������(abc)��Ȼ��(cba)���򣬵�����false
	// bool next_permutation(first, last[, pred]) ����һ���������������(cba)��Ȼ��(abc)���򣬵�����false
	// ���������������������ѭ��������ϣ��õ�ȫ����
	vector<int> vec{ 2,3,1 };
	do
	{
		std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
		cout << endl;
	} while (std::prev_permutation(vec.begin(), vec.end()));

	do
	{
		std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
		cout << endl;
	} while (std::next_permutation(vec.begin(), vec.end()));
	
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;
}

void StlTest::MathTest()
{
	/*accumulate:               iterator�Ա�ʶ�����ж�Ԫ��֮�ͣ��ӵ�һ����valָ���ĳ�ʼֵ�ϡ����ذ汾�������ӷ������Ǵ������Ķ�Ԫ��������Ӧ�õ�Ԫ���ϡ� #include <numeric>
	partial_sum : ����һ�������У�����ÿ��Ԫ��ֵ����ָ����Χ�ڸ�λ��ǰ����Ԫ��֮�͡����ذ汾ʹ���Զ����������ӷ���
	inner_product : �������������ڻ�(��ӦԪ����ˣ������)�����ڻ��ӵ�һ������ĳ�ʼֵ�ϡ����ذ汾ʹ���û�����Ĳ�����
	adjacent_difference : ����һ�������У���������ÿ����ֵ����ǰԪ������һ��Ԫ�صĲ���ذ汾��ָ����Ԫ������������Ԫ�صĲ*/
	std::vector<int> vec{ 1, 3, 5, 4 };
	int total = accumulate(vec.begin(), vec.end(), 7);
	cout << total << endl;
	int res = accumulate(vec.begin(), vec.end(), 3, [](int a, int b) { return a+b; });  
	/*	// ѭ������ op����
		for(auto it = vec.begin();it != vec.end();++it)
		val = binary_op(val, *it);
		return val;
		*/
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;
	cout << "res: " << res << endl;

	std::vector<int> dest(4);	//Ŀ�����������ѷ���ռ�
	partial_sum(vec.begin(), vec.end(), dest.begin());
	std::copy(dest.begin(), dest.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	partial_sum(vec.begin(), vec.end(), dest.begin(), [](int pre, int val) { return pre + val; });
	std::copy(dest.begin(), dest.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	std::vector<int> vec1{ 1, 2, 3, 4 };
	std::vector<int> vec2{ 4, 3, 2, 1 };
	res = inner_product(vec1.begin(), vec1.end(), vec2.begin(), 10);
	cout << "res: " << res << endl;

	res = inner_product(vec1.begin(), vec1.end(), vec2.begin(), 10, [](int a, int b) { return a + b; }, [](int a, int b) {return a * b; });
	cout << "res: " << res << endl;
}

void StlTest::TransformTest()
{
	/*
	for_each : ��ָ���������ζ�ָ����Χ������Ԫ�ؽ��е������ʣ�������ָ���ĺ������͡��ú��������޸������е�Ԫ�ء�
	fill:      ������ֵ������־��Χ�ڵ�����Ԫ�ء�
	fill_n : ������ֵ����first��first + n��Χ�ڵ�����Ԫ�ء�[ )
	generate : ������������ĺ��������ָ���ķ�Χ��
	generate_n : ��generate�������ƣ�����ָ��iterator��ʼ��n��Ԫ�ء�
	transform : ������Ĳ���������ָ����Χ�ڵ�ÿ��Ԫ�أ�������һ���µ����С�
						���ذ汾������������һ��Ԫ���ϣ�����һ��Ԫ���������������һ�����С���������ָ��������*/
	std::vector<int> vec{ 1, 3, 5, 4 };
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	auto func = for_each(vec.begin(), vec.end(), [](int a) { cout << a << ","; });
	func(999);
	cout << endl;

	std::fill(vec.begin(), vec.end(), 11);
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	std::fill_n(vec.begin(), 4, 22);
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;	

	int count = 0;
	generate(vec.begin(), vec.end(), [&count]() { return count++; });
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	count = 100;
	generate_n(vec.begin(), 4, [&count]() { return count++; });
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	std::vector<int> vec1{ 1, 2, 3, 4 };
	std::vector<int> vec2{ 11, 22, 33, 44 };
	std::vector<int> dest;
	dest.resize(4);		//Ŀ�����������ѷ���ռ�
	transform(vec1.begin(), vec1.end(), dest.begin(), [](int a) { return a; });	
	std::copy(dest.begin(), dest.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	transform(vec1.begin(), vec1.end(), vec2.begin(), dest.begin(), [](int a, int b) { return a + b; });
	std::copy(dest.begin(), dest.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	//ת��д
	std::string str = "Hello, World!";
	std::string strUpper(str.length(), ' ');
	std::transform(str.begin(), str.end(), strUpper.begin(), toupper);
	cout << strUpper << endl;
}

void StlTest::EqualTest()
{
	/*equal:                                  ������������ڱ�־��Χ��Ԫ�ض���ȣ�����true�����ذ汾ʹ������Ĳ���������Ĭ�ϵĵ��ڲ�������
	includes :	  ��������Χ��Ԫ�������򣩵ڶ�����Χ�ڵ�����Ԫ�ض����ڵ�һ��ָ����Χ���ҵ����ɹ����� true��
	lexicographical_compare : �Ƚ��������С����ذ汾ʹ���û��Զ���Ƚϲ�����
	max : ��������Ԫ���нϴ�һ�������ذ汾ʹ���Զ���Ƚϲ�����
	max_element : ����һ��ForwardIterator��ָ������������Ԫ�ء����ذ汾ʹ���Զ���Ƚϲ�����
	min : ��������Ԫ���н�Сһ�������ذ汾ʹ���Զ���Ƚϲ�����
	min_element : ����һ��ForwardIterator��ָ����������С��Ԫ�ء����ذ汾ʹ���Զ���Ƚϲ�����
	mismatch : ���бȽ��������У�ָ����һ����ƥ���λ�ã�����һ��iterator����־��һ����ƥ��Ԫ��λ�á�                                                 �����ƥ�䣬����ÿ��������last�����ذ汾ʹ���Զ���ıȽϲ�����*/

	std::vector<int> vec1{ 1, 2, 3, 4 };
	std::vector<int> vec2{ 11, 22, 33, 44 };
	bool isSame = equal(vec1.begin(), vec1.end(), vec2.begin());
	cout << isSame << endl;
	isSame = equal(vec1.begin(), vec1.end(), vec2.begin(), [](int a, int b) { return a % 10 == b % 10; });
	cout << isSame << endl;

	std::vector<int> vec3{ 1, 2, 3 ,11, 22, 33, 44,   };
	std::vector<int> vec4{ 1,3,22,44 };
	cout << includes(vec3.begin(), vec3.end(), vec4.begin(), vec4.end()) << endl;;
}

void StlTest::SetTest()
{
	/*set_union:         ����һ���������У������������������еĲ��ظ�Ԫ�ء����ذ汾ʹ���Զ���ıȽϲ�����
	set_intersection : ����һ���������У�����Ԫ�������������ж����ڡ����ذ汾ʹ���Զ���ıȽϲ�����
	set_difference :	����һ���������У������н�������һ�������д��ڵĶ��ڶ����в����ڵ�Ԫ�ء����ذ汾ʹ���Զ���ıȽϲ�����
	set_symmetric_difference : ����һ���������У�������ȡ�������еĶԳƲ(���� - ����)��*/
}

void StlTest::HeapTest()
{
	/*make_heap: ��ָ����Χ�ڵ�Ԫ������һ���ѡ����ذ汾ʹ���Զ���Ƚϲ�����
	pop_heap : �������������Ԫ�شӶ��е�����������������ѡ�����first��last - 1������Ȼ����������һ���ѡ���ʹ��������                       back�����ʱ�"����"��Ԫ�ػ���ʹ��pop_back����������ɾ�������ذ汾ʹ���Զ���ıȽϲ�����
	push_heap : ����first��last - 1��һ����Ч�ѣ�Ҫ�����뵽�ѵ�Ԫ�ش����λ��last - 1���������ɶѡ���ָ��ú���ǰ�������Ȱ�Ԫ�ز������������ذ汾ʹ��ָ���ıȽϲ�����
	sort_heap : ��ָ����Χ�ڵ�������������������������Ǹ�����ѡ����ذ汾ʹ���Զ���Ƚϲ�����*/

}