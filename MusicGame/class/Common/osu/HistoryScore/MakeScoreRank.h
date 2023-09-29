#pragma once
#include "../Skin/Image/SkinImageData.h"
#include "../Skin/Image/SkinImage.h"
#include "../game/DecisionData.h"

struct MakeScoreRank
{
	inline auto operator()(int score)
	{
		const auto* rankImage = &lpSkinImagePtr.GetAllImage(Beat::SkinImageType::RankD);
		auto rank = "D";
		if (score > Beat::maxScore * 0.7)
		{
			rankImage = &lpSkinImagePtr.GetAllImage(Beat::SkinImageType::RankC);
			rank = "C";
		}
		if (score > Beat::maxScore * 0.9)
		{
			rankImage = &lpSkinImagePtr.GetAllImage(Beat::SkinImageType::RankB);
			rank = "B";
		}
		if (score > Beat::maxScore * 0.95)
		{
			rankImage = &lpSkinImagePtr.GetAllImage(Beat::SkinImageType::RankA);
			rank = "A";
		}
		if (score > Beat::maxScore * 0.975)
		{
			rankImage = &lpSkinImagePtr.GetAllImage(Beat::SkinImageType::RankS);
			rank = "S";
		}
		if (score > Beat::maxScore * 1)
		{
			rankImage = &lpSkinImagePtr.GetAllImage(Beat::SkinImageType::RankSH);
			rank = "SH";
		}
		if (score > Beat::maxScore * 1.005)
		{
			rankImage = &lpSkinImagePtr.GetAllImage(Beat::SkinImageType::RankSS);
			rank = "SS";
		}
		if (score > Beat::maxScore * 1.009)
		{
			rankImage = &lpSkinImagePtr.GetAllImage(Beat::SkinImageType::RankSSH);
			rank = "SSH";
		}
		return std::pair<const std::vector<Beat::SkinImage>&,const char*>(*rankImage,rank);
	}
};
