#pragma once
#include<atomic>

class AtomicTest
{
public:
	static void Test();
};

//atomic_flag������  -- ��������������������Χ����ѭ������ת��
class spinlock_mutex
{
private:
	std::atomic_flag flag{ ATOMIC_FLAG_INIT };
public:
	spinlock_mutex()
	{

	}

	void lock()
	{
		while (flag.test_and_set(std::memory_order_acquire));
	}

	void unlock()
	{
		flag.clear(std::memory_order_release);
	}
};