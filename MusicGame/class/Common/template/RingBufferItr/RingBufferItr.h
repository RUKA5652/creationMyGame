#pragma once
#include "..\RingBufferItr.h"




template <class T>
inline RingBufferItr<T>::RingBufferItr()
{
}

template <class T>
inline RingBufferItr<T>::RingBufferItr(std::shared_ptr<std::vector<T>> ringBuffer,std::vector<T>::iterator  itr)
{
	ringbuffer_ = ringBuffer;
	itr_ = itr;
}

template <class T>
inline void RingBufferItr<T>::operator=(std::vector<T>::iterator& t)
{
	itr_ = t;
}




template <class T>
inline void RingBufferItr<T>::operator=(std::vector<T>::iterator  t)
{
	itr_ = t;
}

template <class T>
inline  RingBufferItr<T> RingBufferItr<T>::operator++()
{
	if (++itr_ == ringbuffer_.lock().get()->end())
	{
		itr_ = ringbuffer_.lock().get()->begin();
		return *this;
	}
	return *this;
}

template <class T>
inline 	 RingBufferItr<T> RingBufferItr<T>::operator--()
{
	if (itr_ == ringbuffer_.lock().get()->begin() )
	{
		itr_ = --ringbuffer_.lock().get()->end();
		return *this;
	}
	--itr_;
	return *this;
}



template <class T>
inline T& RingBufferItr<T>::get()
{
	return *itr_;
}


