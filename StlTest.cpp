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

	//iter = adjacent_find(first, last[, pred]); 搜索序列中两个连续相等的元素, 用==运算符来比较连续的一对元素, 返回的迭代器指向前两个相等元素中的第一个, 没有返回结束迭代器
	string saying{ "Children should be seen and not heard." };
	auto cIter = adjacent_find(begin(saying), end(saying)); 
	if (cIter != std::end(saying))
		cout << "adjacent_find 1 pos: " << distance(std::begin(saying), cIter) << ", " << *cIter << endl;  //"seen" e
	vector<long> numbers{ 64L, 46L, -65L, -128L, 121L, 17L, 35L, 9L, 91L, 5L };
	auto iIter = std::adjacent_find(std::begin(numbers), std::end(numbers), [](long n1, long n2) { return n1 % 2 && n2 % 2; }); //第一对都为奇数的连续整数 
	if (iIter != std::end(numbers))
		cout << "adjacent_find 2 pos: " << distance(std::begin(numbers), iIter) << ", " << *iIter << endl;  //121L, 17L

	//bool binary_search(first, last, val[, pred])二分查找算法，迭代器必须是正向迭代器而且元素必须可以使用 < 运算符来比较, 区间内元素必须有序
	vector<int> vNums = { 5, 7, 11, 16, 33, 45 };
	cout << "binary_search 1 has 11, " << std::binary_search(begin(vNums), end(vNums), 11) << endl;
	cout << "binary_search 2 has 11, " << std::binary_search(begin(vNums), end(vNums), 11, [](int a, int b) { return a == b; }) << endl;	//a是变量，b是11
	//利用二分查找的算法，
	//iter = lower_bound(first, last, val[, pred])返回区间的第一个大于等于x的迭代器(不小于)，
	//iter = upper_bound(first, last, val[, pred])返回区间的第一个大于x的迭代器，
	//pair = equal_range(first, last, val[, pred])则是以pair的形式将两者都返回
	//注意 end判断
	cout << "lower_bound 1, " << *std::lower_bound(vNums.begin(), vNums.end(), 16) << endl;;
	cout << "lower_bound 2, " << *std::lower_bound(vNums.begin(), vNums.end(), 16, [](int a, int b) { return a == b; }) << endl;		//a是变量，b是16
	auto iPair = std::equal_range(vNums.begin(), vNums.end(), 16);	//[)
	cout << "equal_range 1, " << *iPair.first << ", " << *iPair.second << endl;

	//在序列中统计某个值出现的次数
	cout << "count " << saying << ", e, " << std::count(begin(saying), end(saying), 'e') << endl;	//利用==运算符判断
	cout << "count_if " << saying << ", e, " << std::count_if(begin(saying), end(saying), [](char c) { return c == 'e'; }) << endl; //谓词判断

	//判断一个序列是否是另一个序列的子序列
	//多个子序列匹配时，find_end() 函数，返回最后一个子序列；search() 函数，返回第一个子序列
	//(first1, last1, first2, last2[,pred])
	//first1、last1：都为正向迭代器，其组合[first1, last1) 用于指定查找范围（即序列 1）；
	//first2、last2：都为正向迭代器，其组合[first2, last2) 用于指定要查找的序列（即序列 2）；
	//pred：自定义查找规则。该规则实际上是一个包含 2 个参数且返回值类型为 bool 的函数
	//（第一个参数接收[first1, last1) 范围内的元素，第二个参数接收[first2, last2) 范围内的元素）。函数定义的形式可以是普通函数，也可以是函数对象。
	string tmpStr = "en";
	cout << "search 1 " << saying << ", " << tmpStr << ", " << std::search(begin(saying), end(saying), begin(tmpStr), end(tmpStr)) - begin(saying)<< endl;
	cout << "find_end 1 " << saying << ", " << tmpStr << ", " << std::find_end(begin(saying), end(saying), begin(tmpStr), end(tmpStr)) - begin(saying) << endl;
	//search_n 重复元素子序列搜索
	//(first, last, count, val[, pred])
	cout << "search_n 1 " << saying << ", " << std::search_n(begin(saying), end(saying), 2, 'e') - begin(saying) << endl;
	cout << "search_n 2 " << saying << ", " << std::search_n(begin(saying), end(saying), 2, 'e', [](char a, char b) { return toupper(a) == toupper(b); }) - begin(saying) << endl;

	//std::find(first, last, val)
	//std::find_if(first, last, pred)
	//std::find_first_of(first1, last1, first2, last2[, pred])第一段范围内查找与第二段范围中任意元素匹配的元素(任意匹配)

}

