#include"ResultData.h"

Beat::ResultData::ResultData(std::shared_ptr<const Beat::Events::BackImage> image, HitsDataPtr hitsData)
{
	this->image = std::move(image);
	hitsData->result =
	{
		{Type::BAD,0},
		{Type::GOOD,0},
		{Type::GREAT,0},
		{Type::JUST,0},
	};
	this->hitsData = hitsData;
}

