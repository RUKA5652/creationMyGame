#pragma once
#include<memory>
#include<vector>



template <class T>
class RingBufferItr
{
public:
	RingBufferItr();
	RingBufferItr(std::shared_ptr<std::vector<T>>  ringBuffer, std::vector<T>::iterator itr);
	void operator = (std::vector<T>::iterator& t);
	void operator = (std::vector<T>::iterator t);
	RingBufferItr<T> operator++();
	RingBufferItr<T> operator--();


	T& get();

private:
	std::vector<T>::iterator itr_;
	std::weak_ptr<std::vector<T>> ringbuffer_;
	template<class F>
	friend bool operator==(RingBufferItr<F> itr1, RingBufferItr<F> itr2);
	template<class F>
	friend bool operator!=(RingBufferItr<F>& itr1, RingBufferItr<F>& itr2);
};

#include"RingBufferItr/RingBufferItr.h"

template<class T>
inline T& operator*(RingBufferItr<T>& itr)
{
	return itr.get();
}

template <class T>
bool operator==(RingBufferItr<T> itr1, RingBufferItr<T> itr2)
{
	return itr1.itr_ == itr2.itr_;
}

template <class T>
bool operator!=(RingBufferItr<T>& itr1, RingBufferItr<T>& itr2)
{
	return itr1.itr_ != itr2.itr_;
}

