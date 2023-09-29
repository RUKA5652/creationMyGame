#pragma once

#define lpSeedMng  RandSeed::GetInstance()

class RandSeed
{
public:
	static const RandSeed& GetInstance()
	{
		static RandSeed seed;
		return seed;
	}

	const unsigned int& GetSeed() const;

private:
	RandSeed();
	~RandSeed();

	unsigned int seed_;
};

