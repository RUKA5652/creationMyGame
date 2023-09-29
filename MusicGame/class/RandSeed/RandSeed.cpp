#include "RandSeed.h"
#include <random>
#include<chrono>

const unsigned int& RandSeed::GetSeed() const
{
	return seed_;
}

RandSeed::RandSeed()
{
	seed_ = std::random_device()();
}

RandSeed::~RandSeed()
{
}
