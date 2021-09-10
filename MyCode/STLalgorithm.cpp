#include <iostream>
#include <algorithm>

#include <string>
#include <vector>

#include "STLalgorithm.h"
#include "Tool.h"

using namespace std;
using namespace Tool;

void STLAlgorithm::StringTest()
{
	//构造
		//string s(char*, begin, len)：将字符串str中从下标begin开始、长度为len的部分作为字符串初值    string str("12345", 0, 3)  // "123"
		//string s(char*, len)：以C_string类型cstr的前len个字符串作为字符串s的初值								  string str("12345", 3)		// "123"
		//string s(num, char)：生成num个c字符的字符串																			  string str(3, 'a')				// "aaa"
		//string s(string, begin)：将字符串str中从下标str_index开始到字符串结束的位置作为字符串初值   string str1(str, 1)			// "aa"
	//大小和容量
		//str.size() <= > str.length() 返回 string::size_type 类型(unsigned int)  字符串的实际长度(不包括'\0')
		//str.max_size()：返回string对象最多包含的字符数，很大的一个数(9223372036854775807)
		//str.capacity()：重新分配内存之前，string对象能包含的最大字符数
		//str.reserve(n);  手动申请重新分配内存,改变capacity()的大小,申请比当前小的不理你,也不一定是n的大小  string str("hello");  str.reserve(20);
		//str.resize(n); / str.resize(n, char);  改变串的长度,更小就截断('\0'结尾), 更大补char	   str.resize(20, 'p');
	//比较
		//支持 >, >=, <, <=, ==, !=
		//成员函数compare()  支持多参数处理，支持用索引值和长度定位子串进行比较
		//string str1("hello"), str2("heLLhe");
		//MyPrint(str1.compare(str2));				// 1
		//MyPrint(str1.compare(0, 2, str2));		// -1  str1下标0开始2个元素与str2整串比较
		//MyPrint(str1.compare(0, 2, str2, 4, 2)); // 0  str1下标0开始2个元素与str2的下标4开始2个元素
	//插入：push_back() 和 insert()  参数为char
	//删除：erase()
		//iterator erase(iterator p)：删除字符串中p所指的字符																s1.erase(s1.begin() + 1);
		//	iterator erase(iterator first, iterator last)：删除字符串中迭代器区间[first, last) 上所有字符		s1.erase(s1.begin() + 1, s1.end() - 2); 
		//	string& erase(size_t pos, size_t len)：删除字符串中从索引位置 pos 开始的 len 个字符				s1.erase(1, 6);
		//	void clear()：删除字符串中所有字符
	//替换   s1.swap(s2);
	//字符替换																																										string s1("hello,world!");
		//string& replace(size_t pos, size_t n, const char *s)：将当前字符串从pos索引开始的n个字符，替换成字符串s           s1.replace(6, 5, "girl");		hello,girl!
		//string& replace(size_t pos, size_t n, size_t n1, char c)：将当前字符串从pos索引开始的n个字符，替换成n1个字符c  s1.replace(s1.size() - 1, 1, 1, '.');	hello,girl.
		//string& replace(iterator i1, iterator i2, const char* s)：将当前字符串[i1, i2)区间中的字符串替换为字符串s				s1.replace(s1.begin(), s1.begin() + 5, "boy");	boy,girl.
	//tolower() 和 toupper() 或者 STL中的 transform 算法
		//tolower() 和 toupper() 参数为int(char),转小写,大写
		//transform  将某操作应用于指定范围的每个元素
			//transform(first,last,result,op);//first是容器的首迭代器，last为容器的末迭代器，result为存放结果的容器，op为要进行操作的一元函数对象
			//transform(first1,last1,first2,result,binary_op);//first1是第一个容器的首迭代 器，last1为第一个容器的末迭代器，first2为第二个容器的首迭代器，
			//result为存放结果的容器，binary_op为要进行操作的二元函数 对象; 必须要保证两个容器的元素个数相等才行，否则会抛出异常
			//string s1("hello"), s2("world");
			////transform(s1.begin(), s1.end(), s1.begin(), toupper);
			//transform(s1.begin(), s1.end(), s2.begin(), s2.begin(), STLAlgorithm::compa);
	//分割/截取字符串(取字串)
		//string s2 = s1.substr(2, 4);  //取s1下标2开始4个字符
		//s2 = s1.substr(2); //取s1下标2开始到 string::npos		
	//查找子串和字符(没找到返回string::npos)
		//find(const char* s, size_t pos = 0)/rfind：在当前字符串的pos索引位置开始，查找子串s，返回找到的位置索引
		//find(char c, size_t pos = 0)/rfind：在当前字符串的pos索引位置开始，查找字符c，返回找到的位置索引
		//find_first_of(const char* s, size_t pos = 0)/find_last_of：在当前字符串的pos索引位置开始，查找子串s的字符(包含的任意字符)，返回找到的位置索引
		//find_first_not_of(const char* s, size_t pos = 0)/find_last_not_of：在当前字符串的pos索引位置开始，查找第一个不位于子串s的字符(包含的任意字符)，返回找到的位置索引
	//遍历  
		//正向迭代器 str.begin()、str.end()
		//反向迭代器 str.rbegin()、str.rend()
	//用 STL 算法操作 string 对象
		//	sort(s.begin(), s.end());
	//string 对象作为流处理
		//	string src("Avatar 123 5.2 Titanic K");
		//istringstream istrStream(src); //建立src到istrStream的联系
		//string s1, s2;
		//int n;  double d;  char c;
		//istrStream >> s1 >> n >> d >> s2 >> c; //把src的内容当做输入流进行读取	

	//	string str = "hello " + "world";  //错误，必须有一个是string对象 string("hello ")
	//拼接性能 += append  stringstream  sprintf
	
	//转换函数
		// int atoi(const char *nptr);//stoi
		// std::to_string(value);
}

