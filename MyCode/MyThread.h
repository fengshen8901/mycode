#pragma once
#include <iostream>
#include <mutex>
#include <queue>
#include <future>
#include <thread>
// std::mutex mt, mt1;
// std::lock_guard<std::mutex> lk(mt);
// std::unique_lock<std::mutex> uk(mt);

//std::thread::hardware_concurrency();
//std::thread::get_id();
//std::thread::native_handle() SuspendThread  ResumeThread

// std::lock(mt, mt1); //锁起来, 多重锁,避免死锁(要么都锁,要么都不锁)
// std::lock_guard<std::mutex> lk(mt, std::adopt_lock); //用来自动释放,参数2,已经锁了的,不用再锁
// std::lock_guard<std::mutex> lk1(mt1, std::adopt_lock);

// std::unique_lock<std::mutex> lk(mt, atd::defer_lock); //更灵活,损失性能,可移动, 可参数2,,先别锁
// lk.lock();
// lk.unlock();

// 1.如只有初始化需要锁(延迟初始化)
//  std::once_flag fg;
//  std::call_once(fg, Init);
//  std::call_once(fg, &X::Init, this); 类内调用

// 2.很少更新(读多,写少)
//  boost::shared_mutex mt;
//  std::lock_guard<boost::shared_mutex> lk;  //写
//  boost::shared_lock<boost::shared_mutex> sk;  //读
// 所有读可以共享锁, 当有读的锁时,写锁等待; 写锁时,所有读等待

// 3.递归锁(递归互斥元)同一线程可重复锁  不建议用
// 一般互斥元,已锁时再调用lock,将引发未定义行为,
// 类中所有函数成员都先获取锁再doSomething, 互调时将报错,
// std::recursive_mutex mt;
// std::lock_guard<std::recursive_mutex> lk(mt);

//条件变量(可使用条件变量封装一个线程安全队列)
//std::mutex mt;
//std::condition_variable dv;
//std::queue<int> que;
//void thread1_add(int val)
//{
//	std::lock_guard<std::mutex> lk(mt);
//	que.push(val);
//	dv.notify_one(); //dv.notify_all();
//}
//void thread2_pro()
//{
//	while (true)
//	{
//		std::unique_lock<std::mutex> uk(mt);
//		dv.wait(uk, [] { return !que.empty(); });
//		auto val = que.front();
//		que.pop();
//		uk.unlock();
//		//dosomething();
//	}
//}

//期值 future, 等待一次性事件,一旦事件发生(就绪),就无法复位
// 唯一future(std::future<>); 共享future(std::shared_future<>)
//1.从后台任务中返回(异步调用)
// int getResult(){}
// std::future<int> fu = std::async(getResult);
// dosomething();
// auto res = fu.get();
// std::async默认由系统决定在单独线程中运行还是延迟等待wait或get调用时运行
// std::async(std::launch::async, getResult); 在新的线程中运行
// std::async(std::launch::deferred, getResult);  延迟等待wait或get调用时运行

//2.将任务与future相关联--(给个函数给别的线程调用,返回结果)
//std::packaged_task<>将一个future绑定到一个函数或可调用对象上,调用时future就绪
//指定的函数签名的返回值类型决定了std::future<>的模板类型
//线程间传递任务
 //std::mutex mt;
 //std::queue<std::packaged_task<int(void)> > tasks;
 //void thread1()
 //{
	// std::packaged_task<int()> task;
	// {
	//	 std::lock_guard<std::mutex> lk(mt);
	//	 if (tasks.empty()) return;
	//	 task = std::move(tasks.front());
	//	 tasks.pop();
	// }
	// task();
 //}
 //void thread2()
 //{
	// std::packaged_task	<int()> task([] {return 123; });
	// std::future<int> fu = task.get_future();
	// {
	//	 std::lock_guard<std::mutex> lk(mt);
	//	 tasks.push(std::move(task));
	// }
	// int val = fu.get();
 //}

//3.生成std::promise, 调用其成员函数set_value,使其就绪--(传个变量引用给别的线程,设置好值给我)
//std::promise<int> pr;
//std::future<int> fu = pr.get_future();
//std::thread th([&pr] { pr.set_value(123); });
//int val = fu.get();

//std::future<> 是仅可移动的，只有一个线程可以获取值，因为在首次调用get()后，就没有可获取的东西了
//需要多个线程等待同一个事件，可用std::shared_future<>,但也有数据竞争的情况，必须用锁来保护访问
//最好的方式是在各个线程复制一份std::shared_future<>,各线程通过自己的副本去等待获取值
//是由future构造
// std::promise<int> p;
// auto sf = p.get_future().share();   //std::shared_future<int>

//时钟
// 常用时钟“真实时间” std::chrono::system_clock
// 匀速时钟  std::chrono::steady_clock
// 最小可能时间节拍周期（和可能的最高精度） std::chrono::high_resolution_clock
//
// static函数now,获取现在时间
// static数据成员is_steady,是否以均匀的速率进行计时
// 获取到的时间值类型， ...clock::time_point
// 时钟的节拍周期，（由时钟的period成员typedef给出，std::ratio<1,25> 25拍/秒

//时间段
// std::chrono::duration<>
// 第一个模板参数（int, long, double)
// 第二个是个分数， std::ratio<60,1> 60秒一拍，代表分钟， std::ratio<1,1000> 毫秒
// 有一组预定义的typedef,  std::chrono::hours, minutes, seconds
// 可相互转换及运算，转换是截断的，无需截断是可隐式转（大转小）
// 小转大， std::chrono::seconds cs;  
// 时间段中单位时间的计数可通过count()成员函数获取 std::chrono::seconds(5).count() = 5
// std::chrono::minutes ms = std::chrono::duration_cast<std::chrono::seconds>(cs);
// std::future<int> f = std::async(some_task);
// if(f.wait_for(std::chrono::milliseconds(35)) == std::future_status::ready)  //就绪返回
//    auto val = f.get();
// 若超时返回 std::future_status::timeout
// 若任务推迟返回 std::future_status::deferred

//时间点 
// 有一个特定的时间点被称为纪元（epoch),时钟的纪元是一项基本参数，但不能直接查询
// 经典纪元包括1970年1月1日0点
// 虽然纪元不能查询，但能得到时钟纪元到该时间点的时间长度
// time_point的成员函数time_since_epoch(),返回这一时间段
// std::chrono::time_point<>
// 第一个模板参数 指定其参考的时钟
// 第二个模板参数，指定计量单位（时间段）
// 两个时间点(time_point)相减可得到一个时间段(duration)

template<typename T>
class SafeQueue
{
public:

void push(T val)
{
	std::lock_guard<std::mutex> lk(mt);
	que.push(val);
	dv.notify_one(); //dv.notify_all();
}
void wait_pop(T& val)
{
	std::unique_lock<std::mutex> uk(mt);
	dv.wait(uk, [this] { 
		return !que.empty(); 
		});
	val = que.front();
	que.pop();
}

bool try_pop(T& val)
{
	std::lock_guard<std::mutex> lk(mt);
	if (que.empty())
		return false;
	val = que.front();
	que.pop();
	return true;
}
private:
	std::mutex mt;
	std::condition_variable dv;
	std::queue<T> que;
};

class MyThread
{
public:
	
private:
};

