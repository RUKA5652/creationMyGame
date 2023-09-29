#include"DecisionData.h"
#include<algorithm>

void Beat::Hit::clear()
{
	normalsResult.clear();
	if (holdsResult)
	{
		if (holdsResult.value().endFlag)
		{
			holdsResult.reset();
		}
	}
	//holdsResult = std::nullopt;
	//holdsResult.clear();
	//std::ranges::remove_if(holdsResult, [](auto& data) {return data.endFlag; });
}

Beat::HitsData::HitsData(const int  size)
{
	hitData_.resize(size);
	combo = 0;
	score = 0;
}


