#include "LaneLength.h"
#include"../../../WindowSize.h"

LaneLength::LaneLength()
{
	length_ = lpWindowSize->GetSize().y;
}

const LaneLength::Length& LaneLength::GetLength() const
{
	return length_;
}
