#include <iostream>
#include <algorithm>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "STLalgorithm.h"
#include "Tool.h"

using namespace std;
using namespace Tool;


//
// 3个容器适配器
// 每个适配器都定义两个构造，默认构造创建一个空对象； 接受一个容器的构造函数
// 默认情况下，stack, queue是基于deque实现，priority_queue是在vector之上实现的
// 但可以在创建适配器是指定
// 
// stack<string, vector<string> > str_stk;  vector实现的栈
// stack<int> stk;
// stk.push(1);
// auto val = stk.top();
// stk.pop();
// 
// priority_queue 优先队列  push 插入元素到队尾 (并排序)
// 升序队列，小顶堆
// priority_queue <int, vector<int>, greater<int> > q;
// 降序队列，大顶堆 (默认)
// priority_queue <int, vector<int>, less<int> >q;

//插入迭代器
// back_inserter
// front_inserter
// inserter
//   auto it = inserter(vec, iter); 得到一个插入迭代器
//   *it = val;  <=>  it = vec.insert(iter, val);  ++it;
// 
// vector<int> vec{1,2,3};
// auto it = back_inserter(vec);
// *it = 4;
//  *it = 5;
// auto iter = inserter(vec, vec.end());
// *iter = 6;
//

// 
// 顺序容器类型
// vector, deque, list, forward_list, array, string
//
// list和forward_list成员函数
// lst.merge(lst2);
// lst.merge(lst2, comp);
//   lst,lst2都必须是有序的，合并后lst2变为空
// lst.remove(val);
// lst.remove_if(pred); 
//   调用erase删除满足条件的每个元素（通用版本不会删除）
// lst.reverse();  反转元素顺序
// lst.sort();
// lst.sort(comp);
// lst.unique();
// lst.unique(pred);
//   调用erase删除相邻重复元素
// 
// splice/splice_after  捻接; 绞接(两段绳子);
// lst.splice(p, lst2);	 将lst2中所有元素移动到lst的p之前，两链表必须类型相同，且不能是同一链表
// lst.splice(p, lst2, p2);  将lst2中p2指向的元素移动到lst的p之前，可以同一链表
// lst,splice(p, lst2, b, e);  将lst2中给定的范围元素移动到lst的p之前，可以同一链表，但p不能指向给定范围中元素
// 
//顺序容器操作基本类似，以vector为例
void STLAlgorithm::VectorTest()
{
	//构造
		// vector<int> vec(10);  10个默认值元素
		// vector<int> vec(10, 1);  10个1;
		// vector<int> vec1(vec);  拷贝/移动构造   类型必须匹配
		//		内置数组类型不允许拷贝或对象赋值，但array可以（显示赋值不能用{}，因为可能会大小不同）
		// vector<int> vec(b.begin(), b.begin()+3);  类型可以不同但元素间须可转换
		//	    vector<string> vst;  
		//     vector<const char*> vc(vst.begin(), vst.end());
		// vector(initializer_list<value_type>il)	vector<int> vec{1,2,3};

	//Capacity 容量
		//empty()/max_size()
		//capacity()/reserve()
		//size()/resize()	  //forward_list不支持 size()
		//shrink_to_fit()	//回收size以外的多余内存

	//assign
		// vec.assign(b.begin(), b.begin()+3);
		// vec.assign(size_type n, const value_type& val);
		// vec.assign({1,2,3});	

	// swap(v1, v2);  元素本身并未交换，只交换了两个容器的内部数据结构
	// 所有迭代器并不会失效，但指向交换之前的容器（string迭代器会失效）
	// array会真正交换他们的元素，迭代器指向的元素已经发生改变
	// 
	// 关系运算符 （比较容器大小）必须相同类型的容器且元素类型相同
	// 类似与string的比较，主要取决于第一个不相等元素的大小
	// 
	// 顺序容器添加元素
	// 	c.push_back(t); c.emplace_back(args);
	// 	c.push_front(); c.emplace_front(args);
	// 	c.insert(p, t); c.emplace(p, args);
	// 	c.insert(p, n, t);  c.insert(p, b, e);  c.insert(p, il);  //il -> initializer_list
	// forward_list不支持push_back,emplace_back;有自己专业版本的insert,emplace
	// vector,string不支持push_front,emplace_front;
	// 
	// 删除元素
	//     c.pop_back();  c.pop_front();
	// 	c.erase(p);  c.erase(b, e);
	// 	c.clear();    <=>  c.erase(c.begin(), c.end() );
	// forward_list不支持pop_back,有自己特殊版本的erase
	// vector,string不支持pop_front
	// 
	// 特殊的forward_list操作
	//   当删除第3个元素时，第2个指向第4个，找第3个的前一个(第2个)不好找，
	//  所以提供特殊的操作 添加/删除当前的下一个元素
	// 	   lst.before_begin();  lst.cbefore_begin();    首前(首元素之前并不存在的元素)
	// 	   lst.insert_after(p, t);  lst.insert_after(p, n, t);
	// 	   lst.insert_after(p, b, e);  lst.insert_after(p, il);
	// 	   lst.emplace_after(p, args);
	// 	   lst.erase_after(p);  lst.erase(p, b, e);
	// 
	
	
	//note:
	// 未初始化的vector容器不能进行下标操作
		// vector<int> vec;
		// vec[0] = 1;
	//clear()并不真正释放内存(这是为优化效率所做的事)，
		//	clear实际所做的是为vector中所保存的所有对象调用析构函数(如果有的话), 然后初始化size这些东西，让觉得把所有的对象清除了。
		//	真正释放内存是在vector的析构函数里进行的，所以一旦超出vector的作用域（如函数返回)，
		//	首先它所保存的所有对象会被析构，然后会调用allocator中的deallocate函数回收对象本身的内存。
		// 可用 vector<int>(vec).swap(vec); 或是 vec.shrink_to_fit();
	//如果在一个循环中插入/删除容器中的元素，不要缓存end()返回的迭代器，会失效，应该每次调用while(itr != c.end())


}

