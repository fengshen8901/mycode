#pragma once
#include <iostream>

enum class shape_type
{
	circle,
	triangle,
	rectangle,
};

class shape
{
public:
	virtual ~shape() {}
};

class circle : public shape
{

};

class triangle : public shape
{

};

class rectangle : public shape
{

};

shape* creat_shape(shape_type type);


class shape_wrapper
{
public:
	explicit shape_wrapper(shape* ptr = nullptr): ptr_(ptr)
	{
	}

	~shape_wrapper()
	{
		delete ptr_;
	}

	shape* get()
	{
		return ptr_;
	}

private:
	shape* ptr_;
};

class shared_count
{
public:
	shared_count() :count_(1)
	{

	}

	void add_count()
	{
		++count_;
	}

	long reduce_count()
	{
		return --count_;
	}

	long get_count() const
	{
		return count_;
	}

private:
	long count_;
};

template<typename T>
class smart_ptr
{
public:
	template<typename U>
	friend class smart_ptr;

	explicit smart_ptr(T* p = nullptr): ptr_(p)
	{
		if (p)
		{
			shared_count_ = new shared_count;
		}
	}

	smart_ptr(const smart_ptr& other)
	{
		ptr_ = other.ptr_;
		if (ptr_)
		{
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_;
		}
	}

	//smart_ptr(smart_ptr&& other) noexcept
	//{
	//	ptr_ = other.ptr_;
	//	if (ptr_)
	//	{
	//		shared_count_ = other.shared_count_;
	//		other.ptr_ = nullptr;
	//	}
	//}

	smart_ptr& operator=(smart_ptr other) noexcept
	{
		other.swap(*this);
		return *this;
	}

	template<typename U>
	smart_ptr(smart_ptr<U>&& other) noexcept
	{
		ptr_ = other.ptr_;
		if (ptr_)
		{
			shared_count_ = other.shared_count_;
			other.ptr_ = nullptr;
		}
	}

	template<typename U>
	smart_ptr(const smart_ptr<U>& other) noexcept
	{
		ptr_ = other.ptr_;
		if (ptr_)
		{
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_;
		}
	}

	template<typename U>
	smart_ptr(const smart_ptr<U>& other, T* p) noexcept
	{
		ptr_ = p;
		if (ptr_)
		{
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_;
		}
	}

	~smart_ptr()
	{
		if (ptr_ && !shared_count_->reduce_count())
		{
			delete ptr_;
			delete shared_count_;
		}
	}

	T* get() const noexcept
	{
		return ptr_;
	}

	T& operator*() const noexcept
	{
		return *ptr_;
	}

	T* operator->() const noexcept
	{
		return ptr_;
	}

	operator bool() const noexcept
	{
		return ptr_;
	}

	long use_count() const noexcept
	{
		if (ptr_ && shared_count_)
		{
			return shared_count_->get_count();
		}
		return 0;
	}

	void swap(smart_ptr& other) noexcept
	{
		using std::swap;
		swap(ptr_, other.ptr_);
		swap(shared_count_, other.shared_count_);
	}

private:
	T* ptr_;
	shared_count* shared_count_;
};

template<typename T, typename U>
smart_ptr<T> dynamic_pointer_cast(const smart_ptr<U>& other) noexcept
{
	T* p = dynamic_cast<T*>(other.get());
	return smart_ptr<T>(other, p);
}

template<typename T>
void swap(smart_ptr<T>& lhs, smart_ptr<T>& rhs) noexcept
{
	lhs.swap(rhs);
}