void STLAlgorithm::VectorTest()
{
	//vector构造
		// explicit vector(size_type n);		vector<int> vec(10);  10个默认值元素
		// vector<int> vec(10, 1);  10个1;
		// vector<int> vec(b);  拷贝/移动构造
		// vector<int> vec(b.begin(), b.begin()+3); 
		// vector(initializer_list<value_type>il)	vector<int> vec{1,2,3};

	//Capacity 容量
		//empty()/max_size()
		//capacity()/reserve()
		//size()/resize()	
		//shrink_to_fit()	//回收size以外的多余内存
	
	//assign
		// vec.assign(b.begin(), b.begin()+3);
		// vec.assign(size_type n, const value_type& val);
		// vec.assign({1,2,3});
	// push_back , pop_back, emplace_back
	// insert, emplace, swap
	// erase, clear		

	//note:
	// 未初始化的vector容器不能进行下标操作
		// vector<int> vec;
		// vec[0] = 1;
	//clear()并不真正释放内存(这是为优化效率所做的事)，
		//	clear实际所做的是为vector中所保存的所有对象调用析构函数(如果有的话), 然后初始化size这些东西，让觉得把所有的对象清除了。
		//	真正释放内存是在vector的析构函数里进行的，所以一旦超出vector的作用域（如函数返回)，
		//	首先它所保存的所有对象会被析构，然后会调用allocator中的deallocate函数回收对象本身的内存。
		// 可用 vector<int>(vec).swap(vec); 或是 vec.shrink_to_fit();
	vector<int> vec(3);
	MyPrint(vec.capacity());

}

