#include "DecisionDrawInterface.h"
#include "../../../Skin/Image/SkinImage.h"


DecisionDrawInterface::DecisionDrawInterface(Beat::HitsDataConstPtr hitsData)
	:hitsData_(hitsData)
{
	LoadImageData();
}

DecisionDrawInterface::~DecisionDrawInterface()
{
}

void DecisionDrawInterface::LoadImageData()
{
	auto& skin = lpSkinImagePtr;
	auto GetFirstImage = [&](Beat::Type&& type) {
		return skin.GetFirstImage(static_cast<Beat::SkinImageType>(type));
	};

	imageData_ =
	{
		{Beat::Type::JUST,GetFirstImage(Beat::Type::JUST)},
		{Beat::Type::GREAT,GetFirstImage(Beat::Type::GREAT)},
		{Beat::Type::GOOD,GetFirstImage(Beat::Type::GOOD)},
		{Beat::Type::BAD,GetFirstImage(Beat::Type::BAD)},
	};

}
