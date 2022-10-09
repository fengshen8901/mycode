#pragma once


class StlTest
{

public:
	//查找算法
	static void FindTest();

	//排序和通用算法
	static void SortAndCommon();

	//删除和替换算法
	static void RemoveAndReplace();

	//排列组合算法
	static void PermutationTest();

	//算术算法
	static void MathTest();

	//生成和异变算法
	static void TransformTest();

	//关系算法
	static void EqualTest();

	//集合算法
	static void SetTest();

	//堆算法
	static void HeapTest();
};

//仿函数（Functor）
//STL内建的仿函数，必须包含<functional>头文件
//1）算术类仿函数
//加：plus<T>
//减：minus<T>
//乘：multiplies<T>
//除：divides<T>
//模取：modulus<T>
//否定：negate < T>
//2）关系运算类仿函数
//等于：equal_to<T>
//不等于：not_equal_to<T>
//大于：greater<T>
//大于等于：greater_equal<T>
//小于：less<T>
//小于等于：less_equal<T>
//逻辑与：logical_and<T>
//逻辑或：logical_or<T>
//逻辑否：logical_no<T>

//适配器（Adaptor）
//标准库提供了三种顺序容器适配器：queue(FIFO队列)、priority_queue(优先级队列)、stack(栈)
//stack<int, vector<int> >实现了栈的功能，但其内部使用顺序容器vector<int>来存储数据
//种类		默认顺序容器	可用顺序容器				说明
//stack	deque		vector、list、deque
//queue	deque		list、deque				基础容器必须提供push_front()运算
//priority_queue		vector	vector、deque	基础容器必须提供随机访问功能