void STLAlgorithm::AlgorithmTest()
{
	//查找
	/*
		auto it = find(vec.begin(), vec.end(), 2);
		auto it = find_if(vec.begin(), vec.end(), [](int val) { return val % 2 == 0; });

		it = find_first_of(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
		//遍历vec1,到vec2中找相等的,找到返回, 返回vec1迭代器,没有就end()

		it = find_end(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
		//在vec1中找与vec2子串完全匹配的最后一组,找到返回, 返回vec1迭代器,没有就end()

		auto it = search(vec.begin(), vec.end(), vec1.begin(), vec1.end());
		auto it = search_n(vec.begin(), vec.end(), 2, 8); //找连着的2个8

		auto it = count(vec.begin(), vec.end(), 8); //统计有几个8
		auto it = count_if(vec.begin(), vec.end(), [](int val) { return val % 2 == 0; });

		二分查找(必须已序)
		auto it = lower_bound(vec.begin(), vec.end(), 4);     // 第一个大于等于
		auto it = upper_bound(vec.begin(), vec.end(), 4);    // 第一个大于
		二分查找(必须已序)
		auto it = equal_range(vec.begin(), vec.end(), 8);
		cout << *(it.first )<< ", index: " << it.first - vec.begin() << endl;
		cout << *(it.second )<< ", index: " << it.second - vec.begin() << endl;
		二分查找(必须已序)
		bool isHave = binary_search(vec.begin(), vec.end(), 8);

		bool isequal = equal(vec1.begin(), vec1.end(), vec2.begin());  vec2的长度必须>=vec1
		bool isequal = equal(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

	*/

	//排序
	/*
		sort(vec.begin(), vec.end(), greater<>());  默认less<>()
		stable_sort  同上,但相等元素保持相对位置不变

		partial_sort(vec.begin(), vec.begin() + 4, vec.end());	只排序前几个出来,其他不管(partial  adj. 局部的),默认从小到大
		partial_sort(vec.begin(), vec.begin() + 4, vec.end(), greater<>());

		合并(必须已序)vec,vec1到vec2中, vec2还是有序的
		vector<int> vec2(15);
		merge(vec.begin(), vec.end(), vec1.begin(), vec1.end(), vec2.begin());
	*/

	/*
		随机打乱
		random_shuffle(vec2.begin(), vec2.end());
		反转
		reverse(vec2.begin(), vec2.end());
		旋转, 将[0,1)与[1,2)交换 1就成了begin
		rotate(vec2.begin(), vec2.begin()+5, vec2.end());

		最小,最大元素
		auto it = min_element(vec2.begin(), vec2.end());  // auto it = min(vec2.begin(), vec2.end());
		auto it = max_element(vec2.begin(), vec2.end()); // max()

		填充随机数
		generate(vec2.begin(), vec2.end(), []() { return rand() % 5; });

		将vec1复制到vec2, vec2必须足够大
		copy(vec1.begin(), vec1.end(), vec2.begin());
		将vec1的元素经过处理再复制到vec2, vec2必须足够大
		transform(vec1.begin(), vec1.end(), vec.begin(), [](int v) {  return v + 100; });
		transform(vec.begin(), vec.end(), vec.begin(), [](int v) {  return v + 100; });  //遍历所有元素调用处理函数

		替换 8换成-8
		replace(vec.begin(), vec.end(), 8, -8);
		replace_if

		剔除(并不是真正删除) remove并非真正删除,只是挪到后面,甚至size都没变
		remove(vec.begin(), vec.end(), 8);
		remove_if
		//auto itr = std::remove(vec.begin(), vec.end(), 6);
		//if (itr != vec.end())
		//vec.erase(itr, vec.end()); 真正删除
		//auto itr = vec.begin();
		//auto lastItr = itr;
		//while (itr != vec.end())
		//{
		//	if (*itr != 6)
		//	{
		//		*lastItr = *itr;
		//		++lastItr;
		//	}
		//	++itr;
		//}
		//}

		相邻的去重(并不是真正删除)
		unique(vec.begin(), vec.end());

		填充, 全写入8
		fill(vec.begin(), vec.end(), 8);
		fill_n(vec.begin() , 3, 99);  前3个改成99( vec够3个,不能越界)

		
	*/
}
