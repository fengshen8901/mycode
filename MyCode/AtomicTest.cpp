#include "AtomicTest.h"
#include <iostream>

//标准原子类型（几乎）都具有一个is_lock_free()成员函数（除atomic_flag）,检查是否无锁的
//直接用原子指令完成(true), 用锁来完成(false)
// 
//std::atomic_flag,一个非常简单的布尔标识，无锁的（其他不保证无锁）
// 唯一保证无锁，唯一需要特殊初始化
//最简单的标准原子类型() std::atomic_flag f = ATOMIC_FLAG_INIT; 必须这样初始化（清除状态）
//只能 销毁(析构), 清除clear()，设置并查询先前的值(test_and_set())

//标准原子类型是不可复制不可赋值的，没有拷贝构造和拷贝赋值运算符
// load(),读
//  store(), 写
// exchange(), 读-修改-写
// 指针原子类型支持自加、自减、+=、-=等运算符
// fetch_add(), fetch_sub()   交换与添加，读-修改-写操作
// 返回原值，本身进行运算  a.fetch_add(2); 返回a之前的值，a本身偏移2
// 
// 比较/交换
// 比较原子变量值和预料值，相等则存储期望值返回true, 不等则将预料值更新为原子变量实际值返回false
// (预料值引用，期望值）
// compare_exchange_weak(), 可能伪失败(比较值相等，但机器原因操作未处理)，通常用在循环中
// while(!b.compare_exchange_weak(expected, desired) && ! expected)
// compare_exchange_strong()
// 
//标准原子的整型操作支持 前缀/后缀的自加/自减, +=,-=,&=,|=,^=, fetch_add, fetch_sub,
//fetch_and, fetch_or, fetch_xor
// 只有乘法，除法和位移运算符是缺失的
// 浮点值(double, float)没有原子的算术操作

//std::atomic<>初级类模板，创建自定义类型的原子变种
// 该自定义类型必须满足一定的准则：
//     有一个平凡(trivial)的拷贝赋值运算符, 意味着该类型不得拥有任何虚函数或虚基类，
// 并且必须使用编译器生成的拷贝赋值运算符，
//     所有基类和非静态数据成员也都必须有一个平凡的拷贝赋值运算符，即允许编译器
// 将memcpy或一个等价的操作用于赋值操作
//     必须是按位相等可比较，即必须能够使用memcmp比较实例是否相等
// 如果自定义类的大小与一个int或void*大小相同，大部分平台能够使用原子指令
//
//原子操作的自由函数（非成员函数-全局函数）
// 都是以相应的成员函数来命名的，只是带有一个atomic_前缀，指定内存顺序的还带_explicit后缀
// 如： std::atomic_load(&a); std::atomic_load_explicit(&a, std::memory_order_seq_cst)
// 还提供了以原子行为访问std::shared_ptr<>实例的自由函数，可以的原子操作有：
//  载入(load)、存储(store)、交换(exchange) 和比较/交换(compare/exchange)
// 接受std::shared_ptr<>*作为第一个参数
//
//在原子类型上的每一个操作均具有一个可选的内存顺序参数，可以用来指定所需的内存顺序语义
// 所有操作的默认顺序为std::memory_order_seq_cst
	//存储（store): 
		//std::memory_order_relaxed(松散);  std::memory_order_release;  std::memory_order_seq_cst
	//载入（load):
		//std::memory_order_relaxed; std::memory_order_consume; std::memory_order_acquire; 
		//std::memory_order_seq_cst
	//读-修改-写（read-modify-write):
		//std::memory_order_relaxed; std::memory_order_consume; std::memory_order_acquire
		//std::memory_order_release;  std::memory_order_acq_rel; std::memory_order_seq_cst 
//
// 这六种顺序选项其实代表了三种模型
// 顺序一致(sequentially consistent) memory_order_seq_cst
// 获得-释放(acquire-release) ... ... 其中 memory_order_consume 比较特别，数据依赖 
// 松散(relaxed) memory_order_relaxed
//

//std::this_thread::yield
void AtomicTest::Test()
{
	std::atomic_int a = 1; 
	int tmp = 1;
	std::cout << a.is_lock_free() << std::endl;
	if (a.compare_exchange_strong(tmp, 0))
	{
		std::cout << "true" << a << ", " << tmp << std::endl;
	}
	else
	{
		std::cout << "false" << a << ", " << tmp << std::endl;
	}
	//std::is_trivial<int>::value
}
