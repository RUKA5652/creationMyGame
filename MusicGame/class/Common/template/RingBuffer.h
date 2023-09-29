#pragma once
#include<memory>
#include <initializer_list>
#include"RingBufferItr.h"



//どんなバッファ,何を管理しているのか
template <class T > class RingBuffer
{
public:
	RingBuffer() { ringBuf_ = std::make_shared<std::vector<T>>(); };
	RingBuffer(std::initializer_list<T> init) :ringBuf_(std::make_shared<std::vector<T>>(init.begin(), init.end())) {};
	
	typedef RingBufferItr<T> iterator;

	RingBuffer<T>::iterator	begin() 
	{
		return { ringBuf_, ringBuf_.get()->begin() };
	};
	RingBuffer<T>::iterator	end() 
	{
		return { ringBuf_, ringBuf_.get()->end() };
	};

	const std::vector<T>* get()
	{
		return &(*ringBuf_);
	};

	void resize(rsize_t sz)
	{
		ringBuf_.get()->resize(sz);
	};



	T& at(size_t size)
	{
	/*	auto itr = ringBuf_.get()->begin();
		std::advance(itr, size);*/
		return ringBuf_.at(size);
	}

private:
	std::shared_ptr<std::vector<T>> ringBuf_;
	friend RingBufferItr<T>;
};