// 
// 关联容器类型(8种）
// map, set
// multimap, multiset
// unordered_map, unordered_set
// unordered_multemap, unordered_multeset
// 有序容器的键值类型必须定义元素的比较方法，“<”，或指定排序的比较函数指针
//
// 插入操作
// c.insert(v);
// c.emplace(args);
// c.insert(b, e);
// c.emplace(il);
//   c.insert(p, v); c.emplace(p, args);  p为提示从哪开始搜索新元素应该存储的位置
// 返回值，不包含(unordered)重复关键字的容器，返回pair, 
//	    first 添加的新元素的迭代器
//     second (bool),已经存在啥也不干返回false,插入成功返回true
//  包含(unordered)重复关键字的容器，返回新元素的迭代器
//
// 删除操作
// c.erase(key); 返回删除的元素数量
// c.erase(p); 返回删除的下一个迭代器
// c.erase(b, e); 返回e
// 
// 下标操作
// set没有下标操作（因为没有”值“）
// 不能对multimap, unordered_multimap进行下标操作
// 对map进行下标操作时，如果不存在会创建一个元素并插入到map中，关联值将进行值初始化(0)
// 
// c.find(k); 返回一个迭代器
// c.count(k); 返回关键字等于k的元素数量
// c.lower_bound(k);  返回第一个关键字不小于k的元素的迭代器
// c.upper_bound(k);  返回第一个关键字大于k的元素的迭代器
// c.equal_range(k);  返回一个pair, 关键字等于k的元素的范围 [ )，若没有，两个c.end()
//
// 桶
//   无序容器，根据元素键的哈希值存到相应的桶，相同的哈希值元素存到相同的桶
// 桶接口
// c.bucket_count();  正在使用的桶的数目
// c.max_bucket_count();  容器能容纳的最多的桶的数量
// c.bucket_size(n);  第n个桶中元素个数
// c.bucket(k);  关键字k的元素在第几个桶
// 桶迭代
// local_iterator/const_local_iterator  桶中元素的迭代器类型
// c.begin(n); c.end(n);  桶n的首(尾后)元素迭代器
// c.cbegin(n); c.cend(n);
// 哈希策略
// c.load_factor()  每个桶的平均元素数量(float)
// c.max_load_factor();  
// c.rehash(n);  重组存储，使得bucket_count>=n
// c.reserve(n);  重组存储，使得c可以保存n个元素且不必rehash
// 
//无序容器对关键字类型的要求：
// 有==运算符，和哈希计算函数 如下
//

size_t myhash(const Element& v)
{
	return hash<string>()(v.str);
}

bool CompE(const Element& a, const Element& b)
{
	return a.str == b.str;
}

void STLAlgorithm::MapTest()
{
	//桶的期望大小，哈希函数指针，相等性判断运算符指针
	unordered_map<Element, int, decltype(myhash)*, decltype(CompE )*> m(42, myhash, CompE);
	m["abc"] = 2;
	m["bcd"] = 3;
	cout << m.begin()->second << endl;;
	unordered_set<Element, decltype(myhash)*, decltype(CompE)*> s(2, myhash, CompE);
	s.insert("abc");
	

	cout << s.bucket_count();
}

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
		copy_if(beg, end, dest, unaryPred);
		copy_n(beg, n, dest);

		move(beg, end, dest);

		将vec1的元素经过处理再复制到vec2, vec2必须足够大
		transform(vec1.begin(), vec1.end(), vec.begin(), [](int v) {  return v + 100; });
		transform(vec.begin(), vec.end(), vec.begin(), [](int v) {  return v + 100; });  //遍历所有元素调用处理函数
		
		transform(beg, end, beg2, dest, binaryOp);  两个序列二元操作

		替换 8换成-8
		replace(vec.begin(), vec.end(), 8, -8);
		replace_if

		填充, 全写入8
		fill(vec.begin(), vec.end(), 8);
		fill_n(vec.begin() , 3, 99);  前3个改成99( vec够3个,不能越界)

		重排操作
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
		unique(beg, end, binaryPred);

		围绕mid指向的元素进行元素转动，元素mid成为首元素，其次是mid+1到end, beg到(mid-1),返回原来begin迭代器
		

		
	*/
}
