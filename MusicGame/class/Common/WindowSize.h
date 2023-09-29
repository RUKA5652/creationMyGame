#pragma once

#define lpWindowSize WindowSize::GetInstance()

class WindowSize
{
public:

	using X = int;
	using Y = int;
	struct Size
	{
		X x;
		Y y;
	};

	~WindowSize();

	static WindowSize* GetInstance()
	{
		static WindowSize* ptr;
		if (ptr == nullptr)
		{
			ptr = new WindowSize();
		}
		return ptr;
	}

	const Size& GetSize() const;

private:
	WindowSize();
	WindowSize(WindowSize&) = delete;
	WindowSize(WindowSize*) = delete;

	Size size_;

};