void StlTest::SortAndCommon()
{
	//merge, inplace_merge, random_shuffle, nth_element
	//sort, stable_sort
	//partition, stable_partition
	//partial_sort, partial_sort_copy
	//reverse, reverse_copy
	//rotate, rotate_copy


	//merge  合并两个有相同顺序的序列中的元素, 返回合并序列末尾的后一个位置
	//(first1, last1, first2, last2, resultFirst[, pred])
	//目的序列中的元素必须是已经存在的,可以放在一个源序列容器中，但源序列和目的序列不能重叠
	std::vector<int> these{ 2, 15, 4, 11, 6, 7 };
	std::vector<int> those{ 5, 2, 3, 2, 14, 11, 6 }; 
	std::stable_sort(std::begin(these), std::end(these), std::greater<>()); //降序，默认less升序
	std::stable_sort(std::begin(those), std::end(those), std::greater<>()); 
	std::vector<int> result(these.size() + those.size() + 10);
	auto end_iter = std::merge(std::begin(these), std::end(these), std::begin(those), std::end(those), std::begin(result), std::greater<>());
	std::copy(std::begin(result), end_iter, std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	//inplace_merge原地合并，合并同一个序列中两个连续有序的元素序列
	//void (first, second, last[, pred])		同一个序列中,[first, second), [second, last)合并
	std::vector<int> vec{ 1,3,5,7,2,4,6,8 };
	std::inplace_merge(vec.begin(), vec.begin() + 4, vec.end());
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	//void random_shuffle(first, last)	  随机打乱
	std::random_shuffle(vec.begin(), vec.end());
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	//nth_element, void, 从某个序列中找到第 n 小的元素 K，并将 K 移动到序列中第 n 的位置处,并且在处理过后，所有位于 K 之前的元素都比 K 小，所有位于 K 之后的元素都比 K 大
	//(first, nth, last[, pred])
	std::vector<int> vec1{ 0, 3, 8, 1, 7, 2, 9 };
	auto it = vec1.begin() + 5;
	nth_element(vec1.begin(), it, vec1.end());
	std::copy(vec1.begin(), vec1.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	//void sort(first, last[, pred])
	std::vector<int> vec2{ 0, 3, 8, 1, 7, 2, 9 };
	std::sort(vec2.begin(), vec2.end());
	//void stable_sort(first, last[, pred]) 稳定排序，值相同的元素，不会改变它们的相对位置
	std::stable_sort(vec2.begin(), vec2.end());
	std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	//partition(first, last, pred), 将所有满足pred的挪到前面，返回第一个不满足pred元素所在的迭代器
	//stable_partition(first, last, pred)  保持相对位置
	it = std::partition(vec2.begin(), vec2.end(), [](int a) { return a % 2 == 0; });
	cout << "partition 1 pos " << it - vec2.begin() << endl;
	std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;
	
	//void partial_sort(first, second, last[, pred])  部分排序--[first，second) 将会是 [first，last) 中(pred)已续 second-first 个元素
	std::partial_sort(vec2.begin(), vec2.begin() + 4, vec2.end());
	std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;
	//partial_sort_copy(first, last, resFirst, resLast[, pred])  --复制到新容器中，目的位置的元素个数决定了输入元素段中被排序元素的个数(resLast-resFirst),
	//返回目标区间最后一个被复制的元素的下一个位置
	std::random_shuffle(vec2.begin(), vec2.end());
	vector<int> resVec(4); //vec2.size(); / vec2.size + 10 保留足够空间
	auto endIter = std::partial_sort_copy(vec2.begin(), vec2.end(), resVec.begin(), resVec.end());
	std::copy(resVec.begin(), resVec.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;	
	cout << "partial_sort_copy count " << endIter - resVec.begin() << endl;

	//void reverse(first, last)  颠倒重排
	//iter = reverse_copy(first, last, first2) 返回目标区间中最后一个被复制元素的下一位置
	std::random_shuffle(vec2.begin(), vec2.end());
	std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;
	std::reverse(vec2.begin(), vec2.end());
	std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;
	
	//void rotate(first, second, last)  将指定范围内元素移到容器末尾，由second指向的元素成为容器第一个元素(将序列中的元素想象成手镯上的珠子, second转到首位)
	//rotate_copy(first, second, last, resFirst)  返回目标区间中最后一个被复制元素的下一位置
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

	//	iter = copy(first, last, resFirst)   返回目标区间中最后一个被复制元素的下一位置
	// res大小必须 >= （last - first)
	// copy_backward(first, last, resFirst)  复制一个倒序的出来
	vector<int> vec{ 2, 6, 4, 7, 5, 8, 0, 1};
	vector<int> vec1(vec.size());
	auto iter = std::copy(vec.begin(), vec.end(), vec1.begin());
	std::copy(vec1.begin(), vec1.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	//void std::iter_swap(first, last);
	//void std::swap(left, right);
	//iter = std::swap_ranges(first1, last1, first2); 返回第二个序列的最后一个被复制元素的下一位置
	//		第二个序列大小必须 >= （last - first)
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

	//iter = remove(first, last, val)  删除指定范围内所有等于指定元素的元素
	//iter = remove_if(first, last, pred)
	//不是真正删除函数, 只是将元素的值往前挪,返回一个指向新的超尾值的迭代器
	vector<int> vec2{ 2, 6, 4, 7, 6, 5, 8, 0, 1, 6, 6 };
	auto it = std::remove(vec2.begin(), vec2.end(), 6);
	std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;
	cout << *it << endl;
	//remove_copy(first, last, first2, val)
	//remove_copy_if(first, last, first2, pred)
	//忽略[first, last)中相等（或满足条件）的元素，复制到first2, 返回第二个序列的最后一个被复制元素的下一位置
	vector<int> vec3(8);
	vector<int> vec4{ 2, 6, 4, 7, 6, 5, 8, 0, 1, 6, 2, 6 };
	it = std::remove_copy(vec4.begin(), vec4.end(), vec3.begin(), 6);
	std::copy(vec3.begin(), vec3.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	//iter = unique(first, last[, pred])  清除序列中重复(或满足条件)的元素
	//iter = unique_copy(first, last, resFirst[, pred])
	//不是真正删除函数, 只是将元素的值往前挪,返回一个指向新的超尾值的迭代器
	std::sort(vec4.begin(), vec4.end());
	std::copy(vec4.begin(), vec4.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;
	it = std::unique(vec4.begin(), vec4.end());
	std::copy(vec4.begin(), vec4.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;
}

void StlTest::PermutationTest()
{
	//abc全排列, abc，acb，bac，bca，cab，cba
	// bool prev_permutation(first, last[, pred]) 按上一个排序，如果到顶了(abc)任然按(cba)排序，但返回false
	// bool next_permutation(first, last[, pred]) 按下一个排序，如果到底了(cba)任然按(abc)排序，但返回false
	// 可利用先升序或降序排序，再循环排列组合，得到全排序
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
	/*accumulate:               iterator对标识的序列段元素之和，加到一个由val指定的初始值上。重载版本不再做加法，而是传进来的二元操作符被应用到元素上。 #include <numeric>
	partial_sum : 创建一个新序列，其中每个元素值代表指定范围内该位置前所有元素之和。重载版本使用自定义操作代替加法。
	inner_product : 对两个序列做内积(对应元素相乘，再求和)并将内积加到一个输入的初始值上。重载版本使用用户定义的操作。
	adjacent_difference : 创建一个新序列，新序列中每个新值代表当前元素与上一个元素的差。重载版本用指定二元操作计算相邻元素的差。*/
	std::vector<int> vec{ 1, 3, 5, 4 };
	int total = accumulate(vec.begin(), vec.end(), 7);
	cout << total << endl;
	int res = accumulate(vec.begin(), vec.end(), 3, [](int a, int b) { return a+b; });  
	/*	// 循环调用 op函数
		for(auto it = vec.begin();it != vec.end();++it)
		val = binary_op(val, *it);
		return val;
		*/
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;
	cout << "res: " << res << endl;

	std::vector<int> dest(4);	//目标容器必须已分配空间
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
	for_each : 用指定函数依次对指定范围内所有元素进行迭代访问，返回所指定的函数类型。该函数不得修改序列中的元素。
	fill:      将输入值赋给标志范围内的所有元素。
	fill_n : 将输入值赋给first到first + n范围内的所有元素。[ )
	generate : 连续调用输入的函数来填充指定的范围。
	generate_n : 与generate函数类似，填充从指定iterator开始的n个元素。
	transform : 将输入的操作作用与指定范围内的每个元素，并产生一个新的序列。
						重载版本将操作作用在一对元素上，另外一个元素来自输入的另外一个序列。结果输出到指定容器。*/
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
	dest.resize(4);		//目标容器必须已分配空间
	transform(vec1.begin(), vec1.end(), dest.begin(), [](int a) { return a; });	
	std::copy(dest.begin(), dest.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	transform(vec1.begin(), vec1.end(), vec2.begin(), dest.begin(), [](int a, int b) { return a + b; });
	std::copy(dest.begin(), dest.end(), std::ostream_iterator<int>{std::cout, " "});
	cout << endl;

	//转大写
	std::string str = "Hello, World!";
	std::string strUpper(str.length(), ' ');
	std::transform(str.begin(), str.end(), strUpper.begin(), toupper);
	cout << strUpper << endl;
}

void StlTest::EqualTest()
{
	/*equal:                                  如果两个序列在标志范围内元素都相等，返回true。重载版本使用输入的操作符代替默认的等于操作符。
	includes :	  （两个范围内元素需已序）第二个范围内的所有元素都能在第一个指定范围内找到，成功返回 true。
	lexicographical_compare : 比较两个序列。重载版本使用用户自定义比较操作。
	max : 返回两个元素中较大一个。重载版本使用自定义比较操作。
	max_element : 返回一个ForwardIterator，指出序列中最大的元素。重载版本使用自定义比较操作。
	min : 返回两个元素中较小一个。重载版本使用自定义比较操作。
	min_element : 返回一个ForwardIterator，指出序列中最小的元素。重载版本使用自定义比较操作。
	mismatch : 并行比较两个序列，指出第一个不匹配的位置，返回一对iterator，标志第一个不匹配元素位置。                                                 如果都匹配，返回每个容器的last。重载版本使用自定义的比较操作。*/

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
	/*set_union:         构造一个有序序列，包含两个序列中所有的不重复元素。重载版本使用自定义的比较操作。
	set_intersection : 构造一个有序序列，其中元素在两个序列中都存在。重载版本使用自定义的比较操作。
	set_difference :	构造一个有序序列，该序列仅保留第一个序列中存在的而第二个中不存在的元素。重载版本使用自定义的比较操作。
	set_symmetric_difference : 构造一个有序序列，该序列取两个序列的对称差集(并集 - 交集)。*/
}

void StlTest::HeapTest()
{
	/*make_heap: 把指定范围内的元素生成一个堆。重载版本使用自定义比较操作。
	pop_heap : 并不真正把最大元素从堆中弹出，而是重新排序堆。它把first和last - 1交换，然后重新生成一个堆。可使用容器的                       back来访问被"弹出"的元素或者使用pop_back进行真正的删除。重载版本使用自定义的比较操作。
	push_heap : 假设first到last - 1是一个有效堆，要被加入到堆的元素存放在位置last - 1，重新生成堆。在指向该函数前，必须先把元素插入容器后。重载版本使用指定的比较操作。
	sort_heap : 对指定范围内的序列重新排序，它假设该序列是个有序堆。重载版本使用自定义比较操作。*/

}