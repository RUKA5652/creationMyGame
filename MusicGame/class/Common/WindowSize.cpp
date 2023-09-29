#include "WindowSize.h"

WindowSize::~WindowSize()
{
}

const WindowSize::Size& WindowSize::GetSize() const
{
	return size_;
}

WindowSize::WindowSize()
{
	size_.x = 1365;
	size_.y = 768;
}
