#pragma once
#include"../../Base/BaseData.h"
#include"../EventsData.h"
#include"../game/DecisionData.h"

namespace Beat
{
	struct ResultData
		:public BaseData
	{
		ResultData(std::shared_ptr<const Beat::Events::BackImage> image, HitsDataPtr hitsData);

		std::shared_ptr<const Beat::Events::BackImage> image;
		HitsDataPtr hitsData;

	};
	using ResultDataPtr = std::shared_ptr<ResultData>;
	using ResultDataConstPtr = std::shared_ptr<const ResultData>;
}

