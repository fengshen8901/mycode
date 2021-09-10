#pragma once
#include <mutex>
//无界的 使用锁和条件变量等待的 线程安全队列
template<typename T>
class threadsafe_queue
{
private:
	struct node
	{
		std::shared_ptr<T> data;
		std::unique_ptr<node> next;
	};

	std::mutex head_mutex;
	std::unique_ptr<node> head;
	std::mutex tail_mutex;
	node* tail;
	std::condition_variable data_cond;

	node* get_tail()
	{
		std::lock_guard<std::mutex> lk(tail_mutex);
		return tail;
	}

	std::unique_ptr<node> pop_head()
	{
		std::unique_ptr<node> old_head = std::move(head);
		head = std::move(old_head->next);
		return old_head;
	}

	std::unique_lock<std::mutex> wait_for_data()
	{
		std::unique_lock<std::mutex> lk(head_mutex);
		data_cond.wait(lk, [&]() { return head->get() != get_tail(); });
		return std::move(lk);
	}

	std::unique_ptr<node> wait_pop_head()
	{
		std::unique_lock<std::mutex> lk(wait_for_data());
		return pop_head();
	}

	std::unique_ptr<node> wait_pop_head(T& value)
	{
		std::unique_lock<std::mutex> lk(wait_for_data());
		value = *(head->data);
		return pop_head();
	}

	std::unique_ptr<node> try_pop_head()
	{
		std::lock_guard<std::mutex> lk(head_mutex);
		if (head->get() == get_tail())
			return nullptr;
		return pop_head();
	}

	std::unique_ptr<node> try_pop_head(T& value)
	{
		std::lock_guard<std::mutex> lk(head_mutex);
		if (head->get() == get_tail())
			return nullptr;
		value = std::move(*head->data);
		return pop_head();
	}
public:
	threadsafe_queue() :head(new node), tail(head.get())
	{

	}

	threadsafe_queue(const threadsafe_queue& other) = delete;
	threadsafe_queue& operator=(const threadsafe_queue& other) = delete;	

	std::shared_ptr<T> wait_and_pop()
	{
		const std::unique_ptr<node> old_head = wait_pop_head();
		return old_head->data;
	}

	void wait_and_pop(T& value)
	{
		const std::unique_ptr<node> old_head = wait_pop_head(value);
	}

	void push(T value)
	{
		std::shared_ptr<T> new_data(std::make_shared<T>(std::move(value)));
		std::unique_ptr<node> p(new node);
		{
			std::lock_guard<std::mutex> lk(tail_mutex);
			tail->data = new_data;
			const node* new_tail = p.get();
			tail->next = std::move(p);
			tail = new_tail;
		}
		data_cond.notify_one(); 
		//data_cond.notify_all();
	}

	std::shared_ptr<T> try_pop()
	{
		const std::unique_ptr<node> old_head = try_pop_head();
		return old_head ? old_head->data : nullptr;
	}

	bool try_pop(T& value)
	{
		const std::unique_ptr<node> old_head = try_pop_head(value);
		return old_head;
	}

	bool empty()
	{
		std::lock_guard<std::mutex> lk(head_mutex);
		return head->get() == get_tail();
	}
};


