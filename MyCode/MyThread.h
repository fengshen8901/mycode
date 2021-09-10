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

// std::lock(mt, mt1); //������, ������,��������(Ҫô����,Ҫô������)
// std::lock_guard<std::mutex> lk(mt, std::adopt_lock); //�����Զ��ͷ�,����2,�Ѿ����˵�,��������
// std::lock_guard<std::mutex> lk1(mt1, std::adopt_lock);

// std::unique_lock<std::mutex> lk(mt, atd::defer_lock); //�����,��ʧ����,���ƶ�, �ɲ���2,,�ȱ���
// lk.lock();
// lk.unlock();

// 1.��ֻ�г�ʼ����Ҫ��(�ӳٳ�ʼ��)
//  std::once_flag fg;
//  std::call_once(fg, Init);
//  std::call_once(fg, &X::Init, this); ���ڵ���

// 2.���ٸ���(����,д��)
//  boost::shared_mutex mt;
//  std::lock_guard<boost::shared_mutex> lk;  //д
//  boost::shared_lock<boost::shared_mutex> sk;  //��
// ���ж����Թ�����, ���ж�����ʱ,д���ȴ�; д��ʱ,���ж��ȴ�

// 3.�ݹ���(�ݹ黥��Ԫ)ͬһ�߳̿��ظ���  ��������
// һ�㻥��Ԫ,����ʱ�ٵ���lock,������δ������Ϊ,
// �������к�����Ա���Ȼ�ȡ����doSomething, ����ʱ������,
// std::recursive_mutex mt;
// std::lock_guard<std::recursive_mutex> lk(mt);

//��������(��ʹ������������װһ���̰߳�ȫ����)
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

//��ֵ future, �ȴ�һ�����¼�,һ���¼�����(����),���޷���λ
// Ψһfuture(std::future<>); ����future(std::shared_future<>)
//1.�Ӻ�̨�����з���(�첽����)
// int getResult(){}
// std::future<int> fu = std::async(getResult);
// dosomething();
// auto res = fu.get();
// std::asyncĬ����ϵͳ�����ڵ����߳������л����ӳٵȴ�wait��get����ʱ����
// std::async(std::launch::async, getResult); ���µ��߳�������
// std::async(std::launch::deferred, getResult);  �ӳٵȴ�wait��get����ʱ����

//2.��������future�����--(��������������̵߳���,���ؽ��)
//std::packaged_task<>��һ��future�󶨵�һ��������ɵ��ö�����,����ʱfuture����
//ָ���ĺ���ǩ���ķ���ֵ���;�����std::future<>��ģ������
//�̼߳䴫������
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

//3.����std::promise, �������Ա����set_value,ʹ�����--(�����������ø�����߳�,���ú�ֵ����)
//std::promise<int> pr;
//std::future<int> fu = pr.get_future();
//std::thread th([&pr] { pr.set_value(123); });
//int val = fu.get();

//std::future<> �ǽ����ƶ��ģ�ֻ��һ���߳̿��Ի�ȡֵ����Ϊ���״ε���get()�󣬾�û�пɻ�ȡ�Ķ�����
//��Ҫ����̵߳ȴ�ͬһ���¼�������std::shared_future<>,��Ҳ�����ݾ����������������������������
//��õķ�ʽ���ڸ����̸߳���һ��std::shared_future<>,���߳�ͨ���Լ��ĸ���ȥ�ȴ���ȡֵ
//����future����
// std::promise<int> p;
// auto sf = p.get_future().share();   //std::shared_future<int>

//ʱ��
// ����ʱ�ӡ���ʵʱ�䡱 std::chrono::system_clock
// ����ʱ��  std::chrono::steady_clock
// ��С����ʱ��������ڣ��Ϳ��ܵ���߾��ȣ� std::chrono::high_resolution_clock
//
// static����now,��ȡ����ʱ��
// static���ݳ�Աis_steady,�Ƿ��Ծ��ȵ����ʽ��м�ʱ
// ��ȡ����ʱ��ֵ���ͣ� ...clock::time_point
// ʱ�ӵĽ������ڣ�����ʱ�ӵ�period��Աtypedef������std::ratio<1,25> 25��/��

//ʱ���
// std::chrono::duration<>
// ��һ��ģ�������int, long, double)
// �ڶ����Ǹ������� std::ratio<60,1> 60��һ�ģ�������ӣ� std::ratio<1,1000> ����
// ��һ��Ԥ�����typedef,  std::chrono::hours, minutes, seconds
// ���໥ת�������㣬ת���ǽضϵģ�����ض��ǿ���ʽת����תС��
// Сת�� std::chrono::seconds cs;  
// ʱ����е�λʱ��ļ�����ͨ��count()��Ա������ȡ std::chrono::seconds(5).count() = 5
// std::chrono::minutes ms = std::chrono::duration_cast<std::chrono::seconds>(cs);
// std::future<int> f = std::async(some_task);
// if(f.wait_for(std::chrono::milliseconds(35)) == std::future_status::ready)  //��������
//    auto val = f.get();
// ����ʱ���� std::future_status::timeout
// �������Ƴٷ��� std::future_status::deferred

//ʱ��� 
// ��һ���ض���ʱ��㱻��Ϊ��Ԫ��epoch),ʱ�ӵļ�Ԫ��һ�����������������ֱ�Ӳ�ѯ
// �����Ԫ����1970��1��1��0��
// ��Ȼ��Ԫ���ܲ�ѯ�����ܵõ�ʱ�Ӽ�Ԫ����ʱ����ʱ�䳤��
// time_point�ĳ�Ա����time_since_epoch(),������һʱ���
// std::chrono::time_point<>
// ��һ��ģ����� ָ����ο���ʱ��
// �ڶ���ģ�������ָ��������λ��ʱ��Σ�
// ����ʱ���(time_point)����ɵõ�һ��ʱ���(duration)

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

